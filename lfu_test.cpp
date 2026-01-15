#include <gtest/gtest.h>
#include "lfu.hpp"

TEST(LFUTest, canPutAndGet)
{
    LFUCache<int, int> lfu(10);
    lfu.put(2, 5);
    int res = lfu.get(2);
    EXPECT_EQ(res, 5);
}

TEST(LFUTest, evictLeastFreq)
{
    LFUCache<int, int> lfu(2);
    lfu.put(1, 2);
    lfu.put(3, 4);
    lfu.get(1);
    lfu.get(1);    // 1 has freq 3.
    lfu.put(5, 6); // 3 should be evicted.

    EXPECT_THROW(lfu.get(3), std::out_of_range);
}