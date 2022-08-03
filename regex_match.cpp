#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool isMatchPos(const std::string& s, const std::string& p, int i, int j) {
  int ns = s.size();
  int np = p.size();

  if (i >= ns) {
    if (j >= np) {
      return true;
    }
    if ((np - j) % 2 == 1) {
      return false;
    }
    for (j = j + 1; j < np; j += 2) {
      if (p[j] != '*') {
        return false;
      }
    }
    return true;
  }

  for (; i < ns; i++) {
    char sc = s[i];
    char pc = p[j];
    bool isStar = j + 1 < np && p[j + 1] == '*';
    if (!isStar) {
      if (pc != '.' && sc != pc) {
        return false;
      }
      j++;
    } else if (pc != '.' && sc != pc) {
      // No match for the star character anymore, so the star pattern must have ended.
      i--; // retry this character
      j += 2; // skip the star pattern
    } else {
      // Star pattern is matching, so it might be continuing.
      if (isMatchPos(s, p, i, j + 2)) {
        return true;
      }
    }
  }

  return isMatchPos(s, p, i, j);
}

bool isMatch(const std::string& s, const std::string& p) { return isMatchPos(s, p, 0, 0); }

bool isMatchDp(const std::string& s, const std::string& p) {
  int ns = s.size();
  int np = p.size();

  // trivial cases
  if (ns == 0) {
    if (np == 0) {
      return true;
    }
    if (np % 2 == 1) {
      return false;
    }
    for (int j = 1; j < np; j += 2) {
      if (p[j] != '*') {
        return false;
      }
    }
    return true;
  }

  // compute number of pattern elements
  for (int j = 0; j < p.size(); j++) {
    if (p[j] == '*') {
      np--;
    }
  }

  std::vector<bool> table((ns + 1) * (np + 1));

  // bottom right entry
  table[np * (ns + 1) + ns] = true;

  // fill bottom row
  for (int i = 0; i < ns; i++) {
    table[np * (ns + 1) + i] = false;
  }

  // fill right column
  int j = p.size() - 1;
  int k = np - 1;
  while (j >= 0) {
    if (p[j] != '*') {
      break;
    }
    table[k * (ns + 1) + ns] = true;
    j -= 2; // skip star pattern
    k--;
  }
  while (k >= 0) {
    table[k * (ns + 1) + ns] = false;
    k--;
  }

  // fill table from bottom to top, right to left
  j = p.size() - 1;
  k = np - 1;
  while (k >= 0) {
    bool isStar = p[j] == '*';
    char pc = isStar ? p[j - 1] : p[j];

    int i = ns - 1;
    while (i >= 0) {
      char sc = s[i];

      if (!isStar) {
        if (pc != '.' && sc != pc) {
          table[k * (ns + 1) + i] = false;
        } else {
          table[k * (ns + 1) + i] = table[(k + 1) * (ns + 1) + i + 1];
        }
      } else {
        if (pc != '.' && sc != pc) {
          table[k * (ns + 1) + i] = table[(k + 1) * (ns + 1) + i];
        } else {
          table[k * (ns + 1) + i] =
              table[(k + 1) * (ns + 1) + i] || table[k * (ns + 1) + i + 1];
        }
      }

      i--;
    }

    k--;
    if (isStar) {
      j -= 2;
    } else {
      j--;
    }
  }

  return table[0];
}

TEST(RegexMatch, test) {
  ASSERT_TRUE(isMatch("", ""));
  ASSERT_FALSE(isMatch("", "a"));
  ASSERT_TRUE(isMatch("", ".*"));
  ASSERT_TRUE(isMatch("", "a*b*"));
  ASSERT_FALSE(isMatch("aa", "p"));
  ASSERT_TRUE(isMatch("aa", "a*"));
  ASSERT_TRUE(isMatch("ab", ".*"));
  ASSERT_TRUE(isMatch("foobar", "fo*bar"));
  ASSERT_TRUE(isMatch("foobar", "fo*obar"));
  ASSERT_TRUE(isMatch("foobar", "fo*oobar"));
  ASSERT_TRUE(isMatch("foobar", "foo*bar"));
  ASSERT_TRUE(isMatch("foobar", "fooo*bar"));
  ASSERT_FALSE(isMatch("ab", ".*c"));
}


TEST(RegexMatch, dp) {
  ASSERT_TRUE(isMatchDp("", ""));
  ASSERT_FALSE(isMatchDp("", "a"));
  ASSERT_TRUE(isMatchDp("", ".*"));
  ASSERT_TRUE(isMatchDp("", "a*b*"));
  ASSERT_FALSE(isMatchDp("aa", "p"));
  ASSERT_TRUE(isMatchDp("aa", "a*"));
  ASSERT_TRUE(isMatchDp("ab", ".*"));
  ASSERT_TRUE(isMatchDp("foobar", "fo*bar"));
  ASSERT_TRUE(isMatchDp("foobar", "fo*obar"));
  ASSERT_TRUE(isMatchDp("foobar", "fo*oobar"));
  ASSERT_TRUE(isMatchDp("foobar", "foo*bar"));
  ASSERT_TRUE(isMatchDp("foobar", "fooo*bar"));
  ASSERT_FALSE(isMatchDp("ab", ".*c"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
