#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int racecar(int target) {
  std::vector<int> shortestData(4 * target * 20, 0);
  std::vector<int> solutions(1001);
  auto shortest = [&](int t, int s, bool p) -> int& {
    assert(s >= 0);
    assert(s <= 9);
    assert(t + 2 * target >= 0);
    assert(t + 2 * target < 4 * target);

    if (p) {
      return shortestData[(t + 2 * target) * 20 + 10 + s];
    } else {
      return shortestData[(t + 2 * target) * 20 + 9 - s];
    }
  };

  std::function<int(int, int, bool, int f)> computeShortest;
  computeShortest = [&](int t, int s, bool p, int f) -> int {
    // std::cout << "t = " << t << ", s = " << s << ", p = " << (p ? "true" : "false") << ", f = "
    // << f << std::endl;

    if (t == 0 && s == 0 && p) {
      // initial state
      return 0;
    }

    if (t < -2 * target) {
      return 999999;
    }
    if (t >= 2 * target) {
      return 999999;
    }
    if (s > 10) {
      return 999999;
    }

    if (t > 0 && t <= 1000 && solutions[t] > f) {
      return -1;
    }

    if (shortest(t, s, p) > 0) {
      return shortest(t, s, p);
    }

    int current;
    int solution;
    if (s > 0) {
      if (f < 1) {
        return -1;
      }

      if (p) {
        current = computeShortest(t - (1 << (s - 1)), s - 1, p, f - 1);
      } else {
        current = computeShortest(t + (1 << (s - 1)), s - 1, p, f - 1);
      }

      if (current < 0) {
        return -1;
      }

      solution = current + 1;
    } else {
      if (f < 2) {
        return -1;
      }

      solution = 999999;
      for (int i = 0; i <= 9; i++) {
        // AR
        if (p) {
          current = computeShortest(t + (1 << i), i, false, f - 2);
        } else {
          current = computeShortest(t - (1 << i), i, true, f - 2);
        }
        if (current >= 0 && current + 2 < solution) {
          solution = current + 2;
        }

        // ARR
        if (f >= 3) {
          if (p) {
            current = computeShortest(t - (1 << i), i, true, f - 3);
          } else {
            current = computeShortest(t + (1 << i), i, false, f - 3);
          }
          if (current >= 0 && current + 3 < solution) {
            solution = current + 3;
          }
        }
      }

      if (solution > f) {
        return -1;
      }
    }

    // std::cout << "t = " << t << ", s = " << s << ", p = " << (p ? "true" : "false") << ": " <<
    // solution << std::endl;

    shortest(t, s, p) = solution;
    return solution;
  };

  auto computeBest = [&](int t, int l) {
    int bestSolution = 999999;
    for (int s = 1; s <= 9; s++) {
      int current;

      current = computeShortest(t, s, true, l);
      if (current >= 0 && current < bestSolution) {
        bestSolution = current;
      }

      current = computeShortest(t, s, false, l);
      if (current >= 0 && current < bestSolution) {
        bestSolution = current;
      }
    }

    return bestSolution;
  };

  solutions[0] = 0;
  for (int t = 1; t <= target; t++) {
    solutions[t] = computeBest(t, solutions[t - 1] + 3);
    std::cout << t << ": " << solutions[t] << std::endl;
  }

  return solutions[target];
}

TEST(Racecar, test) {
  //  EXPECT_THAT(racecar(2), 4);
  //  EXPECT_THAT(racecar(3), 2);
  //  EXPECT_THAT(racecar(4), 5);
  //  EXPECT_THAT(racecar(5), 7);
  //  EXPECT_THAT(racecar(6), 5);
  //  EXPECT_THAT(racecar(7), 3);
  //  EXPECT_THAT(racecar(8), 6);
  //  EXPECT_THAT(racecar(9), 8);
  //  EXPECT_THAT(racecar(10), 7);
  EXPECT_THAT(racecar(1000), 7);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
