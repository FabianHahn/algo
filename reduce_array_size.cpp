#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int minSetSize(std::vector<int> arr) {
  std::unordered_map<int, int> numbers;
  for (int num : arr) {
    numbers[num]++;
  }

  std::vector<int> counts;
  for(auto entry: numbers) {
    counts.push_back(entry.second);
  }

  std::sort(counts.begin(), counts.end());

  int target = arr.size() / 2;
  int sum = 0;
  int count = 0;
  for (auto iter = counts.rbegin(); iter != counts.rend(); ++iter) {
    sum += *iter;
    count++;
    if (sum >= target) {
      return count;
    }
  }

  return 0;
}

TEST(ReduceArraySize, test) {
  EXPECT_EQ(minSetSize(std::vector<int>{3, 3, 3, 3, 5, 5, 5, 2, 2, 7}), 2);
  EXPECT_EQ(minSetSize(std::vector<int>{7, 7, 7, 7, 7, 7}), 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
