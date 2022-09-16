#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool isHappy(int number) {
  std::unordered_set<int> dp;
  std::function<bool(int)> isHappyRec;
  isHappyRec = [&](int n) {
    if (n == 1) {
      return true;
    }

    if (dp.find(n) != dp.end()) {
      return false;
    }

    int digitSquareSum = 0;
    while (n / 10 > 0) {
      int digit = n % 10;
      n -= digit;
      n /= 10;
      digitSquareSum += digit * digit;
    }
    digitSquareSum += n * n;

    dp.insert(n);
    return isHappyRec(digitSquareSum);
  };

  return isHappyRec(number);
}

bool isHappyTortoise(int number) {
  auto advance = [](int n) {
    int digitSquareSum = 0;
    while (n / 10 > 0) {
      int digit = n % 10;
      n -= digit;
      n /= 10;
      digitSquareSum += digit * digit;
    }
    digitSquareSum += n * n;
    return digitSquareSum;
  };

  int slow = number;
  int fast = advance(number);
  while (fast != 1 && slow != fast) {
    slow = advance(slow);
    fast = advance(advance(fast));
  }

  return fast == 1;
}

TEST(HappyNumber, test) {
  EXPECT_THAT(isHappy(1111111), true);
  EXPECT_THAT(isHappy(2), false);
  EXPECT_THAT(isHappy(27), false);
  EXPECT_THAT(isHappy(19), true);
}

TEST(HappyNumber, test2) {
  EXPECT_THAT(isHappyTortoise(1111111), true);
  EXPECT_THAT(isHappyTortoise(2), false);
  EXPECT_THAT(isHappyTortoise(27), false);
  EXPECT_THAT(isHappyTortoise(19), true);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
