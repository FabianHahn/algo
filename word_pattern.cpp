#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool wordPattern(std::string pattern, std::string s) {
  std::vector<std::string> words;
  {
    std::istringstream stream{s};
    std::string word;
    while (stream >> word) {
      words.emplace_back(word);
    }
  }

  if (pattern.size() != words.size()) {
    return false;
  }

  std::unordered_map<char, std::string> patternWords;
  std::unordered_map<std::string, char> wordPatterns;
  for (int i = 0; i < pattern.size(); i++) {
    char c = pattern[i];
    const auto& word = words[i];
    auto query1 = patternWords.find(c);
    auto query2 = wordPatterns.find(word);
    if (query1 == patternWords.end() && query2 == wordPatterns.end()) {
      patternWords[c] = word;
      wordPatterns[word] = c;
      continue;
    }
    if (query1 == patternWords.end() && query2 != wordPatterns.end()) {
      return false;
    }
    if (query1 != patternWords.end() && query2 == wordPatterns.end()) {
      return false;
    }

    const auto& patternWord = query1->second;
    char wordPattern = query2->second;
    if (c != wordPattern || word != patternWord) {
      return false;
    }
  }

  return true;
}

TEST(WordPattern, test) {
  EXPECT_FALSE(wordPattern("abba", "dog cat cat fish"));
  EXPECT_FALSE(wordPattern("aaaa", "dog cat cat dog"));
  EXPECT_TRUE(wordPattern("abba", "dog cat cat dog"));
  EXPECT_FALSE(wordPattern("abba", "dog dog dog dog"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
