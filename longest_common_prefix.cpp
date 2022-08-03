#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::string longestCommonPrefix(const std::vector<std::string>& strs) {
  if (strs.empty()) {
    return "";
  }

  std::stringstream ss;
  const std::string& first = strs[0];
  for (std::size_t i = 0; i < first.size(); i++) {
    for (std::size_t j = 1; j < strs.size(); j++) {
      if (strs[j][i] != first[i]) {
        return ss.str();
      }
    }
    ss << first[i];
  }

  return ss.str();
}

TEST(LongestCommonPrefix, test) {
  ASSERT_EQ(longestCommonPrefix(std::vector<std::string>{"flower", "flow", "flight"}), "fl");
  ASSERT_EQ(longestCommonPrefix(std::vector<std::string>{"dog", "racecar", "car"}), "");
  ASSERT_EQ(longestCommonPrefix(std::vector<std::string>{"foo", "foobar", "foo"}), "foo");
  ASSERT_EQ(longestCommonPrefix(std::vector<std::string>{"foo", "foo", "foo"}), "foo");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
