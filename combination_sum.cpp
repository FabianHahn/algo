#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int combinationSum4(std::vector<int>& nums, int target) {
  std::vector<int> combinations(target, -1);

  std::function<int(int)> countCombinations;
  countCombinations = [&](int t) {
    if (t < 1) {
      return 0;
    }

    int lookup = combinations[t - 1];
    if (lookup >= 0) {
      return lookup;
    }

    int result = 0;
    for (int i = 0; i < nums.size(); i++) {
      int num = nums[i];
      if (t == num) {
        result += 1;
      } else if (num < t) {
        result += countCombinations(t - nums[i]);
      }
    }

    combinations[t - 1] = result;
    return result;
  };

  return countCombinations(target);
}

int combinationSum4Test(const std::vector<int>& nums, int target) {
  std::vector<int> copy{nums};
  return combinationSum4(copy, target);
}

int combinationSumDp(std::vector<int>& nums, int target) {
  std::vector<int> combinations(nums.size() * target, -1);

  std::function<int(int, int)> countCombinations;
  countCombinations = [&](int n, int t) {
    if (n < 0) {
      return 0;
    }
    if (t < 1) {
      return 0;
    }

    int lookup = combinations[n * target + t - 1];
    if (lookup >= 0) {
      return lookup;
    }

    int num = nums[n];
    int result;
    if (num == t) {
      result = countCombinations(n - 1, t) + 1;
    } else if (num < t) {
      result = countCombinations(n, t - num) + countCombinations(n - 1, t);
    } else {
      result = countCombinations(n - 1, t);
    }

    combinations[n * target + t - 1] = result;
    return result;
  };

  return countCombinations(nums.size() - 1, target);
}

int combinationSumDpTest(const std::vector<int>& nums, int target) {
  std::vector<int> copy{nums};
  return combinationSumDp(copy, target);
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& nums, int target) {
  std::sort(nums.begin(), nums.end());

  std::vector<std::pair<bool, std::vector<std::vector<int>>>> combinations(
      nums.size() * target, std::make_pair(false, std::vector<std::vector<int>>{}));

  std::function<std::vector<std::vector<int>>(int, int)> countCombinations;
  countCombinations = [&](int n, int t) -> std::vector<std::vector<int>> {
    if (n < 0) {
      return {};
    }
    if (t < 1) {
      return {};
    }

    auto lookup = combinations[n * target + t - 1];
    if (lookup.first) {
      return lookup.second;
    }

    int num = nums[n];
    std::vector<std::vector<int>> result;
    if (num == t) {
      result.push_back(std::vector<int>{num});
      int i = n - 1;
      while (i > 0 && nums[i] == num) {
        i--;
      }
      if (i >= 0 && nums[i] != num) {
        auto subcombinations = countCombinations(i, t);
        result.insert(result.end(), subcombinations.begin(), subcombinations.end());
      }
    } else if (num < t) {
      auto subcombinationsWithNum = countCombinations(n - 1, t - num);
      for (auto combination : subcombinationsWithNum) {
        combination.push_back(num);
        result.push_back(combination);
      }
      int i = n - 1;
      while (i > 0 && nums[i] == num) {
        i--;
      }
      if (i >= 0 && nums[i] != num) {
        auto subcombinationsWithoutNum = countCombinations(i, t);
        result.insert(
            result.end(), subcombinationsWithoutNum.begin(), subcombinationsWithoutNum.end());
      }
    } else {
      result = countCombinations(n - 1, t);
    }

    combinations[n * target + t - 1] = std::make_pair(true, result);
    return result;
  };

  return countCombinations(nums.size() - 1, target);
}

std::vector<std::vector<int>> combinationSum2Test(const std::vector<int>& nums, int target) {
  std::vector<int> copy{nums};
  return combinationSum2(copy, target);
}

TEST(CombinationSum, sum4) {
  ASSERT_EQ(combinationSum4Test(std::vector<int>{1, 2, 3}, 4), 7);
  ASSERT_EQ(combinationSum4Test(std::vector<int>{3}, 9), 1);
  ASSERT_EQ(combinationSum4Test(std::vector<int>{9}, 3), 0);
}

TEST(CombinationSum, dp) {
  ASSERT_EQ(combinationSumDpTest(std::vector<int>{1, 2, 3}, 4), 4);
  ASSERT_EQ(combinationSumDpTest(std::vector<int>{3}, 9), 1);
  ASSERT_EQ(combinationSumDpTest(std::vector<int>{9}, 3), 0);
}

TEST(CombinationSum, sum2) {
  ASSERT_THAT(
      combinationSum2Test(std::vector<int>{1, 2, 3}, 4),
      UnorderedElementsAre(UnorderedElementsAre(1, 3)));
  ASSERT_THAT(
      combinationSum2Test(std::vector<int>{10, 1, 2, 7, 6, 1, 5}, 8),
      UnorderedElementsAre(
          UnorderedElementsAre(1, 1, 6),
          UnorderedElementsAre(1, 2, 5),
          UnorderedElementsAre(1, 7),
          UnorderedElementsAre(2, 6)));
  ASSERT_THAT(
      combinationSum2Test(std::vector<int>{2, 5, 2, 1, 2}, 5),
      UnorderedElementsAre(UnorderedElementsAre(1, 2, 2), UnorderedElementsAre(5)));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
