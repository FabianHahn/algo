#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::AnyOf;
using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::string longestPalindrome(std::string s) {
  if (s.empty()) {
    return s;
  }

  int longestSize = 0;
  int longestIndex = 0;
  for (int i = 0; i < s.size(); i++) {
    int k = 0;
    while (i - k - 1 >= 0 && i + k + 1 < s.size() && s[i - k - 1] == s[i + k + 1]) {
      k++;
    }

    if (2 * k + 1 > longestSize) {
      longestSize = 2 * k + 1;
      longestIndex = i - k;
    }

    k = 0;
    while (i - k >= 0 && i + k + 1 < s.size() && s[i - k] == s[i + k + 1]) {
      k++;
    }

    if (2 * k > longestSize) {
      longestSize = 2 * k;
      longestIndex = i - k + 1;
    }
  }

  return s.substr(longestIndex, longestSize);
}

TEST(LongestPalindromicSubstring, test) {
  EXPECT_THAT(longestPalindrome("babad"), AnyOf(Eq("bab"), Eq("aba")));
  EXPECT_THAT(longestPalindrome("cbbd"), Eq("bb"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
