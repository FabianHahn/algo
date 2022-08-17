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
  std::unordered_map<TreeNode*, int> maxPaths;

  std::function<int(TreeNode*)> traverse;
  traverse = [&](TreeNode* node) {
    if (node == nullptr) {
      return 0;
    }

    int maxPath = node->val;
    int maxDown = node->val;

    int maxLeft = traverse(node->left);
    if (maxLeft > 0) {
      maxPath += maxLeft;
    }

    int maxRight = traverse(node->right);
    if (maxRight > 0) {
      maxPath += maxRight;
    }

    if (maxLeft > 0 || maxRight > 0) {
      if (maxLeft > maxRight) {
        maxDown += maxLeft;
      } else {
        maxDown += maxRight;
      }
    }

    maxPaths[node] = maxPath;
    return maxDown;
  };

  traverse(root);

  int maxPath = INT_MIN;
  for (auto entry : maxPaths) {
    if (entry.second > maxPath) {
      maxPath = entry.second;
    }
  }

  return maxPath;
}

TEST(TreeMaxPathSum, test) {
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
