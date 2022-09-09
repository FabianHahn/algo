#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool exist(std::vector<std::vector<char>> board, std::string word) {
  int m = board.size();
  int n = board[0].size();

  std::unordered_map<char, std::vector<std::pair<int, int>>> letterPositions;
  for (int row = 0; row < m; row++) {
    for (int column = 0; column < n; column++) {
      char letter = board[row][column];
      letterPositions[letter].emplace_back(std::make_pair(row, column));
    }
  }

  // Returns true if we can spell the word from wordIndex to the end starting at (row, column).
  // Won't visit any grid cells in visited.
  std::function<bool(int, int, int, std::vector<bool>&)> canMakeWord;
  canMakeWord = [&](int row, int column, int wordIndex, std::vector<bool>& visited) {
    if (wordIndex == word.size()) {
      return true; // we can make the empty word from any board
    }
    if (row < 0 || column < 0 || row >= m || column >= n) {
      return false; // we cannot make a word with cells outside the grid
    }
    if (visited[row * n + column]) {
      return false; // we've already visited here, cannot use this cell
    }

    char letter = board[row][column];
    if (letter != word[wordIndex]) {
      return false;
    }

    visited[row * n + column] = true;
    if (canMakeWord(row + 1, column, wordIndex + 1, visited) ||
        canMakeWord(row - 1, column, wordIndex + 1, visited) ||
        canMakeWord(row, column + 1, wordIndex + 1, visited) ||
        canMakeWord(row, column - 1, wordIndex + 1, visited)) {
      return true;
    }
    visited[row * n + column] = false;
    return false;
  };

  const auto& startingPositions = letterPositions[word[0]];
  for (auto startingPosition : startingPositions) {
    int row = startingPosition.first;
    int column = startingPosition.second;

    std::vector<bool> visited(m * n, false);
    if (canMakeWord(row, column, 0, visited)) {
      return true;
    }
  }

  return false;
}

TEST(WordSearch, test) {
  ASSERT_TRUE(exist(
      std::vector<std::vector<char>>{
          {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
      "ABCCED"));
  ASSERT_TRUE(exist(
      std::vector<std::vector<char>>{
          {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
      "SEE"));
  ASSERT_FALSE(exist(
      std::vector<std::vector<char>>{
          {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
      "ABCB"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
