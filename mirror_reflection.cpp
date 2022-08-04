#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int mirrorReflection(int p, int q) {
  int t = 0;

  int bottomLeft = -1;
  int bottomRight = 0;
  int topRight = 1;
  int topLeft = 2;

  while (true) {
    t += q;

    if (t == p) {
      return topRight;
    } else if (t < p) {
      // mirror horizontally
      std::swap(bottomLeft, bottomRight);
      std::swap(topLeft, topRight);
    } else {
      std::swap(bottomLeft, topLeft);
      std::swap(bottomRight, topRight);
      t = t - q - p;
    }
  }
}

int gcd(int a, int b) {
  if (a == 0) {
    return b;
  }
  if (b == 0) {
    return a;
  }

  if (a > b) {
    return gcd(a % b, b);
  } else {
    return gcd(a, b % a);
  }
}

int mirrorReflectionGcd(int p, int q) {
  int pqGcd = gcd(p, q);
  int pqLcm = p * q / pqGcd;
  int horizontalSteps = pqLcm / q;
  int verticalSteps = pqLcm / p;
  bool horizontalChange = horizontalSteps % 2 == 1;
  bool verticalChange = verticalSteps % 2 == 1;
  if (horizontalChange && !verticalChange) {
    return 0;
  } else if (horizontalChange && verticalChange) {
    return 1;
  } else {
    return 2;
  }
}

TEST(MirrorReflection, iterative) {
  EXPECT_THAT(mirrorReflection(2, 1), 2);
  EXPECT_THAT(mirrorReflection(3, 1), 1);
  EXPECT_THAT(mirrorReflection(4, 3), 2);
}

TEST(MirrorReflection, gcd) {
  EXPECT_THAT(mirrorReflectionGcd(2, 1), 2);
  EXPECT_THAT(mirrorReflectionGcd(3, 1), 1);
  EXPECT_THAT(mirrorReflectionGcd(4, 3), 2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
