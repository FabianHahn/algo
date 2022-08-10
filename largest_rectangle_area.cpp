#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int largestRectangleArea(const std::vector<int>& heights) {
  constexpr auto kMaxHeight = 10000;

  std::vector<int> sizes(kMaxHeight + 1, 0);
  int largest = 0;
  int previous = 0;
  for (int i = 0; i < heights.size(); i++) {
    int current = heights[i];

    for (int j = 1; j <= current; j++) {
      sizes[j]++;
    }

    if (current < previous) {
      for (int j = current + 1; j <= previous; j++) {
        if (sizes[j] * j > largest) {
          largest = sizes[j] * j;
        }

        sizes[j] = 0;
      }
    }

    previous = current;
  }

  for (int j = 0; j <= kMaxHeight; j++) {
    if (sizes[j] * j > largest) {
      largest = sizes[j] * j;
    }

    sizes[j] = 0;
  }

  return largest;
}

TEST(LargestRectangleArea, test) {
  EXPECT_EQ(largestRectangleArea(std::vector<int>{2, 1, 5, 6, 2, 3}), 10);
  EXPECT_EQ(largestRectangleArea(std::vector<int>{2, 4}), 4);
  EXPECT_EQ(largestRectangleArea(std::vector<int>(42858, 8180)), 42858 * 8180);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
