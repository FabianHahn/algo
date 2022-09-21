#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left_, TreeNode* right_) : val{x}, left{left_}, right{right_} {}
};

// Encodes a tree to a single string.
std::string serialize(TreeNode* root) {
  std::stringstream stream;

  std::function<void(TreeNode*)> dfs;
  dfs = [&](TreeNode* node) {
    if (node == nullptr) {
      stream << 9999;
      return;
    }

    stream << node->val;
    stream << "(";
    dfs(node->left);
    stream << ")";
    stream << "(";
    dfs(node->right);
    stream << ")";
  };

  dfs(root);
  return stream.str();
}

// Decodes your encoded data to tree.
TreeNode* deserialize(std::string data) {
  std::istringstream stream{data};
  std::function<TreeNode*()> dfs;
  dfs = [&]() -> TreeNode* {
    int val;
    stream >> val;

    if (val == 9999) {
      return nullptr;
    }

    char c;
    stream >> c;
    assert(c == '(');
    TreeNode* left = dfs();
    stream >> c;
    assert(c == ')');
    stream >> c;
    assert(c == '(');
    TreeNode* right = dfs();
    stream >> c;
    assert(c == ')');

    return new TreeNode(val, left, right);
  };

  return dfs();
}

TEST(SerializeTree, test) {
  EXPECT_EQ(
      serialize(
          new TreeNode(3, new TreeNode(4, new TreeNode(2), new TreeNode(5)), new TreeNode(8))),
      "3(4(2(9999)(9999))(5(9999)(9999)))(8(9999)(9999))");
  EXPECT_EQ(
      serialize(deserialize(serialize(
          new TreeNode(3, new TreeNode(4, new TreeNode(2), new TreeNode(5)), new TreeNode(8))))),
      "3(4(2(9999)(9999))(5(9999)(9999)))(8(9999)(9999))");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
