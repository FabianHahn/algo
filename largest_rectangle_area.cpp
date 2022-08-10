#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int largestRectangleArea(const std::vector<int>& heights) {
  if (heights.empty()) {
    return 0;
  }
  if (heights.size() == 1) {
    return heights[0];
  }

  std::vector<std::pair<int, int>> stack;
  int largest = 0;
  for (int i = 0; i < heights.size(); i++) {
    int current = heights[i];

    int width = 0;
    while (!stack.empty()) {
      int previous = stack.back().first;
      int previousWidth = stack.back().second;
      if (previous <= current) {
        break;
      }

      width += previousWidth;
      if (width * previous > largest) {
        largest = width * previous;
      }

      stack.pop_back();
    }

    int previous = 0;
    if (!stack.empty()) {
      previous = stack.back().first;
    }

    if (!stack.empty() && current == previous) {
      stack.back().second += width + 1;
    } else {
      assert(stack.empty() || current > previous);
      stack.emplace_back(std::make_pair(current, width + 1));
    }
  }

  int width = 0;
  while (!stack.empty()) {
    int previous = stack.back().first;
    int previousWidth = stack.back().second;

    width += previousWidth;

    if (width * previous > largest) {
      largest = width * previous;
    }

    stack.pop_back();
  }

  return largest;
}

TEST(LargestRectangleArea, test) {
  EXPECT_EQ(largestRectangleArea(std::vector<int>{2, 1, 2}), 3);
  EXPECT_EQ(largestRectangleArea(std::vector<int>{2, 1, 5, 6, 2, 3}), 10);
  EXPECT_EQ(largestRectangleArea(std::vector<int>{2, 4}), 4);
  EXPECT_EQ(largestRectangleArea(std::vector<int>(42858, 8180)), 42858 * 8180);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
