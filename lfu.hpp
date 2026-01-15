#include <iostream>
#include <unordered_map>
#include <list>

template <typename K, typename V>
struct Node
{
    int freq;
    K key; // When evicting, minFreq -> back of list -> key -> remove from keyMap.
    V value;
};

template <typename K, typename V>
class LFUCache
{
public:
    explicit LFUCache(int capacity) : capacity_{capacity} {}

    void put(const K &key, const V &value)
    {
        if (!keyToIt_.contains(key))
        {
            if (size_ == capacity_)
            {
                // evict
                K &keyToBeEvicted = freqToList_[minFreq_].back().key;
                keyToIt_.erase(keyToBeEvicted);
                freqToList_[minFreq_].pop_back();
                --size_;
            }
            freqToList_[1].emplace_front(1, key, value);
            auto it = freqToList_[1].begin();
            keyToIt_[key] = it;
            minFreq_ = 1;
            ++size_;
        }
        else
        {
            auto it = keyToIt_.find(key);
            freq_type curFreq = it->second->freq;
            freqToList_[curFreq + 1].emplace_front(curFreq, key, value);
            freqToList_[curFreq].erase(it->second);
            if (curFreq == minFreq_ && freqToList_[curFreq].empty())
                ++minFreq_;

            keyToIt_[key] = freqToList_[curFreq + 1].begin();
        }
    }

    V &get(const K &key)
    {
        auto it = keyToIt_.find(key);
        if (it == keyToIt_.end())
        {
            throw std::out_of_range("key not found");
        }
        freq_type curFreq = it->second->freq;
        V value = it->second->value;
        freqToList_[curFreq + 1].emplace_front(curFreq + 1, key, value);
        freqToList_[curFreq].erase(it->second);
        if (curFreq == minFreq_ && freqToList_[curFreq].empty())
            ++minFreq_;

        keyToIt_[key] = freqToList_[curFreq + 1].begin();

        return keyToIt_.at(key)->value;
    }

private:
    using freq_type = int;
    using list_type = std::list<Node<K, V>>;

    std::unordered_map<freq_type, list_type> freqToList_;
    std::unordered_map<K, typename list_type::iterator> keyToIt_;
    freq_type minFreq_{};
    const int capacity_;
    int size_{};
};
