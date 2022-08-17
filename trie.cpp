#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct Node {
  char letter;
  bool present;
  Node* children[26];

  Node(char l) : letter{l}, present{false} { memset(children, 0, 26 * sizeof(Node*)); }
};

class Trie {
public:
  Trie() { root = new Node(-1); }

  void insert(std::string word) {
    Node* current = root;
    for (int i = 0; i < word.size(); i++) {
      char c = word[i];
      char charIndex = c - 'a';
      if (current->children[charIndex] == nullptr) {
        current->children[charIndex] = new Node(c);
      }
      current = current->children[charIndex];
    }

    current->present = true;
  }

  bool search(std::string word) {
    Node* current = root;
    for (int i = 0; i < word.size(); i++) {
      char c = word[i];
      char charIndex = c - 'a';
      if (current->children[charIndex] == nullptr) {
        return false;
      }
      current = current->children[charIndex];
    }

    return current->present;
  }

  bool startsWith(std::string prefix) {
    Node* current = root;
    for (int i = 0; i < prefix.size(); i++) {
      char c = prefix[i];
      char charIndex = c - 'a';
      if (current->children[charIndex] == nullptr) {
        return false;
      }
      current = current->children[charIndex];
    }

    return true;
  }

private:
  Node* root;
};

TEST(Trie, test) {
  Trie trie;
  trie.insert("apple");
  ASSERT_TRUE(trie.search("apple"));
  ASSERT_FALSE(trie.search("app"));
  ASSERT_TRUE(trie.startsWith("app"));
  trie.insert("app");
  ASSERT_TRUE(trie.search("app"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
