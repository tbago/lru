
#include <string>
#include "gtest/gtest.h"

#include "lru_cache.hpp"

LRUCache<int, int> lru_cache(5);

TEST(LRUTest, BasicFunction) {
    lru_cache.Add(1, 123);
    EXPECT_EQ(lru_cache.GetCount(), 1);
}

TEST(LRUTest, MaxStore) {
     for (int i = 0; i < 10; i++) {
        lru_cache.Add(i, i);
    }
    EXPECT_EQ(lru_cache.GetCount(), 5);
}

TEST(LRUTest, GetItem) {
    for (int i = 0; i < 5; i++) {
        lru_cache.Add(i, i + 1);
    }
    for (int i = 0; i < 5; i++) {
        int value = 0;
        bool result = lru_cache.Search(i, value);
        EXPECT_EQ(result, true);
        EXPECT_EQ(value, i + 1);
    }
}

TEST(LRUTest, ReplaceElement) {
    for (int i = 0; i < 6; i++) {
        lru_cache.Add(i, i);
    }
    int value = -1;
    bool result = lru_cache.Search(0, value);
    EXPECT_EQ(result, false);
    result = lru_cache.Search(1, value);
    EXPECT_EQ(result, true);
}
