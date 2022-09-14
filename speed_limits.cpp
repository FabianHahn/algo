#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int speedLimits(int n, int c, std::vector<std::vector<int>> roads) {
  std::sort(
      roads.begin(), roads.end(), [](const std::vector<int>& road1, const std::vector<int>& road2) {
        return road1[2] > road2[2];
      });

  std::vector<std::vector<std::pair<int, int>>> adjacency(n + 1);
  for (int j = 0; j < roads.size(); j++) {
    const auto& road = roads[j];
    adjacency[road[0]].emplace_back(std::make_pair(road[1], j));
    adjacency[road[1]].emplace_back(std::make_pair(road[0], j));
  }

  auto speedLimit = [&](int roadIndex) { return roads[roadIndex][2]; };
  auto nodeStats = [&](int nodeIndex) {
    int maxSpeed = INT_MIN;
    bool uneven = false;
    for (const auto& neighbor : adjacency[nodeIndex]) {
      int speed = speedLimit(neighbor.second);
      if (maxSpeed > INT_MIN && speed != maxSpeed) {
        uneven = true;
      }

      if (speed > maxSpeed) {
        maxSpeed = speed;
      }
    }

    return std::make_pair(maxSpeed, uneven);
  };
  auto nodeCost = [&](int nodeIndex) -> int {
    if (adjacency[nodeIndex].size() <= 1) {
      return 0;
    }

    auto [maxSpeed, uneven] = nodeStats(nodeIndex);
    if (uneven) {
      return c * adjacency[nodeIndex].size();
    } else {
      return 0;
    }
  };
  auto totalNodeCost = [&]() {
    int totalCost = 0;
    for (int i = 0; i < n; i++) {
      totalCost += nodeCost(i);
    }

    return totalCost;
  };

  auto upgrade = [&](int roadIndex, int newSpeed, bool costOnly = false) {
    int oldSpeed = speedLimit(roadIndex);
    if (oldSpeed == newSpeed) {
      return 0;
    }

    int costDifference = newSpeed - oldSpeed; // cost of upgrading road itself

    costDifference -= nodeCost(roads[roadIndex][0]);
    costDifference -= nodeCost(roads[roadIndex][1]);
    roads[roadIndex][2] = newSpeed;
    costDifference += nodeCost(roads[roadIndex][0]);
    costDifference += nodeCost(roads[roadIndex][1]);
    if (costOnly) {
      roads[roadIndex][2] = oldSpeed;
    }
    return costDifference;
  };

#if 0
  for (int j = 0; j < roads.size(); j++) {
    int sourceNode = roads[j][0];
    int targetNode = roads[j][1];
    int oldSpeed = roads[j][2];

    auto [sourceMaxSpeed, sourceUneven] = nodeStats(sourceNode);
    auto [targetMaxSpeed, targetUneven] = nodeStats(targetNode);

    int changeSourceDifference = 0;
    if (oldSpeed < sourceMaxSpeed) {
      changeSourceDifference = upgrade(j, sourceMaxSpeed, /* costOnly */ true);
    }

    int changeTargetDifference = 0;
    if (oldSpeed < targetMaxSpeed) {
      changeTargetDifference = upgrade(j, targetMaxSpeed, /* costOnly */ true);
    }

    if (changeSourceDifference < 0 && changeSourceDifference < changeTargetDifference) {
      roads[j][2] = sourceMaxSpeed;
      cost += changeSourceDifference;
    }
    if (changeTargetDifference < 0 && changeTargetDifference < changeSourceDifference) {
      roads[j][2] = targetMaxSpeed;
      cost += changeTargetDifference;
    }
  }
#endif

  auto greedy = [&](int startingNodeIndex) {
    int cost = totalNodeCost();
    auto oldRoads = roads;

    std::deque<std::pair<int, int>> queue{std::make_pair(startingNodeIndex, -1)};
    while (!queue.empty()) {
      auto [targetNodeIndex, sourceNodeIndex] = queue.front();
      queue.pop_front();

      auto [targetMaxSpeed, targetUneven] = nodeStats(targetNodeIndex);
      int costDifference = 0;
      if (targetUneven) {
        std::deque<int> previousSpeeds;
        for (auto [neighborNodeIndex, roadIndex] : adjacency[targetNodeIndex]) {
          previousSpeeds.push_back(speedLimit(roadIndex));
          costDifference += upgrade(roadIndex, targetMaxSpeed);
        }

        if (costDifference > 0) {
          // not worth it, restore old speeds
          for (auto [neighborNodeIndex, roadIndex] : adjacency[targetNodeIndex]) {
            roads[roadIndex][2] = previousSpeeds.front();
            previousSpeeds.pop_front();
          }
        } else {
          cost += costDifference;
        }
      }

      for (auto [neighborNodeIndex, roadIndex] : adjacency[targetNodeIndex]) {
        if (neighborNodeIndex != sourceNodeIndex) {
          queue.emplace_back(std::make_pair(neighborNodeIndex, targetNodeIndex));
        }
      }
    }

    roads = oldRoads;
    return cost;
  };

  int bestCost = INT_MAX;
  for (int i = 1; i <= n; i++) {
    int cost = greedy(i);
    if (cost < bestCost) {
      bestCost = cost;
    }
  }

  return bestCost;
}

TEST(SpeedLimits, test) {
  EXPECT_EQ(
      speedLimits(5, 2, std::vector<std::vector<int>>{{1, 2, 10}, {1, 3, 5}, {1, 4, 7}, {2, 5, 9}}),
      7);
  EXPECT_EQ(
      speedLimits(
          5, 100, std::vector<std::vector<int>>{{1, 2, 10}, {1, 3, 5}, {1, 4, 7}, {2, 5, 9}}),
      9);
  EXPECT_EQ(
      speedLimits(
          6,
          100,
          std::vector<std::vector<int>>{{1, 2, 3}, {2, 3, 2}, {3, 4, 1}, {3, 5, 2}, {3, 6, 2}}),
      5);
  EXPECT_EQ(
      speedLimits(
          6,
          3,
          std::vector<std::vector<int>>{{1, 2, 10}, {2, 3, 2}, {3, 4, 1}, {3, 5, 2}, {3, 6, 2}}),
      7);
  EXPECT_EQ(
      speedLimits(
          13,
          20,
          std::vector<std::vector<int>>{
              {1, 8, 101},
              {1, 9, 30},
              {1, 2, 100},
              {1, 3, 100},
              {2, 4, 75},
              {2, 5, 70},
              {2, 6, 82},
              {2, 7, 77},
              {3, 10, 73},
              {3, 11, 69},
              {3, 12, 83},
              {3, 13, 79}}),
      272);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
