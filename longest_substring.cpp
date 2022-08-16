#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int lengthOfLongestSubstring(std::string s) {
  std::unordered_set<char> letters;
  int lo = 0;
  int hi = 0;
  int maxLength = 0;
  while (hi < s.size()) {
    assert(lo <= hi);

    char c = s[hi];
    auto query = letters.find(c);
    if (query == letters.end()) {
      letters.insert(c);
      hi++;
    } else {
      while (s[lo] != c) {
        letters.erase(s[lo]);
        lo++;
      }
      lo++;
      hi++;
    }

    if (letters.size() > maxLength) {
      maxLength = letters.size();
    }
  }

  return maxLength;
}

TEST(LongestSubstring, test) {
  EXPECT_EQ(lengthOfLongestSubstring("abcabcbb"), 3);
  EXPECT_EQ(lengthOfLongestSubstring("bbbbb"), 1);
  EXPECT_EQ(lengthOfLongestSubstring("pwwkew"), 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
