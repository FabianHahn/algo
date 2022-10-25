#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool isBadVersion(int i) {
  return i >= 4;
}

int firstBadVersion(int n) {
  int lo = 1; // 1 4
  int hi = n; // 5 4
  while (lo < hi) {
    int size = hi - lo; // 4 1
    int mid = lo + (size / 2); // 3 4

    if (isBadVersion(mid)) { // false
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  return hi;
}

TEST(FirstBadVersion, test) {
  EXPECT_EQ(firstBadVersion(5), 4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
