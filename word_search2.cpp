#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct TrieNode {
  TrieNode(char letter_) : letter{letter_}, word{""}, children{} {}

  char letter;
  std::string word;
  TrieNode* children[26];
};

void insertTrie(TrieNode* node, const std::string& word, int wordIndex) {
  assert(node != nullptr);

  if (wordIndex >= word.size()) {
    node->word = word;
    return;
  }

  char letter = word[wordIndex];
  char letterIndex = letter - 'a';
  if (node->children[letterIndex] == nullptr) {
    node->children[letterIndex] = new TrieNode(letter);
  }

  insertTrie(node->children[letterIndex], word, wordIndex + 1);
}

std::vector<std::string> findWords(
    std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
  int m = board.size();
  int n = board[0].size();

  TrieNode* root = new TrieNode('\0');
  for (const auto& word : words) {
    insertTrie(root, word, 0);
  }

  std::unordered_set<std::string> foundWords;
  // Finds all words that can be made starting from the given grid position that are contained in
  // the given trie subtree, adding them to foundWords.
  std::function<void(int, int, TrieNode*)> findWords;
  findWords = [&](int row, int column, TrieNode* node) {
    if (row < 0 || column < 0 || row >= m || column >= n) {
      return;
    }

    char letter = board[row][column];
    char letterIndex = letter - 'a';
    if (letter == '*') {
      // already visited, cannot use this cell
      return;
    }

    TrieNode* childNode = node->children[letterIndex];
    if (childNode == nullptr) {
      // trie finishes here, cannot find any more words
      return;
    }

    // add any found word
    if (!childNode->word.empty()) {
      foundWords.insert(childNode->word);
    }

    // Try continuing with neighboring grid cells
    board[row][column] = '*'; // mark cell as visited
    findWords(row + 1, column, childNode);
    findWords(row - 1, column, childNode);
    findWords(row, column + 1, childNode);
    findWords(row, column - 1, childNode);
    board[row][column] = letter; // restore cell state
  };

  for (int row = 0; row < m; row++) {
    for (int column = 0; column < n; column++) {
      findWords(row, column, root);
    }
  }

  return std::vector<std::string>{foundWords.begin(), foundWords.end()};
}

std::vector<std::string> findWordsTest(
    std::vector<std::vector<char>> board, std::vector<std::string> words) {
    return findWords(board, words);
}

TEST(WordSearch2, test) {
  ASSERT_THAT(
      findWordsTest(
          std::vector<std::vector<char>>{
              {'o', 'a', 'a', 'n'},
              {'e', 't', 'a', 'e'},
              {'i', 'h', 'k', 'r'},
              {'i', 'f', 'l', 'v'}},
          std::vector<std::string>{"oath", "pea", "eat", "rain"}),
      UnorderedElementsAre("eat", "oath"));
  ASSERT_THAT(
      findWordsTest(
          std::vector<std::vector<char>>{{'a', 'b'}, {'c', 'd'}}, std::vector<std::string>{"abcd"}),
      IsEmpty());
  ASSERT_THAT(
      findWordsTest(
          std::vector<std::vector<char>>{{'a', 'b'}, {'c', 'd'}},
          std::vector<std::string>{"abdca"}),
      IsEmpty());
  ASSERT_THAT(
      findWordsTest(
          std::vector<std::vector<char>>{{'a', 'b'}, {'c', 'd'}}, std::vector<std::string>{"abdc"}),
      UnorderedElementsAre("abdc"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
