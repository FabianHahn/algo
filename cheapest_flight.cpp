#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
  std::vector<std::vector<std::pair<int, int>>> adjacency(n);
  for (const auto& flight : flights) {
    adjacency[flight[0]].emplace_back(std::make_pair(flight[1], flight[2]));
  }

  std::vector<int> distances(n, INT_MAX);
  std::vector<int> nextDistances(n, INT_MAX);
  distances[src] = 0;
  std::deque<int> queue{src};
  std::deque<int> nextQueue;
  for (int i = 0; i <= k; i++) {
    nextDistances = distances;

    while (!queue.empty()) {
      int next = queue.front();
      queue.pop_front();

      int distance = distances[next];

      for (const auto& [to, price] : adjacency[next]) {
        if (distance + price < nextDistances[to]) {
          nextDistances[to] = distance + price;
          nextQueue.emplace_back(to);
        }
      }
    }

    std::swap(nextQueue, queue);
    std::swap(nextDistances, distances);
  }

  if (distances[dst] == INT_MAX) {
    return -1;
  }

  return distances[dst];
}

int findCheapestPriceTest(int n, std::vector<std::vector<int>> flights, int src, int dst, int k) {
  return findCheapestPrice(n, flights, src, dst, k);
}

TEST(CheapestFlight, test) {
  EXPECT_EQ(
      findCheapestPriceTest(
          5,
          std::vector<std::vector<int>>{
              {0, 1, 5}, {1, 2, 5}, {0, 3, 2}, {3, 1, 2}, {1, 4, 1}, {4, 2, 1}},
          0,
          2,
          2),
      7);
  EXPECT_EQ(
      findCheapestPriceTest(
          4,
          std::vector<std::vector<int>>{
              {0, 1, 1}, {0, 2, 5}, {1, 2, 1}, {2, 3, 1}},
          0,
          3,
          1),
      700);
  EXPECT_EQ(
      findCheapestPriceTest(
          4,
          std::vector<std::vector<int>>{
              {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}},
          0,
          3,
          1),
      6);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
