#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool checkSubarraySum(std::vector<int>& nums, int k) {
  int n = nums.size();
  std::vector<bool> possible(k, false);
  std::vector<bool> nextPossible(k, false);
  for (int i = n - 2; i >= 0; i--) {
    std::fill(nextPossible.begin(), nextPossible.end(), false);

    int twoPair = (nums[i] + nums[i + 1]) % k;
    nextPossible[twoPair] = true;

    for (int j = 0; j < k; j++) {
      if (!possible[j]) {
        continue;
      }

      int sequence = (nums[i] + j) % k;
      nextPossible[sequence] = true;
    }

    std::swap(possible, nextPossible);
    if (possible[0]) {
      return true;
    }
  }

  return false;
}

bool checkSubarraySumSparse(std::vector<int>& nums, int k) {
  int n = nums.size();
  std::unordered_set<int> possible;
  std::unordered_set<int> nextPossible;
  for (int i = n - 2; i >= 0; i--) {
    nextPossible.clear();

    int twoPair = (nums[i] + nums[i + 1]) % k;
    nextPossible.insert(twoPair);

    for (int j : possible) {
      int sequence = (nums[i] + j) % k;
      nextPossible.insert(sequence);
    }

    std::swap(possible, nextPossible);

    if (possible.count(0) > 0) {
      return true;
    }
  }

  return false;
}

bool checkSubarraySumMod(std::vector<int>& nums, int k) {
  int n = nums.size();
  std::unordered_set<int> possible;
  int offset = 0;
  for (int i = n - 2; i >= 0; i--) {
    offset = (offset + nums[i]) % k;

    int twoPair = (nums[i] + nums[i + 1]) % k;
    int twoPairOffset = (twoPair - offset) % k;
    if (twoPairOffset < 0) {
      twoPairOffset += k;
    }
    possible.insert(twoPairOffset);

//    for (int j : possible) {
//      std::cout << (offset + j) % k << " ";
//    }
//    std::cout << std::endl;

    int zeroOffset = (k - offset) % k;
    if (possible.count(zeroOffset) > 0) {
      return true;
    }
  }

  return false;
}

bool checkSubarraySumTest(std::vector<int> nums, int k) { return checkSubarraySumMod(nums, k); }

TEST(ContinuousSubarraySum, test) {
  EXPECT_TRUE(checkSubarraySumTest(std::vector<int>{23, 2, 4, 6, 7}, 6));
  EXPECT_TRUE(checkSubarraySumTest(
      std::vector<int>{470, 161, 377, 184, 118, 91,  413, 73,  224, 167, 505, 413, 521, 5,   7,
                       372, 393, 523, 211, 479, 90,  516, 238, 467, 410, 51,  337, 31,  442, 297,
                       100, 75,  260, 33,  490, 477, 21,  374, 233, 41,  215, 87,  84,  153, 271,
                       241, 169, 275, 323, 358, 291, 176, 423, 426, 296, 175, 413, 423, 387, 416,
                       27,  266, 257, 136, 27,  155, 77,  142, 60,  335, 401, 443, 52,  153, 345,
                       71,  117, 443, 177, 238, 433, 464, 323, 79,  156, 429, 79,  327, 64,  335,
                       92,  147, 350, 480, 277, 335, 97,  317, 420, 453},
      75));
  EXPECT_FALSE(checkSubarraySumTest(std::vector<int>{23, 2, 6, 4, 7}, 13));
  EXPECT_TRUE(checkSubarraySumTest(std::vector<int>{5, 0, 0, 0}, 3));

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
