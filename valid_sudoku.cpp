#include <gtest/gtest.h>

#include <vector>

bool isValidSudoku(std::vector<std::vector<char>>& board) {
  auto updateFilled = [](std::vector<bool>& filled, char entry) {
    int number = 0;
    if (entry >= '1' && entry <= '9') {
      number = entry - '1' + 1;
    }

    if (number > 0) {
      if (filled[number]) {
        return false;
      }
      filled[number] = true;
    }

    return true;
  };

  for (int i = 0; i < 9; i++) {
    std::vector<bool> filled(10, false);
    for (int j = 0; j < 9; j++) {
      if (!updateFilled(filled, board[i][j])) {
        return false;
      }
    }
  }

  for (int j = 0; j < 9; j++) {
    std::vector<bool> filled(10, false);
    for (int i = 0; i < 9; i++) {
      if (!updateFilled(filled, board[i][j])) {
        return false;
      }
    }
  }

  std::vector<std::pair<int, int>> offsets{
      {0, 0}, {3, 0}, {6, 0}, {0, 3}, {3, 3}, {6, 3}, {0, 6}, {3, 6}, {6, 6}};
  for (auto offset : offsets) {
    std::vector<bool> filled(10, false);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (!updateFilled(filled, board[offset.first + i][offset.second + j])) {
          return false;
        }
      }
    }
  }

  return true;
}

TEST(ValidSudoku, validRow) {
  std::vector<std::vector<char>> board{
      {'5', '3', '2', '1', '4', '8', '6', '7', '9'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'}};

  ASSERT_TRUE(isValidSudoku(board));
}

TEST(ValidSudoku, invalidRow) {
  std::vector<std::vector<char>> board{
      {'5', '3', '2', '1', '4', '5', '6', '7', '9'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.'}};

  ASSERT_FALSE(isValidSudoku(board));
}

TEST(ValidSudoku, valid) {
  std::vector<std::vector<char>> board{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  ASSERT_TRUE(isValidSudoku(board));
}

TEST(ValidSudoku, invalid) {
  std::vector<std::vector<char>> board{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '3', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  ASSERT_FALSE(isValidSudoku(board));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
