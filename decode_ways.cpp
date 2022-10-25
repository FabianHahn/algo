#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int numDecodings(std::string s) {
  auto madd = [](int64_t a, int64_t b) {
    const int64_t p = 1000000007;
    return static_cast<int>((a + b) % p);
  };
  auto mmul = [](int64_t a, int64_t b) {
    const int64_t p = 1000000007;
    return static_cast<int>((a * b) % p);
  };

  int n = s.size();
  int prev = 1;
  int pprev = 0;
  char prevC = '\0';
  for (int k = n - 1; k >= 0; k--) {
    int ways = 0;
    char c = s[k];

    if (c >= '1' && c <= '9') {
      // can just pick this individually plus the rest as it was
      ways = madd(ways, prev);
    }
    if (c == '*') {
      ways = madd(ways, mmul(9, prev));
    }

    if (c == '1' && prevC != '*') {
      ways = madd(ways, pprev);
    }
    if (c == '2' && prevC >= '0' && prevC <= '6') {
      ways = madd(ways, pprev);
    }
    if (c == '1' && prevC == '*') {
      ways = madd(ways, mmul(9, pprev));
    }
    if (c == '2' && prevC == '*') {
      ways = madd(ways, mmul(6, pprev));
    }
    if (c == '*' && prevC >= '0' && prevC <= '6') {
      ways = madd(ways, mmul(2, pprev));
    }
    if (c == '*' && prevC >= '7' && prevC <= '9') {
      ways = madd(ways, pprev);
    }
    if (c == '*' && prevC == '*') {
      ways = madd(ways, mmul(15, pprev));
    }

    prevC = c;
    pprev = prev;
    prev = ways;
  }

  return prev;
}

TEST(DecodeWays, test) {
  EXPECT_EQ(numDecodings("*1*1*0"), 404);
  EXPECT_EQ(numDecodings("1*"), 18);
  EXPECT_EQ(numDecodings("2*"), 15);
  EXPECT_EQ(numDecodings("*1"), 11);
  EXPECT_EQ(numDecodings("*2"), 11);
  EXPECT_EQ(numDecodings("**"), 96);
  EXPECT_EQ(numDecodings("2*111"), 49);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
