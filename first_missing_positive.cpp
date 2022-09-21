#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int firstMissingPositive(std::vector<int>& nums) {
  int n = nums.size();
  for (int i = 0; i < n; i++) {
    int num = nums[i];
    if (num < 1 || num > n) {
      // out of range, we don't care about this number at all
      nums[i] = 0;
      continue;
    }

    int targetPosition = num - 1;

    if (i == targetPosition) {
      // correct element
      continue;
    }

    if (nums[targetPosition] == num) {
      // correct number already at position, this is a duplicate
      nums[i] = 0;
      continue;
    }

    // Move number into target position.
    std::swap(nums[i], nums[targetPosition]);
    i--;
  }

  int nextMissing = 1;
  for (int i = 0; i < n; i++) {
    int num = nums[i];
    int targetPosition = num - 1;

    if (i != targetPosition) {
      // incorrect element
      break;
    }

    nextMissing++;
  }
  return nextMissing;
}

int firstMissingPositiveTest(std::vector<int> nums) {
  return firstMissingPositive(nums);
}

TEST(FirstMissingPositive, test) {
  EXPECT_EQ(firstMissingPositiveTest(std::vector<int>{0, 2, 2, 1, 1}), 3);
  EXPECT_EQ(firstMissingPositiveTest(std::vector<int>{7, 8, 9, 11, 12}), 1);
  EXPECT_EQ(firstMissingPositiveTest(std::vector<int>{1, 2, 0}), 3);
  EXPECT_EQ(firstMissingPositiveTest(std::vector<int>{3, 4, -1, 1}), 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
