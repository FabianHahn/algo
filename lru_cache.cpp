#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

class LRUCache {
public:
  LRUCache(int capacity_) : capacity{capacity_} {}

  int get(int key) {
    auto query = entries.find(key);
    if (query == entries.end()) {
      return -1;
    }

    auto valuesIter = query->second;
    int value = valuesIter->second;
    values.erase(valuesIter);
    values.push_front(std::make_pair(key, value));
    query->second = values.begin();

    return value;
  }

  void put(int key, int value) {
    auto query = entries.find(key);
    if (query != entries.end()) {
      auto valuesIter = query->second;
      values.erase(valuesIter);
      values.push_front(std::make_pair(key, value));
      query->second = values.begin();
    } else {
      if (values.size() == capacity) {
        int leastRecentlyUsedKey = values.back().first;
        values.pop_back();
        entries.erase(leastRecentlyUsedKey);
      }

      values.push_front(std::make_pair(key, value));
      entries[key] = values.begin();
    }
  }

  using ValuesList = std::list<std::pair<int, int>>;

  int capacity;
  std::unordered_map<int, ValuesList::iterator> entries;
  ValuesList values;
};

TEST(LruCache, test) {
  LRUCache lRUCache{2};
  lRUCache.put(1, 1); // cache is {1=1}
  lRUCache.put(2, 2); // cache is {1=1, 2=2}
  ASSERT_EQ(lRUCache.get(1), 1); // return 1
  lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  ASSERT_EQ(lRUCache.get(2), -1); // returns -1 (not found)
  lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  ASSERT_EQ(lRUCache.get(1), -1); // return -1 (not found)
  ASSERT_EQ(lRUCache.get(3), 3); // return 3
  ASSERT_EQ(lRUCache.get(4), 4); // return 4
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
