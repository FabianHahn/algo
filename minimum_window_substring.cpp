#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::string minWindow(std::string s, std::string t) {
  if (t.size() > s.size()) {
    return "";
  }
  if (t.empty()) {
    return s;
  }

  int numNeeded = 0;
  std::unordered_map<char, int> need;
  for (char c : t) {
    numNeeded++;
    need[c]++;
  }

  int l = 0;
  int r = 0;
  int bestL = 0;
  int bestSize = INT_MAX;
  int numHave = 0;
  std::unordered_map<char, int> have;
  while (r < s.size()) {
    // extend window to the right
    while (r < s.size() && numHave < numNeeded) {
      char c = s[r];
      if (need[c] > 0) {
        if (have[c] < need[c]) {
          numHave++;
        }
        have[c]++;
      }
      r++;
    }

    if (numHave != numNeeded) {
      break;
    }

    // shrink window from the left
    while (l < r && numHave == numNeeded) {
      // record solution
      int size = r - l;
      if (size < bestSize) {
        bestL = l;
        bestSize = size;
      }

      char c = s[l];
      if (need[c] > 0) {
        have[c]--;
        if (have[c] < need[c]) {
          numHave--;
        }
      }
      l++;
    }
  }

  if (bestSize == INT_MAX) {
    return "";
  }

  return s.substr(bestL, bestSize);
}

TEST(MinimumWindowSubstring, test) {
  EXPECT_EQ(minWindow("ADOBECODEBANC", "ABC"), "BANC");
  EXPECT_EQ(minWindow("a", "a"), "a");
  EXPECT_EQ(minWindow("a", "aa"), "");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
