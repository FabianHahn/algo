#include <gtest/gtest.h>

#include <vector>

double computeMedian(const std::vector<int>& nums, std::size_t middleIndex, bool isAverage) {
  if (isAverage) {
    return 0.5 * (nums[middleIndex] + nums[middleIndex - 1]);
  } else {
    return nums[middleIndex];
  }
}

double findMedianSortedArray(const std::vector<int>& nums) {
  std::size_t size = nums.size();

  if (size == 1) {
    return nums[0];
  }

  std::size_t middleIndex = size / 2;
  bool isAverage = size % 2 == 0;
  return computeMedian(nums, middleIndex, isAverage);
}

// o(log n)
std::size_t findFirstElementLargerEqualThan(const std::vector<int>& nums, int value) {
  auto iter = std::lower_bound(nums.begin(), nums.end(), value);
  return iter - nums.begin();
}

int findElementKInSortedArrays(std::vector<int>& numsA, std::vector<int>& numsB, size_t k) {
  std::size_t m = numsA.size();
  std::size_t n = numsB.size();
  std::size_t x = findFirstElementLargerEqualThan(numsA, numsB[0]);

  if (k <= x) {
    return numsA[k];
  }

  if (numsB.back() > numsA.back()) {
    std::size_t y = findFirstElementLargerEqualThan(numsB, numsA.back());
    std::size_t yPosition = y + m;

    if (k >= yPosition) {
      return numsB[y + k - yPosition];
    }
  } else {
    std::size_t y = findFirstElementLargerEqualThan(numsA, numsB.back());
    std::size_t yPosition = y + n;

    if (k >= yPosition) {
      return numsA[y + k - yPosition];
    }
  }

  return -1;
}

// o(log m + log n)
std::size_t findElementPositionInSortedArrays(
    const std::vector<int>& numsA, const std::vector<int>& numsB, int element) {
  std::size_t x = findFirstElementLargerEqualThan(numsA, element);
  std::size_t y = findFirstElementLargerEqualThan(numsB, element);
  return x + y;
}

int findKthElementInSortedArrays(
    const std::vector<int>& numsA, const std::vector<int>& numsB, std::size_t k) {
  std::size_t currentMinA = 0;
  std::size_t currentMaxA = numsA.size();
  while (currentMaxA - currentMinA > 0) {
    std::size_t currentIndexA = currentMinA + (currentMaxA - currentMinA) / 2;
    int currentElement = numsA[currentIndexA];
    std::size_t currentRankA = findElementPositionInSortedArrays(numsA, numsB, currentElement);
    if (currentRankA == k) {
      return currentElement;
    }
    if (currentRankA < k) {
      if (currentIndexA == currentMinA) {
        break;
      }
      currentMinA = currentIndexA;
    } else {
      if (currentIndexA == currentMaxA) {
        break;
      }
      currentMaxA = currentIndexA;
    }
  }

  std::size_t currentMinB = 0;
  std::size_t currentMaxB = numsB.size();
  while (currentMaxB - currentMinB > 0) {
    std::size_t currentIndexB = currentMinB + (currentMaxB - currentMinB) / 2;
    int currentElement = numsB[currentIndexB];
    std::size_t currentRankB = findElementPositionInSortedArrays(numsA, numsB, currentElement);
    if (currentRankB == k) {
      return currentElement;
    }
    if (currentRankB < k) {
      if (currentIndexB == currentMinB) {
        break;
      }
      currentMinB = currentIndexB;
    } else {
      if (currentIndexB == currentMaxB) {
        break;
      }
      currentMaxB = currentIndexB;
    }
  }

  if (numsA[currentMinA] > numsB[currentMinB]) {
    return numsA[currentMinA];
  } else {
    return numsB[currentMinB];
  }
}

double findMedianSortedArrays(const std::vector<int>& numsA, const std::vector<int>& numsB) {
  if (numsA.empty()) {
    return findMedianSortedArray(numsB);
  }
  if (numsB.empty()) {
    return findMedianSortedArray(numsA);
  }

  std::size_t size = numsA.size() + numsB.size();
  std::size_t middleIndex = size / 2;
  bool isAverage = size % 2 == 0;

  int kth = findKthElementInSortedArrays(numsA, numsB, middleIndex);
  if (isAverage) {
    int kprevth = findKthElementInSortedArrays(numsA, numsB, middleIndex - 1);
    return 0.5 * (kth + kprevth);
  } else {
    return kth;
  }
}

