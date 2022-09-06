#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::string longestWord(std::vector<std::string>& words) {
  std::sort(words.begin(), words.end());
  int maxSize = 0;
  int bestIndex = -1;
  std::vector<char> prefix;
  for (int i = 0; i < words.size(); i++) {
    const auto& word = words[i];
    int wordSize = word.size();

    int commonPrefixLength = 0;
    for (int j = 0; j < word.size(); j++) {
      if (j < prefix.size() && prefix[j] == word[j]) {
        commonPrefixLength++;
      } else {
        break;
      }
    }
    prefix.resize(commonPrefixLength);
    if (wordSize != commonPrefixLength + 1) {
      // not in a position to append anything
      continue;
    }

    prefix.push_back(word[wordSize - 1]);
    if (prefix.size() > maxSize) {
      maxSize = prefix.size();
      bestIndex = i;
    }
  }

  if (bestIndex < 0) {
    return "";
  }

  return words[bestIndex];
}

std::string longestWordTest(std::vector<std::string> words) { return longestWord(words); }

TEST(LongestDictionaryWord, Test) {
  EXPECT_EQ(
      longestWordTest(std::vector<std::string>{
          "rac",
          "rs",
          "ra",
          "on",
          "r",
          "otif",
          "o",
          "onpdu",
          "rsf",
          "rs",
          "ot",
          "oti",
          "racy",
          "onpd"}),
      "otif");
  EXPECT_EQ(
      longestWordTest(
          std::vector<std::string>{"a", "banana", "app", "appl", "ap", "apply", "apple"}),
      "apple");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
