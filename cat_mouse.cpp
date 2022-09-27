#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

enum GameResult {
  kCanDraw,
  kMustLose,
  kCanWin,
  kUndecided,
};

int catMouseGame(std::vector<std::vector<int>> graph) {
  std::vector<std::optional<GameResult>> bestMouseTurnDp(50 * 50, std::nullopt);
  std::vector<std::optional<GameResult>> bestCatTurnDp(50 * 50, std::nullopt);
  std::vector<bool> bestMouseTurnRecursion(50 * 50, false);
  std::vector<bool> bestCatTurnRecursion(50 * 50, false);
  std::function<GameResult(int, int)> bestMouseTurn;
  std::function<GameResult(int, int)> bestCatTurn;
  bestMouseTurn = [&](int mouse, int cat) {
    if (mouse == cat) {
      return kMustLose;
    }
    int positionIndex = 50 * mouse + cat;
    if (bestMouseTurnRecursion[positionIndex]) {
      return kUndecided;
    }

    auto& dp = bestMouseTurnDp[positionIndex];
    if (dp) {
      return *dp;
    }
    bestMouseTurnRecursion[positionIndex] = true;

    GameResult bestMouseResult = kMustLose;
    for (int target : graph[mouse]) {
      if (target == cat) {
        continue;
      }

      GameResult bestCatResult = bestCatTurn(target, cat);
      if (bestCatResult == kMustLose) {
        bestMouseResult = kCanWin;
        break;
      }
      if (bestCatResult == kUndecided) {
        bestMouseResult = kUndecided;
      }
    }

    if (bestMouseResult != kUndecided) {
      //std::cout << "mouse " << mouse << ", cat " << cat << ": mouse "
      //          << (bestMouseResult == kMustLose ? "must lose" : "can win") << std::endl;
      dp = bestMouseResult;
    }
    bestMouseTurnRecursion[positionIndex] = false;
    return bestMouseResult;
  };

  bestCatTurn = [&](int mouse, int cat) {
    if (mouse == 0) {
      return kMustLose;
    }
    int positionIndex = 50 * mouse + cat;
    if (bestCatTurnRecursion[positionIndex]) {
      return kUndecided;
    }

    auto& dp = bestCatTurnDp[positionIndex];
    if (dp) {
      return *dp;
    }
    bestCatTurnRecursion[positionIndex] = true;

    GameResult bestCatResult = kMustLose;
    for (int target : graph[cat]) {
      if (target == 0) {
        continue;
      }

      GameResult bestMouseResult = bestMouseTurn(mouse, target);
      if (bestMouseResult == kMustLose) {
        bestCatResult = kCanWin;
        break;
      }
      if (bestMouseResult == kUndecided) {
        bestCatResult = kUndecided;
      }
    }

    if (bestCatResult != kUndecided) {
      //std::cout << "mouse " << mouse << ", cat " << cat << ": cat "
      //          << (bestCatResult == kMustLose ? "must lose" : "can win") << std::endl;
      dp = bestCatResult;
    }
    bestCatTurnRecursion[positionIndex] = false;
    return bestCatResult;
  };

  auto result = bestMouseTurn(1, 2);
  if (result == kCanWin) {
    return 1;
  } else if (result == kUndecided) {
    return 0;
  } else {
    return 2;
  }
}

TEST(CatMouse, test) {
  EXPECT_EQ(
      catMouseGame(std::vector<std::vector<int>>{
          {5, 6}, {3, 4}, {6}, {1, 4, 5}, {1, 3, 5}, {0, 3, 4, 6}, {0, 2, 5}}),
      2);
  EXPECT_EQ(
      catMouseGame(
          std::vector<std::vector<int>>{{2, 5}, {3}, {0, 4, 5}, {1, 4, 5}, {2, 3}, {0, 2, 3}}),
      0);
  EXPECT_EQ(catMouseGame(std::vector<std::vector<int>>{{1, 3}, {0}, {3}, {0, 2}}), 1);
  EXPECT_EQ(
      catMouseGame(std::vector<std::vector<int>>{
          {3, 4, 6, 7, 9, 15, 16, 18},
          {4, 5, 8, 19},
          {3, 4, 6, 9, 17, 18},
          {0, 2, 11, 15},
          {0, 1, 10, 6, 2, 12, 14, 16},
          {1, 10, 7, 9, 15, 17, 18},
          {0, 10, 4, 7, 9, 2, 11, 12, 13, 14, 15, 17, 19},
          {0, 10, 5, 6, 9, 16, 17},
          {1, 9, 14, 15, 16, 19},
          {0, 10, 5, 6, 7, 8, 2, 11, 13, 15, 16, 17, 18},
          {4, 5, 6, 7, 9, 18},
          {3, 6, 9, 12, 19},
          {4, 6, 11, 15, 17, 19},
          {6, 9, 15, 17, 18, 19},
          {4, 6, 8, 15, 19},
          {0, 3, 5, 6, 8, 9, 12, 13, 14, 16, 19},
          {0, 4, 7, 8, 9, 15, 17, 18, 19},
          {5, 6, 7, 9, 2, 12, 13, 16},
          {0, 10, 5, 9, 2, 13, 16},
          {1, 6, 8, 11, 12, 13, 14, 15, 16}}),
      1);
}

TEST(CatMouse, DISABLED_hard) {
  EXPECT_EQ(
      catMouseGame(std::vector<std::vector<int>>{
          {5, 21, 28},
          {6, 8, 9, 13, 23, 24, 30},
          {9, 10, 22, 24},
          {24, 30},
          {5, 6, 8, 9, 13, 18, 19, 20, 24},
          {0, 4, 9, 10, 11, 12, 22, 27},
          {1, 4, 9, 11, 16, 19, 25, 30},
          {8, 9, 13, 19, 25, 26},
          {1, 4, 7, 9, 29},
          {1, 2, 4, 5, 6, 7, 8, 13, 18, 19, 24, 26, 28, 29},
          {2, 5, 15, 22, 27, 30},
          {5, 6, 12, 24},
          {5, 11, 20, 22, 23},
          {1, 4, 7, 9, 29, 30},
          {19, 24, 27},
          {10, 16, 19},
          {6, 15, 27},
          {20, 22, 24, 29},
          {4, 9, 21},
          {4, 6, 7, 9, 14, 15, 20, 26, 28, 30},
          {4, 12, 17, 19, 21},
          {0, 18, 20, 27},
          {2, 5, 10, 12, 17},
          {1, 12, 26, 30},
          {1, 2, 3, 4, 9, 11, 14, 17, 27, 29},
          {6, 7, 26, 27, 29},
          {7, 9, 19, 23, 25},
          {5, 10, 14, 16, 21, 24, 25},
          {0, 9, 19, 30},
          {8, 9, 13, 17, 24, 25},
          {1, 3, 6, 10, 13, 19, 23, 28}}),
      1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
