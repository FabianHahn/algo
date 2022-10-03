#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int minCost(std::string colors, std::vector<int>& neededTime) {
  int n = colors.size();
  int totalTime = 0;
  char previousColor = '\0';
  int maxCost = 0;
  for (int i = 0; i < n; i++) {
    char color = colors[i];
    int cost = neededTime[i];

    if (color == previousColor) {
      if (cost > maxCost) {
        totalTime += maxCost;
        maxCost = cost;
      } else {
        totalTime += cost;
      }
      continue;
    }

    maxCost = cost;
    previousColor = color;
  }

  return totalTime;
}

int minCostTest(std::string colors, std::vector<int> neededTime) {
  return minCost(colors, neededTime);
}

TEST(ColorfulBalloons, test) {
  EXPECT_EQ(minCostTest("abaac", std::vector<int>{1, 2, 3, 4, 5}), 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
