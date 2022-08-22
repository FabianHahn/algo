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
  int endIndex = -1;
  wordList.push_back(beginWord);
  std::vector<std::vector<int>> graph(wordList.size());
  for (int i = 0; i < wordList.size(); i++) {
    const std::string& word1 = wordList[i];
    for (int j = i + 1; j < wordList.size(); j++) {
      const std::string& word2 = wordList[j];
      if (differsByOne(word1, word2)) {
        graph[i].emplace_back(j);
        graph[j].emplace_back(i);
      }
    }

    if (word1 == endWord) {
      endIndex = i;
    }
  }

  if (endIndex == -1) {
    return 0;
  }

  std::vector<int> distances(wordList.size(), -1);
  distances[wordList.size() - 1] = 1;
  std::deque<int> queue{(int) wordList.size() - 1};
  while (!queue.empty()) {
    int current = queue.front();
    queue.pop_front();
    int distance = distances[current];

    if (current == endIndex) {
      return distance;
    }

    for (int neighbor : graph[current]) {
      if (distances[neighbor] >= 0) {
        continue;
      }

      distances[neighbor] = distance + 1;
      queue.emplace_back(neighbor);
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
