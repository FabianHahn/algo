#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int maxValueOfCoins(std::vector<std::vector<int>>& piles, int k) {
  std::vector<int> maxValueDp(piles.size() * k, -1);
  std::function<int(int, int)> maxValue;
  maxValue = [&](int picks, int startPile) {
    if (picks == 0) {
      return 0;
    }
    if (startPile >= piles.size()) {
      return INT_MIN;
    }

    int index = startPile * k + picks - 1;
    int& bestChoice = maxValueDp[index];
    if (bestChoice != -1) {
      return bestChoice;
    }

    bestChoice = INT_MIN;
    int pileIndex = 0;
    int pileValue = 0;
    while (pileIndex <= picks) {
      int choice = maxValue(picks - pileIndex, startPile + 1) + pileValue;
      if (choice > bestChoice) {
        bestChoice = choice;
      }

      if (pileIndex == piles[startPile].size()) {
        break;
      }

      // add top coin of pile
      pileValue += piles[startPile][pileIndex];
      pileIndex++;
    }

    return bestChoice;
  };

  return maxValue(k, 0);
}

int maxValueOfCoinsTest(std::vector<std::vector<int>> piles, int k) {
  return maxValueOfCoins(piles, k);
}

TEST(CoinPiles, test) {
  EXPECT_EQ(maxValueOfCoinsTest(std::vector<std::vector<int>>{{1, 100, 3}, {7, 8, 9}}, 2), 101);
  EXPECT_EQ(
      maxValueOfCoinsTest(
          std::vector<std::vector<int>>{
              {100}, {100}, {100}, {100}, {100}, {100}, {1, 1, 1, 1, 1, 1, 700}},
          7),
      706);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
