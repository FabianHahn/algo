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

int pathSum(TreeNode* root, int targetSum) {
  // number of paths starting with node + number of paths not starting with node equal to sum
  // num(node, sum) = numWith(node, sum) + numWithout(node, sum)
  // numWith(node, sum) = numWith(node->left, sum - node->val) + numWith(node->right, sum -
  // node->val) numWithout(node, sum) = num(node->left, sum) + num(node->right, sum) each node: 2
  // rec calls to left, 2 rec calls to right
  std::function<int(TreeNode*, int64_t)> num;
  std::function<int(TreeNode*, int64_t)> numWith;
  std::function<int(TreeNode*, int64_t)> numWithout;
  num = [&](TreeNode* node, int64_t sum) { return numWith(node, sum) + numWithout(node, sum); };
  numWith = [&](TreeNode* node, int64_t sum) {
    if (node == nullptr) {
      return 0;
    }

    int thisCount = 0;
    if (node->val == sum) {
      thisCount = 1;
    }

    int64_t remaining = sum - node->val;
    return numWith(node->left, remaining) + numWith(node->right, remaining) + thisCount;
  };
  numWithout = [&](TreeNode* node, int64_t sum) {
    if (node == nullptr) {
      return 0;
    }

    return num(node->left, sum) + num(node->right, sum);
  };

  return num(root, targetSum);
}

int pathSumLinear(TreeNode* root, int targetSum) {
  std::unordered_map<int64_t, int> prefixCounts{{0, 1}};
  std::function<int(TreeNode*, int64_t, int)> dfs;
  dfs = [&](TreeNode* node, int64_t prefixSum, int target) {
    if (node == nullptr) {
      return 0;
    }

    prefixSum += node->val;
    int64_t remaining = prefixSum - target;

    int count = prefixCounts[remaining];

    prefixCounts[prefixSum]++;
    count += dfs(node->left, prefixSum, target) + dfs(node->right, prefixSum, target);
    prefixCounts[prefixSum]--;
    return count;
  };

  return dfs(root, 0, targetSum);
}

TEST(PathSum, test) {
  EXPECT_EQ(
      pathSumLinear(
          new TreeNode(
              10,
              new TreeNode(
                  5,
                  new TreeNode(3, new TreeNode(3), new TreeNode(-2)),
                  new TreeNode(2, nullptr, new TreeNode(1))),
              new TreeNode(-3, nullptr, new TreeNode(11))),
          8),
      3);

  EXPECT_EQ(
      pathSumLinear(
          new TreeNode(
              5,
              new TreeNode(4, new TreeNode(11, new TreeNode(7), new TreeNode(2)), nullptr),
              new TreeNode(8, new TreeNode(13), new TreeNode(4, new TreeNode(5), new TreeNode(1)))),
          22),
      3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
