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

class MedianFinderTwoHeap {
public:
  MedianFinderTwoHeap(): init{true}, maxHeap{}, minHeap{} {}

  void addNum(int num) {
    if (init) {
      median1 = num;
      init = false;
      isPlusOneHalf = false;
      return;
    }

    if (num < median1) {
      maxHeap.push_back(num);
      std::push_heap(maxHeap.begin(), maxHeap.end());

      if (isPlusOneHalf) {
        minHeap.push_back(median2);
        std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>{});
        isPlusOneHalf = false;
      } else {
        median2 = median1;
        median1 = maxHeap[0];
        std::pop_heap(maxHeap.begin(), maxHeap.end());
        maxHeap.pop_back();
        isPlusOneHalf = true;
      }
    } else if (!isPlusOneHalf) {
      minHeap.push_back(num);
      std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>{});
      median2 = minHeap[0];
      std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<int>{});
      minHeap.pop_back();
      isPlusOneHalf = true;
    } else if (num < median2) {
      maxHeap.push_back(median1);
      std::push_heap(maxHeap.begin(), maxHeap.end());
      minHeap.push_back(median2);
      std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>{});
      median1 = num;
      isPlusOneHalf = false;
    } else {
      assert(isPlusOneHalf && num >= median2);
      maxHeap.push_back(median1);
      std::push_heap(maxHeap.begin(), maxHeap.end());
      minHeap.push_back(num);
      std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>{});
      median1 = median2;
      isPlusOneHalf = false;
    }
  }

  double findMedian() {
    if (isPlusOneHalf) {
      return 0.5 * (median1 + median2);
    } else {
      return median1;
    }
  }

private:
  bool init;
  std::vector<int> maxHeap;
  std::vector<int> minHeap;
  int median1;
  int median2;
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

TEST(MedianOfStream, TestTwoHeap) {
  MedianFinderTwoHeap medianFinder{};
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

TEST(MedianOfStream, TestTwoHeap2) {
  MedianFinderTwoHeap medianFinder{};
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
