#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int minEatingSpeed(std::vector<int>& piles, int h) {
  int maxPile = 0;
  for (int pile : piles) {
    if (pile > maxPile) {
      maxPile = pile;
    }
  }

  auto speed = [&](int k) {
    int time = 0;
    for (int pile : piles) {
      if (pile % k == 0) {
        time += pile / k;
      } else {
        time += (pile / k) + 1;
      }
    }
    return time;
  };

  int lo = 0;
  int hi = maxPile;
  while (hi - lo > 1) {
    int diff = hi - lo;
    int halfDiff = diff / 2;
    int mid = hi - halfDiff;

    int currentSpeed = speed(mid);
    if (currentSpeed <= h) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  return hi;
}

int minEatingSpeedTest(std::vector<int> piles, int h) { return minEatingSpeed(piles, h); }

TEST(MinEatingSpeed, test) {
  EXPECT_EQ(minEatingSpeedTest(std::vector<int>{3, 6, 7, 11}, 8), 4);
  EXPECT_EQ(
      minEatingSpeedTest(
          std::vector<int>{
              332484035,
              524908576,
              855865114,
              632922376,
              222257295,
              690155293,
              112677673,
              679580077,
              337406589,
              290818316,
              877337160,
              901728858,
              679284947,
              688210097,
              692137887,
              718203285,
              629455728,
              941802184},
          823855818),
      14);
  EXPECT_EQ(minEatingSpeedTest(std::vector<int>{312884470}, 312884469), 2);
  EXPECT_EQ(minEatingSpeedTest(std::vector<int>{30, 11, 23, 4, 20}, 5), 30);
  EXPECT_EQ(minEatingSpeedTest(std::vector<int>{30, 11, 23, 4, 20}, 6), 23);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
