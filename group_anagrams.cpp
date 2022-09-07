#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct Histogram {
  Histogram() : counts{} {}

  bool operator==(const Histogram& other) const {
    for (int i = 0; i < 26; i++) {
      if (counts[i] != other.counts[i]) {
        return false;
      }
    }
    return true;
  }

  char counts[26];
};

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <>
struct std::hash<Histogram> {
  std::size_t operator()(const Histogram& histogram) const {
    std::size_t hash = 0;
    for (int i = 0; i < 26; i++) {
      hash_combine(hash, histogram.counts[0]);
    }
    return hash;
  }
};

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
  std::unordered_map<Histogram, std::vector<std::string>> groups;
  for (auto& word : strs) {
    Histogram histogram;
    for (char c : word) {
      char index = c - 'a';
      if (index >= 0 && index < 26) {
        histogram.counts[index]++;
      }
    }

    groups[histogram].emplace_back(std::move(word));
  }

  std::vector<std::vector<std::string>> result;
  for (auto entry: groups) {
    std::vector<std::string> group;
    for (auto& word: entry.second) {
      group.emplace_back(std::move(word));
    }
    result.emplace_back(std::move(group));
  }

  return result;
}

std::vector<std::vector<std::string>> groupAnagramsTest(std::vector<std::string> strs) {
  return groupAnagrams(strs);
}

TEST(GroupAnagrams, test) {
  EXPECT_THAT(
      groupAnagramsTest(std::vector<std::string>{"eat", "tea", "tan", "ate", "nat", "bat"}),
      UnorderedElementsAre(
          UnorderedElementsAre("bat"),
          UnorderedElementsAre("nat", "tan"),
          UnorderedElementsAre("ate", "eat", "tea")));
  EXPECT_THAT(
      groupAnagramsTest(std::vector<std::string>{""}),
      UnorderedElementsAre(UnorderedElementsAre("")));
  EXPECT_THAT(
      groupAnagramsTest(std::vector<std::string>{"a"}),
      UnorderedElementsAre(UnorderedElementsAre("a")));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
