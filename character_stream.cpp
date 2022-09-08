#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct TrieNode {
  TrieNode(TrieNode* parent_, char c_)
      : c{c_}, isWord{false}, parent{parent_}, children{}, longestSuffix{nullptr} {}

  char c;
  bool isWord;
  TrieNode* parent;
  TrieNode* children[26];
  TrieNode* longestSuffix;
  std::vector<TrieNode*> wordSuffixes;
};

void insertTrie(TrieNode* node, const std::string& word, int index) {
  assert(node != nullptr);
  assert(index >= 0);

  if (index == word.size()) {
    node->isWord = true;
    return;
  }

  char c = word[index];
  char childIndex = c - 'a';

  if (node->children[childIndex] == nullptr) {
    node->children[childIndex] = new TrieNode(node, c);
  }

  insertTrie(node->children[childIndex], word, index + 1);
}

void findLongestSuffixes(TrieNode* root) {
  root->longestSuffix = root;

  std::deque<TrieNode*> queue{root};
  while (!queue.empty()) {
    TrieNode* node = queue.front();
    queue.pop_front();

    char childIndex = node->c - 'a';

    TrieNode* current = node->parent;
    node->longestSuffix = root;
    while (current != nullptr && current != root) {
      if (current->longestSuffix->children[childIndex] != nullptr) {
        node->longestSuffix = current->longestSuffix->children[childIndex];
        break;
      }
      current = current->longestSuffix;
    }

    if (node->longestSuffix->isWord) {
      node->wordSuffixes.push_back(node->longestSuffix);
    }
    node->wordSuffixes.insert(
        node->wordSuffixes.end(),
        node->longestSuffix->wordSuffixes.begin(),
        node->longestSuffix->wordSuffixes.end());

    for (int i = 0; i < 26; i++) {
      if (node->children[i] != nullptr) {
        queue.push_back(node->children[i]);
      }
    }
  }
}

class StreamChecker {
public:
  StreamChecker(std::vector<std::string> words) {
    root = new TrieNode(nullptr, -1);
    for (const auto& word : words) {
      insertTrie(root, word, 0);
    }
    findLongestSuffixes(root);
    current = root;
  }

  bool query(char c) {
    char charIndex = c - 'a';
    while (current != root && current->children[charIndex] == nullptr) {
      current = current->longestSuffix;
    }

    if (current->children[charIndex] != nullptr) {
      current = current->children[charIndex];
    }

    return current->isWord || !current->wordSuffixes.empty();
  }

private:
  TrieNode* root;
  TrieNode* current;
};

TEST(AhoCorasick, test) {
  TrieNode* root = new TrieNode(nullptr, -1);
  insertTrie(root, "a", 0);
  insertTrie(root, "ab", 0);
  insertTrie(root, "bab", 0);
  insertTrie(root, "bc", 0);
  insertTrie(root, "bca", 0);
  insertTrie(root, "c", 0);
  insertTrie(root, "caa", 0);
  findLongestSuffixes(root);
}

TEST(CharacterStream, test) {
  StreamChecker streamChecker{std::vector<std::string>{"cd", "f", "kl"}};
  ASSERT_FALSE(streamChecker.query('a')); // return False
  ASSERT_FALSE(streamChecker.query('b')); // return False
  ASSERT_FALSE(streamChecker.query('c')); // return False
  ASSERT_TRUE(streamChecker.query('d')); // return True, because 'cd' is in the wordlist
  ASSERT_FALSE(streamChecker.query('e')); // return False
  ASSERT_TRUE(streamChecker.query('f')); // return True, because 'f' is in the wordlist
  ASSERT_FALSE(streamChecker.query('g')); // return False
  ASSERT_FALSE(streamChecker.query('h')); // return False
  ASSERT_FALSE(streamChecker.query('i')); // return False
  ASSERT_FALSE(streamChecker.query('j')); // return False
  ASSERT_FALSE(streamChecker.query('k')); // return False
  ASSERT_TRUE(streamChecker.query('l')); // return True, because 'kl' is in the wordlist
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
