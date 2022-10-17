#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
template <>
struct hash<std::pair<int, int>> {
  size_t operator()(std::pair<int, int> a) const {
    size_t h = 0;
    hash_combine(h, a.first);
    hash_combine(h, a.second);
    return h;
  }
};
} // namespace std

int findTargetSumWays(std::vector<int>& nums, int target) {
  int n = nums.size();
  std::function<int(int, int)> dfs;
  std::unordered_map<std::pair<int, int>, int> dfsDp;
  dfs = [&](int k, int t) {
    if (k == n) {
      if (t == 0) {
        return 1;
      } else {
        return 0;
      }
    }

    auto key = std::make_pair(k, t);
    auto query = dfsDp.find(key);
    if (query != dfsDp.end()) {
      return query->second;
    }

    int num = nums[k];
    int plus = dfs(k + 1, t - num);
    int minus = dfs(k + 1, t + num);
    int result = plus + minus;
    dfsDp[key] = result;

    return result;
  };

  return dfs(0, target);
}

int findTargetSumWaysTest(std::vector<int> nums, int target) {
  return findTargetSumWays(nums, target);
}

TEST(TargetSum, test) {
  EXPECT_EQ(findTargetSumWaysTest(std::vector<int>{1, 1, 1, 1, 1}, 3), 5);
  EXPECT_EQ(findTargetSumWaysTest(std::vector<int>{1}, 1), 1);
  EXPECT_EQ(findTargetSumWaysTest(std::vector<int>{1, 2, 3, 1}, 3), 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
