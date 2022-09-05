#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;

std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
  int n = nums.size();
  std::deque<int> queue{};
  std::vector<int> result;
  for (int i = 0; i < n; i++) {
    int next = nums[i];

    while (!queue.empty() && next > queue.back()) {
      queue.pop_back();
    }
    queue.push_back(next);

    if (i < k - 1) {
      continue;
    }
    if (i == k - 1) {
      result.push_back(queue.front());
      continue;
    }

    int oldest = nums[i - k];
    if (oldest == queue.front()) {
      queue.pop_front();
    }

    result.push_back(queue.front());
  }

  return result;
}

TEST(SlidingWindowMax, Test) {
  EXPECT_THAT(
      maxSlidingWindow(std::vector<int>{1, 3, -1, -3, 5, 3, 6, 7}, 3),
      ElementsAre(3, 3, 5, 5, 6, 7));
  EXPECT_THAT(
      maxSlidingWindow(std::vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, 3),
      ElementsAre(9, 8, 7, 6, 5, 4, 3));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
