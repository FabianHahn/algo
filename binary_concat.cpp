#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int concatenatedBinary(int n) {
  int mod = 1000000007;

  auto modmul = [&](int a, int b) {
    std::int64_t result = (static_cast<std::int64_t>(a) * static_cast<std::int64_t>(b)) % mod;
    return static_cast<int>(result);
  };
  auto modadd = [&](int a, int b) {
    std::int64_t result = (static_cast<std::int64_t>(a) + static_cast<std::int64_t>(b)) % mod;
    return static_cast<int>(result);
  };

  int digits = 0;
  int nReduced = n;
  while (nReduced > 0) {
    nReduced >>= 1;
    digits++;
  }

  int result = 0;
  int multiplier = 1;
  for (int i = n; i >= 1; i--) {
    int add = modmul(i, multiplier);
    result = modadd(result, add);

    for (int j = 0; j < digits; j++) {
      multiplier = modmul(multiplier, 2);
    }

    int digitLimit = 1 << (digits - 1);
    if (i == digitLimit) {
      digits--;
    }
  }

  return result;
}

TEST(BinaryConcat, test) {
  EXPECT_EQ(concatenatedBinary(3), 27);
  EXPECT_EQ(concatenatedBinary(1), 1);
  EXPECT_EQ(concatenatedBinary(12), 505379714);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
