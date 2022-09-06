#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::vector<int> compute(const std::vector<int>& input) {
  std::vector<int> output;
  return output;
}

TEST(Interview, Test) {
  EXPECT_THAT(compute(std::vector<int>{2, 7, 11, 15}), UnorderedElementsAre(0, 1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
