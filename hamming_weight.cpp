#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int hammingWeight(uint32_t n) {
  int result = 0;
  for (int i = 0; i < 32; i++) {
    uint32_t bit = 1u << i;
    if ((n & bit) == bit) {
      result++;
    }
  }
  return result;
}

TEST(HammingWeight, test) {
  EXPECT_THAT(hammingWeight(11), 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
