#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
  std::unordered_multimap<int, std::size_t> indices;
  std::vector<int> diffs(nums.size());
  for (std::size_t i = 0; i < nums.size(); i++) {
    indices.insert(std::make_pair(nums[i], i));
  }

  for (std::size_t i = 0; i < nums.size(); i++) {
    int b = target - nums[i];
    auto query = indices.find(b);
    if (b == nums[i] && indices.count(b) < 2) {
      continue;
    }
    if (query != indices.end()) {
      return std::vector<int>{(int) i, (int) query->second};
    }
  }

  return {};
}

TEST(TwoSum, duos) {
  EXPECT_THAT(twoSum(std::vector<int>{2, 7, 11, 15}, 9), UnorderedElementsAre(0, 1));
  EXPECT_THAT(twoSum(std::vector<int>{3, 2, 4}, 6), UnorderedElementsAre(1, 2));
  EXPECT_THAT(twoSum(std::vector<int>{3, 3}, 6), UnorderedElementsAre(0, 1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
