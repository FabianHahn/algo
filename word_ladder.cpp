#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool differsByOne(const std::string& a, const std::string& b) {
  assert(a.size() == b.size());
  int diff = 0;
  for(int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      diff++;
    }
  }
  return diff == 1;
}

int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
  int k = beginWord.size();

  wordList.push_back(beginWord);
  std::unordered_map<std::string, int> distances;
  for(const auto& word: wordList) {
    distances[word] = -1;
  }
  distances[beginWord] = 1;

  if (distances.find(endWord) == distances.end()) {
    return 0;
  }

  std::deque<std::string> queue{beginWord};
  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop_front();
    int distance = distances[current];

    if (current == endWord) {
      return distance;
    }

    std::string modified = current;
    for (int i = 0; i < k; i++) {
      for (char c = 'a'; c <= 'z'; c++) {
        if (current[i] == c) {
          continue;
        }

        modified[i] = c;

        auto query = distances.find(modified);
        if (query == distances.end()) {
          continue;
        }

        if (query->second >= 0) {
          continue;
        }

        query->second = distance + 1;
        queue.emplace_back(modified);
      }

      modified[i] = current[i];
    }
  }

  return 0;
}

TEST(WordLadder, test) {
  std::vector<std::string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
  EXPECT_THAT(ladderLength("hit", "cog", wordList), 5);
  std::vector<std::string> wordList2{"hot", "dot", "dog", "lot", "log"};
  EXPECT_THAT(ladderLength("hit", "cog", wordList2), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
