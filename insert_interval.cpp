#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;

bool overlaps(const std::vector<int>& a, const std::vector<int>& b) {
  return a[0] >= b[0] && a[0] <= b[1] || b[0] >= a[0] && b[0] <= a[1];
}

void merge(std::vector<int>& newInterval, const std::vector<int>& extension) {
  assert(overlaps(newInterval, extension));

  if (extension[0] < newInterval[0]) {
    newInterval[0] = extension[0];
  }
  if (extension[1] > newInterval[1]) {
    newInterval[1] = extension[1];
  }
}

std::vector<std::vector<int>> insert(
    std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
  int& lo = newInterval[0];
  int& hi = newInterval[1];

  auto firstPotentiallyAffected = std::partition_point(
      intervals.begin(), intervals.end(), [&](const std::vector<int>& interval) {
        return interval[1] < lo;
      });
  auto firstUnaffected = std::partition_point(
      intervals.begin(), intervals.end(), [&](const std::vector<int>& interval) {
        return interval[0] <= hi;
      });
  auto range = std::equal_range(
      intervals.begin(),
      intervals.end(),
      newInterval,
      [](const std::vector<int>& a, const std::vector<int>& b) { return a[1] < b[0]; });
  assert(range.first == firstPotentiallyAffected);
  assert(range.second == firstUnaffected);

  for (auto iter = firstPotentiallyAffected; iter < firstUnaffected; iter++) {
    auto& current = *iter;

    if (overlaps(current, newInterval)) {
      merge(newInterval, current);
    }
  }

  std::vector<std::vector<int>> result;
  std::copy(intervals.begin(), firstPotentiallyAffected, std::back_inserter(result));
  result.push_back(newInterval);
  std::copy(firstUnaffected, intervals.end(), std::back_inserter(result));

  return result;
}

TEST(InsertIntervals, test) {
  std::vector<std::vector<int>> intervals;
  intervals.emplace_back(std::vector<int>{1, 2});
  intervals.emplace_back(std::vector<int>{3, 5});
  intervals.emplace_back(std::vector<int>{6, 7});
  intervals.emplace_back(std::vector<int>{8, 10});
  intervals.emplace_back(std::vector<int>{12, 16});

  std::vector<int> newInterval{4, 8};
  ASSERT_THAT(
      insert(intervals, newInterval),
      ElementsAre(ElementsAre(1, 2), ElementsAre(3, 10), ElementsAre(12, 16)));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
