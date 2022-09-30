#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;

std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
  std::vector<std::vector<int>> skyline;

  int n = buildings.size();
  auto compare = [&](int a, int b) {
    int aHeight = buildings[a][2];
    int bHeight = buildings[b][2];
    if (aHeight == bHeight) {
      return a < b;
    }
    return aHeight < bHeight;
  };
  std::set<int, decltype(compare)> activeBuildings(compare);
  auto eraseHighestActive = [&activeBuildings]() {
    auto lastIter = activeBuildings.end();
    lastIter--;
    activeBuildings.erase(lastIter);
  };

  using Event = std::tuple<int, int, int>;
  std::priority_queue<Event, std::vector<Event>, std::greater<>> queue;
  for (int i = 0; i < n; i++) {
    const auto& building = buildings[i];
    int buildingStart = building[0];
    int buildingEnd = building[1];
    queue.emplace(std::make_tuple(buildingStart, 0, i));
    queue.emplace(std::make_tuple(buildingEnd, 1, i));
  }

  while (!queue.empty()) {
    auto [eventPosition, isEnd, buildingIndex] = queue.top();
    queue.pop();

    const auto& building = buildings[buildingIndex];
    int buildingStart = building[0];
    int buildingEnd = building[1];
    int buildingHeight = building[2];

    if (eventPosition == buildingStart) {
      if (activeBuildings.empty()) {
        activeBuildings.insert(buildingIndex);
        skyline.emplace_back(std::vector<int>{buildingStart, buildingHeight});
        continue;
      }

      int topBuildingIndex = *activeBuildings.rbegin();
      const auto& topBuilding = buildings[topBuildingIndex];
      int topBuildingStart = topBuilding[0];
      int topBuildingEnd = topBuilding[1];
      int topBuildingHeight = topBuilding[2];

      if (buildingHeight > topBuildingHeight) {
        if (skyline.back()[0] == buildingStart) { // did we already place a skyline point here?
          // move it up
          skyline.back()[1] = buildingHeight;
        } else {
          skyline.emplace_back(std::vector<int>{buildingStart, buildingHeight});
        }
      }

      activeBuildings.insert(buildingIndex);
    } else {
      assert(!activeBuildings.empty());
      int topBuildingIndex = *activeBuildings.rbegin();

      if (buildingIndex != topBuildingIndex) {
        activeBuildings.erase(buildingIndex);
        continue;
      }

      // we are the highest building
      eraseHighestActive();
      if (activeBuildings.empty()) {
        if (skyline.back()[0] == buildingEnd) { // did we already place a skyline point here?
          // move it down
          skyline.back()[1] = 0;
        } else {
          skyline.emplace_back(std::vector<int>{buildingEnd, 0});
        }
        continue;
      }

      // take the next lower one
      int nextLowestBuildingIndex = *activeBuildings.rbegin();
      const auto& nextLowestBuilding = buildings[nextLowestBuildingIndex];
      int nextLowestBuildingStart = nextLowestBuilding[0];
      int nextLowestBuildingEnd = nextLowestBuilding[1];
      int nextLowestBuildingHeight = nextLowestBuilding[2];

      if (buildingHeight == nextLowestBuildingHeight) {
        // this building is as tall as we were and just continues the current skyline level
        continue;
      }

      if (skyline.back()[0] == buildingEnd) { // did we already place a skyline point here?
        // move it down
        skyline.back()[1] = nextLowestBuildingHeight;
      } else {
        skyline.emplace_back(std::vector<int>{buildingEnd, nextLowestBuildingHeight});
      }
    }
  }

  return skyline;
}

std::vector<std::vector<int>> getSkylineTest(std::vector<std::vector<int>> buildings) {
  return getSkyline(buildings);
}

TEST(Skyline, test) {
  EXPECT_THAT(
      getSkylineTest(std::vector<std::vector<int>>{{0, 4, 4}, {1, 4, 4}, {2, 4, 3}, {3, 4, 2}}),
      ElementsAre(std::vector<int>{0, 4}, std::vector<int>{4, 0}));
  EXPECT_THAT(
      getSkylineTest(std::vector<std::vector<int>>{{1, 5, 2}, {2, 4, 4}}),
      ElementsAre(
          std::vector<int>{1, 2},
          std::vector<int>{2, 4},
          std::vector<int>{4, 2},
          std::vector<int>{5, 0}));
  EXPECT_THAT(
      getSkylineTest(std::vector<std::vector<int>>{{0, 2, 3}, {2, 5, 3}}),
      ElementsAre(std::vector<int>{0, 3}, std::vector<int>{5, 0}));
  EXPECT_THAT(
      getSkylineTest(std::vector<std::vector<int>>{
          {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}}),
      ElementsAre(
          std::vector<int>{2, 10},
          std::vector<int>{3, 15},
          std::vector<int>{7, 12},
          std::vector<int>{12, 0},
          std::vector<int>{15, 10},
          std::vector<int>{20, 8},
          std::vector<int>{24, 0}));
  EXPECT_THAT(
      getSkylineTest(std::vector<std::vector<int>>{{1, 2, 1}, {1, 2, 2}, {1, 2, 3}}),
      ElementsAre(std::vector<int>{1, 3}, std::vector<int>{2, 0}));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
