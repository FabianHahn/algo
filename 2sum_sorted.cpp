#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
  double middle = 0.5 * target;
  auto middleIter = std::lower_bound(numbers.begin(), numbers.end(), target / 2);
  std::size_t middleIndex = middleIter - numbers.begin();
  if (middleIndex + 1 < numbers.size() && numbers[middleIndex] <= middle) {
    middleIndex++;
  }
  if (middleIndex == 0) {
    middleIndex = 1;
  }
  std::size_t lo = middleIndex - 1;
  std::size_t hi = middleIndex;
  while (hi < numbers.size()) {
    int a = numbers[lo];
    int b = numbers[hi];
    assert(b >= a);
    if (a + b == target) {
      return std::vector<int>{(int) lo + 1, (int) hi + 1};
    }

    double da = middle - a;
    double db = b - middle;
    if (da < db) {
      if (lo == 0) {
        break;
      }

      lo--;
    } else {
      hi++;
    }
  }

  return {};
}

TEST(TwoSum, sorted) {
  EXPECT_THAT(twoSum(std::vector<int>{2, 7, 11, 15}, 9), ElementsAre(1, 2));
  EXPECT_THAT(twoSum(std::vector<int>{2, 3, 4}, 6), ElementsAre(1, 3));
  EXPECT_THAT(twoSum(std::vector<int>{-1, 0}, -1), ElementsAre(1, 2));
  EXPECT_THAT(twoSum(std::vector<int>{1, 2, 4, 6, 7, 10}, 9), ElementsAre(2, 5));
  EXPECT_THAT(twoSum(std::vector<int>{0, 0, 3, 4}, 0), ElementsAre(1, 2));
  EXPECT_THAT(twoSum(std::vector<int>{1, 2, 3, 4, 4, 9, 56, 90}, 8), ElementsAre(4, 5));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
