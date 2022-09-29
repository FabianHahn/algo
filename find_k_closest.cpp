#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;

std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
  int n = arr.size();

  auto iter = std::upper_bound(arr.begin(), arr.end(), x);
  int lo = iter - arr.begin();
  int hi = lo;
  while (hi - lo < k) {
    bool canPickPrevious = lo > 0;
    bool canPickNext = hi < n;

    if (canPickPrevious && !canPickNext) {
      lo--;
      continue;
    }
    if (!canPickPrevious && canPickNext) {
      hi++;
      continue;
    }

    int previous = arr[lo - 1];
    int next = arr[hi];

    int previousDistance = std::abs(previous - x);
    int nextDistance = std::abs(next - x);
    if (previousDistance <= nextDistance) {
      lo--;
    } else {
      hi++;
    }
  }

  return {arr.begin() + lo, arr.begin() + hi};
}

std::vector<int> findClosestElementsTest(std::vector<int> arr, int k, int x) {
  return findClosestElements(arr, k, x);
}

TEST(FindKClosest, duos) {
  EXPECT_THAT(
      findClosestElementsTest(std::vector<int>{1, 2, 3, 4, 5}, 4, 3), ElementsAre(1, 2, 3, 4));
  EXPECT_THAT(
      findClosestElementsTest(std::vector<int>{1, 2, 3, 4, 5}, 4, -1), ElementsAre(1, 2, 3, 4));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