double findMedianSortedArrays2(const std::vector<int>& numsA, const std::vector<int>& numsB) {
  if (numsA.empty()) {
    return findMedianSortedArray(numsB);
  }
  if (numsB.empty()) {
    return findMedianSortedArray(numsA);
  }

  std::size_t currentMinA = 0;
  std::size_t currentMaxA = numsA.size();
  std::size_t currentMinB = 0;
  std::size_t currentMaxB = numsB.size();
  std::size_t currentSizeA = numsA.size();
  std::size_t currentSizeB = numsB.size();
  std::size_t currentHalfSizeA = currentSizeA / 2;
  std::size_t currentHalfSizeB = currentSizeB / 2;
  bool isAverageA = currentSizeA % 2 == 0;
  bool isAverageB = currentSizeB % 2 == 0;
  while (currentSizeA > 1 && currentSizeB > 1) {
    currentSizeA = currentMaxA - currentMinA;
    currentSizeB = currentMaxB - currentMinB;
    currentHalfSizeA = currentSizeA / 2;
    currentHalfSizeB = currentSizeB / 2;
    isAverageA = currentSizeA % 2 == 0;
    isAverageB = currentSizeB % 2 == 0;
    std::size_t currentMedianIndexA = currentMinA + currentHalfSizeA;
    std::size_t currentMedianIndexB = currentMinB + currentHalfSizeB;
    double currentMedianA = computeMedian(numsA, currentMedianIndexA, isAverageA);
    double currentMedianB = computeMedian(numsB, currentMedianIndexB, isAverageB);

    if (currentMedianA <= currentMedianB) {
      if (currentHalfSizeA <= currentHalfSizeB) {
        currentMinA += currentHalfSizeA;
        currentMaxB -= currentHalfSizeA;
      } else {
        currentMinA += currentHalfSizeB;
        currentMaxB -= currentHalfSizeB;
      }
    } else {
      if (currentHalfSizeA <= currentHalfSizeB) {
        currentMaxA -= currentHalfSizeA;
        currentMinB += currentHalfSizeA;
      } else {
        currentMaxA -= currentHalfSizeB;
        currentMinB += currentHalfSizeB;
      }
    }
  }

  if (currentSizeA == 1 && currentSizeB == 1) {
    return 0.5 * (numsA[currentMinA] + numsB[currentMinB]);
  }

  if (currentSizeA == 1) {
    std::size_t x = findFirstElementLargerEqualThan(numsB, numsA[currentMinA]);
    auto 

    if (isAverageB) {

    }


    if (isAverageB == 0) {
      if (x == currentHalfSizeB) {
        return numsA[currentMinA];
      } else if (x < currentHalfSizeB) {
        return numsB[currentMinB + currentHalfSizeB - 1];
      } else {
        return numsB[currentMinB + currentHalfSizeB];
      }
    } else {
      if (x < currentHalfSizeB) {
        return 0.5 * (numsB[currentHalfSizeB] + numsB[currentHalfSizeB - 1]);
      } else if (x == currentHalfSizeB)
    }
  } else {
    if (isAverageA == 0) {
      std::size_t x = findFirstElementLargerEqualThan(numsA, numsB[currentMinB]);
      if (x == currentHalfSizeA) {
        return numsB[currentMinB];
      } else if (x < currentHalfSizeA) {
        return numsA[currentMinA + currentHalfSizeA - 1];
      } else {
        return numsA[currentMinA + currentHalfSizeA];
      }
    }
  }
}

TEST(Leetcode4, bisect) {
  std::vector<int> a{1, 3, 4, 5, 8};
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 0), 0);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 1), 0);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 2), 1);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 3), 1);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 4), 2);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 5), 3);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 6), 4);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 7), 4);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 8), 4);
  ASSERT_EQ(findFirstElementLargerEqualThan(a, 9), 5);
}

TEST(Leetcode4, findKTrivialHighA) {
  std::vector<int> a{2, 3, 5, 10, 12};
  std::vector<int> b{3, 3, 3, 3, 7};

  ASSERT_EQ(findElementKInSortedArrays(a, b, 0), 2);
  ASSERT_EQ(findElementKInSortedArrays(a, b, 1), 3);
  ASSERT_EQ(findElementKInSortedArrays(a, b, 8), 10);
  ASSERT_EQ(findElementKInSortedArrays(a, b, 9), 12);
}

TEST(Leetcode4, findKTrivialHighB) {
  std::vector<int> a{2, 3, 3, 3, 3, 7};
  std::vector<int> b{3, 5, 10, 12};

  ASSERT_EQ(findElementKInSortedArrays(a, b, 0), 2);
  ASSERT_EQ(findElementKInSortedArrays(a, b, 1), 3);
  ASSERT_EQ(findElementKInSortedArrays(a, b, 8), 10);
  ASSERT_EQ(findElementKInSortedArrays(a, b, 9), 12);
}

TEST(Leetcode4, findElementPositionHighA) {
  std::vector<int> a{2, 3, 5, 10, 12};
  std::vector<int> b{3, 3, 3, 3, 7};

  ASSERT_EQ(findElementPositionInSortedArrays(a, b, 2), 0);
  ASSERT_EQ(findElementPositionInSortedArrays(a, b, 3), 1);
  ASSERT_EQ(findElementPositionInSortedArrays(a, b, 5), 6);
  ASSERT_EQ(findElementPositionInSortedArrays(a, b, 7), 7);
  ASSERT_EQ(findElementPositionInSortedArrays(a, b, 10), 8);
  ASSERT_EQ(findElementPositionInSortedArrays(a, b, 12), 9);
}

TEST(Leetcode4, findKthHighA) {
  std::vector<int> a{2, 3, 5, 10, 12};
  std::vector<int> b{3, 3, 3, 3, 7};

  ASSERT_EQ(findKthElementInSortedArrays(a, b, 0), 2);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 1), 3);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 2), 3);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 3), 3);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 4), 3);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 5), 3);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 6), 5);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 7), 7);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 8), 10);
  ASSERT_EQ(findKthElementInSortedArrays(a, b, 9), 12);
}

TEST(Leetcode4, median) {
  ASSERT_EQ(
      findMedianSortedArrays(std::vector<int>{2, 3, 5, 10, 12}, std::vector<int>{3, 3, 3, 3, 7}),
      3);
  ASSERT_EQ(
      findMedianSortedArrays(std::vector<int>{2, 3, 5, 10, 12}, std::vector<int>{3, 3, 3, 7}), 3);
  ASSERT_EQ(
      findMedianSortedArrays(std::vector<int>{2, 3, 5, 10, 12}, std::vector<int>{3, 3, 7}), 4);
  ASSERT_EQ(findMedianSortedArrays(std::vector<int>{2, 3, 5, 10, 12}, std::vector<int>{3, 7}), 5);
  ASSERT_EQ(findMedianSortedArrays(std::vector<int>{2, 3, 5, 10, 12}, std::vector<int>{7}), 6);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
