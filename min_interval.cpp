#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::SizeIs;

struct IntervalTreeNode {
  IntervalTreeNode(int d = INT_MIN)
      : delimiter{d},
        hasPoint{false},
        shortestMin{INT_MIN},
        shortestMax{INT_MAX},
        left{nullptr},
        right{nullptr} {}

  IntervalTreeNode* left;
  IntervalTreeNode* right;
  int delimiter;
  int shortestMin;
  int shortestMax;
  bool hasPoint;
};

IntervalTreeNode* createSubtree(const std::vector<int>& delimiters, int lo, int hi) {
  if (lo >= hi) {
    return new IntervalTreeNode();
  }

  int size = hi - lo;
  int halfSize = size / 2;
  int mid = lo + halfSize;

  IntervalTreeNode* node = new IntervalTreeNode(delimiters[mid]);
  node->left = createSubtree(delimiters, lo, mid);
  node->right = createSubtree(delimiters, mid + 1, hi);
  return node;
}

bool insertInterval(IntervalTreeNode* node, const std::vector<int>& interval, int lo, int hi) {
  if (node == nullptr) {
    return false;
  }

  if (lo >= interval[0] && hi <= interval[1]) {
    if (node->shortestMin == INT_MIN) {
      node->shortestMin = interval[0];
      node->shortestMax = interval[1];
    } else {
      int intervalSize = interval[1] - interval[0] + 1;
      int nodeIntervalSize = node->shortestMax - node->shortestMin + 1;
      if (intervalSize < nodeIntervalSize) {
        node->shortestMin = interval[0];
        node->shortestMax = interval[1];
      }
    }
    return true;
  }

  if (node->left == nullptr && node->right == nullptr) {
    return false;
  }

  if (interval[0] < node->delimiter) {
    if (!insertInterval(node->left, interval, lo, node->delimiter)) {
      return false;
    }
  }

  if (interval[1] > node->delimiter) {
    if (!insertInterval(node->right, interval, node->delimiter, hi)) {
      return false;
    }
  }

  if (interval[0] == node->delimiter && interval[1] == node->delimiter) {
    node->hasPoint = true;
  }

  return true;
}

void findIntervals(
    IntervalTreeNode* node, int query, int lo, int hi, std::vector<std::vector<int>>& intervals) {
  if (node == nullptr) {
    return;
  }

  if (query >= lo && query <= hi && node->shortestMin > INT_MIN) {
    intervals.emplace_back(std::vector<int>{node->shortestMin, node->shortestMax});
  }

  if (node->left != nullptr || node->right != nullptr) {
    if (query == node->delimiter && node->hasPoint) {
      intervals.emplace_back(std::vector<int>{query, query});
    }

    if (query <= node->delimiter) {
      findIntervals(node->left, query, lo, node->delimiter, intervals);
    }
    if (query >= node->delimiter) {
      findIntervals(node->right, query, node->delimiter, hi, intervals);
    }
  }
}

std::vector<int> minInterval(std::vector<std::vector<int>>& intervals, std::vector<int>& queries) {
  std::set<int> delimitersSet;
  for (const auto& interval : intervals) {
    delimitersSet.insert(interval[0]);
    delimitersSet.insert(interval[1]);
  }

  std::vector<int> delimiters(delimitersSet.begin(), delimitersSet.end());
  IntervalTreeNode* root = createSubtree(delimiters, 0, delimiters.size());
  for (const auto& interval : intervals) {
    bool inserted = insertInterval(root, interval, delimiters.front(), delimiters.back());
    assert(inserted);
  }

  std::vector<int> result;
  std::vector<std::vector<int>> queryResults;
  for (int query : queries) {
    queryResults.clear();
    findIntervals(root, query, delimiters.front(), delimiters.back(), queryResults);

    int bestSize = INT_MAX;
    for (const auto& interval : queryResults) {
      int intervalSize = interval[1] - interval[0] + 1;
      if (intervalSize < bestSize) {
        bestSize = intervalSize;
      }
    }

    if (bestSize < INT_MAX) {
      result.emplace_back(bestSize);
    } else {
      result.emplace_back(-1);
    }
  }
  return result;
}

std::vector<int> minIntervalTest(
    std::vector<std::vector<int>> intervals, std::vector<int> queries) {
  return minInterval(intervals, queries);
}

TEST(MinInterval, Test) {
  EXPECT_THAT(
      minIntervalTest(
          std::vector<std::vector<int>>{{1, 4}, {2, 4}, {3, 6}, {4, 4}},
          std::vector<int>{2, 3, 4, 5}),
      ElementsAre(3, 3, 1, 4));
  EXPECT_THAT(
      minIntervalTest(
          std::vector<std::vector<int>>{{2, 3}, {2, 5}, {1, 8}, {20, 25}},
          std::vector<int>{2, 19, 5, 22}),
      ElementsAre(2, -1, 4, 6));
}

TEST(MinInterval, Big) {
  std::ifstream intervalsFile("intervals.txt");
  std::vector<std::vector<int>> intervals;
  int lo;
  int hi;
  while (intervalsFile >> lo) {
    intervalsFile >> hi;
    intervals.push_back(std::vector<int>{lo, hi});
  }

  std::ifstream queriesFile("queries.txt");
  std::vector<int> queries;
  int q;
  while (queriesFile >> q) {
    queries.push_back(q);
  }

  auto result = minIntervalTest(intervals, queries);
  ASSERT_THAT(result, SizeIs(queries.size()));
  std::set<int> resultNumbers(result.begin(), result.end());
  ASSERT_THAT(
      resultNumbers,
      ElementsAre(4980285, 4980600, 4981315, 4982204, 4983049, 4985773, 4985809, 4985863, 4989029));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
