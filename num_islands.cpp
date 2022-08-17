#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int numIslands(std::vector<std::vector<char>> grid) {
  if (grid.empty()) {
    return 0;
  }

  int rows = grid.size();
  int cols = grid[0].size();

  std::vector<bool> visited(rows * cols, false);
  std::function<void(int, int)> visit;
  visit = [&](int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
      return;
    }

    if (grid[row][col] == '0') {
      return;
    }

    int index = row * cols + col;
    if (visited[index]) {
      return;
    }

    visited[index] = true;

    visit(row - 1, col);
    visit(row, col - 1);
    visit(row + 1, col);
    visit(row, col + 1);
  };

  int islands = 0;
  for(int row = 0; row < rows; row++) {
    for(int col = 0; col < cols; col++) {
      int index = row * cols + col;
      if (visited[index] || grid[row][col] == '0') {
        continue;
      }

      islands++;
      visit(row, col);
    }
  }

  return islands;
}

TEST(NumIslands, test) {
  ASSERT_EQ(
      numIslands(std::vector<std::vector<char>>{
          {'1', '1', '1', '1', '0'},
          {'1', '1', '0', '1', '0'},
          {'1', '1', '0', '0', '0'},
          {'0', '0', '0', '0', '0'}}),
      1);
  ASSERT_EQ(
      numIslands(std::vector<std::vector<char>>{
          {'1', '1', '0', '0', '0'},
          {'1', '1', '0', '0', '0'},
          {'0', '0', '1', '0', '0'},
          {'0', '0', '0', '1', '1'}}),
      3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
