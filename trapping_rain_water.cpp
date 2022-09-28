#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int trap(std::vector<int> heights) {
  int n = heights.size();
  int total = 0;
  std::vector<std::pair<int, int>> stack;
  for (int i = 0; i < n; i++) {
    int height = heights[i];
    if (stack.empty()) {
      stack.emplace_back(std::make_pair(height, i));
      continue;
    }

    auto [lowestHeight, lowestIndex] = stack.back();
    if (height == lowestHeight) {
      // do nothing
      continue;
    } else if (height < lowestHeight) {
      stack.emplace_back(std::make_pair(height, i));
      continue;
    }
    assert(height > lowestHeight);

    int pushIndex = i;
    stack.pop_back();
    while (!stack.empty()) {
      auto [nextLowestHeight, nextLowestIndex] = stack.back();

      // fill up water: [lowestIndex, i] x [lowestHeight, min(nextLowestHeight, height)]
      total += (i - lowestIndex) * (std::min(nextLowestHeight, height) - lowestHeight);

      if (nextLowestHeight >= height) {
        if (nextLowestHeight > height) {
          pushIndex = lowestIndex;
        }
        break;
      }

      lowestHeight = nextLowestHeight;
      lowestIndex = nextLowestIndex;
      stack.pop_back();
    }

    stack.emplace_back(std::make_pair(height, pushIndex));
  }

  return total;
}

TEST(TrappingRainWater, test) {
  EXPECT_EQ(trap(std::vector<int>{0,3,0,0,2,0}), 4);
  EXPECT_EQ(trap(std::vector<int>{0,4,3,3,1,1,0,3,0}), 7);
  EXPECT_EQ(trap(std::vector<int>{0,2,2,1,1,0,0,3,0}), 6);
  EXPECT_EQ(trap(std::vector<int>{0,1,0,2,1,0,1,3,2,1,2,1}), 6);
  EXPECT_EQ(trap(std::vector<int>{4,2,0,3,2,5}), 9);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
