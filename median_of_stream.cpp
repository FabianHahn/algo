#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

class MedianFinder {
public:
  MedianFinder() : median{numbers.end()}, isPlusOneHalf{true} {}

  void addNum(int num) {
    auto nextTree = tree.upper_bound(num);
    auto nextList = numbers.end();
    if (nextTree != tree.end()) {
      nextList = nextTree->second;
    }
    auto inserted = numbers.insert(nextList, num);
    tree.insert(std::make_pair(num, inserted));

    if (median == numbers.end()) {
      median = inserted;
    } else if (num >= *median && isPlusOneHalf) {
      ++median;
    } else if (num < *median && !isPlusOneHalf) {
      --median;
    }

    isPlusOneHalf = !isPlusOneHalf;
  }

  double findMedian() {
    if (isPlusOneHalf) {
      auto next = median;
      ++next;
      return 0.5 * (*median + *next);
    } else {
      return *median;
    }
  }

private:
  std::list<int> numbers;
  std::multimap<int, std::list<int>::iterator> tree;
  std::list<int>::iterator median;
  bool isPlusOneHalf;
};

TEST(MedianOfStream, Test) {
  MedianFinder medianFinder{};
  medianFinder.addNum(1);
  medianFinder.addNum(2);
  ASSERT_EQ(medianFinder.findMedian(), 1.5);
  medianFinder.addNum(3);
  ASSERT_EQ(medianFinder.findMedian(), 2.0);
  medianFinder.addNum(4);
  ASSERT_EQ(medianFinder.findMedian(), 2.5);
  medianFinder.addNum(1);
  ASSERT_EQ(medianFinder.findMedian(), 2.0);
  medianFinder.addNum(1);
  ASSERT_EQ(medianFinder.findMedian(), 1.5);
}

TEST(MedianOfStream, Test2) {
  MedianFinder medianFinder{};
  medianFinder.addNum(6);
  ASSERT_EQ(medianFinder.findMedian(), 6.0);
  medianFinder.addNum(10);
  ASSERT_EQ(medianFinder.findMedian(), 8.0);
  medianFinder.addNum(2);
  ASSERT_EQ(medianFinder.findMedian(), 6.0);
  medianFinder.addNum(6);
  ASSERT_EQ(medianFinder.findMedian(), 6.0);
  medianFinder.addNum(5);
  ASSERT_EQ(medianFinder.findMedian(), 6.0);
  medianFinder.addNum(0);
  ASSERT_EQ(medianFinder.findMedian(), 5.5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
