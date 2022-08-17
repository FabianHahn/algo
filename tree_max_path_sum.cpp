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
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int maxPathSum(TreeNode* root) {
  std::function<std::pair<int,int>(TreeNode*)> traverse;
  traverse = [&](TreeNode* node) {
    if (node == nullptr) {
      return std::make_pair(0, 0);
    }
    if (node->left == nullptr && node->right == nullptr) {
      return std::make_pair(node->val, node->val);
    }

    int maxPath = node->val;
    int maxDown = node->val;

    int maxPathLeft = INT_MIN;
    int maxDownLeft = INT_MIN;
    if (node->left != nullptr) {
      auto left = traverse(node->left);
      maxPathLeft = left.first;
      maxDownLeft = left.second;
      if (maxDownLeft > 0) {
        maxPath += maxDownLeft;
      }
    }

    int maxPathRight = INT_MIN;
    int maxDownRight = INT_MIN;
    if (node->right != nullptr) {
      auto right = traverse(node->right);
      maxPathRight = right.first;
      maxDownRight = right.second;
      if (maxDownRight > 0) {
        maxPath += maxDownRight;
      }
    }

    if (maxDownLeft > 0 || maxDownRight > 0) {
      if (maxDownLeft > maxDownRight) {
        maxDown += maxDownLeft;
      } else {
        maxDown += maxDownRight;
      }
    }

    if (maxPathLeft > maxPath) {
      maxPath = maxPathLeft;
    }
    if (maxPathRight > maxPath) {
      maxPath = maxPathRight;
    }

    return std::make_pair(maxPath, maxDown);
  };

  auto result = traverse(root);
  return result.first;
}

TEST(TreeMaxPathSum, test) {
  ASSERT_EQ(maxPathSum(new TreeNode(-3)), -3);
  ASSERT_EQ(maxPathSum(new TreeNode(-2, new TreeNode(-1), nullptr)), -1);
  ASSERT_EQ(maxPathSum(new TreeNode(1, new TreeNode(2), new TreeNode(3))), 6);
  ASSERT_EQ(
      maxPathSum(
          new TreeNode(-10, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))),
      42);
  ASSERT_EQ(
      maxPathSum(new TreeNode(
          5,
          new TreeNode(4, new TreeNode(11, new TreeNode(7), new TreeNode(2)), nullptr),
          new TreeNode(8, new TreeNode(13), new TreeNode(4, nullptr, new TreeNode(1))))),
      48);
  ASSERT_EQ(
      maxPathSum(new TreeNode(
          9,
          new TreeNode(6),
          new TreeNode(
              -3,
              new TreeNode(-6),
              new TreeNode(
                  2,
                  new TreeNode(2, new TreeNode(-6, new TreeNode(-6), nullptr), new TreeNode(-6)),
                  nullptr)))),
      16);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
