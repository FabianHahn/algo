#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::string pushDominoesIncremental(std::string dominoes) {
  int n = dominoes.size();

  while (true) {
    bool changed = false;

    char prev = '.';
    char current = '.';
    char next = n > 0 ? dominoes[0] : '.';
    for (int i = 0; i < n; i++) {
      prev = current;
      current = next;
      next = i < n - 1 ? dominoes[i + 1] : '.';

      if (current != '.') {
        continue;
      }

      if (prev == 'R' && next != 'L') {
        dominoes[i] = 'R';
        changed = true;
      } else if (prev != 'R' && next == 'L') {
        dominoes[i] = 'L';
        changed = true;
      }
    }

    if (!changed) {
      break;
    }
  }

  return dominoes;
}

std::string pushDominoesForces(std::string dominoes) {
  int n = dominoes.size();

  std::deque<int> rights;
  std::deque<int> lefts;
  for (int i = 0; i < n; i++) {
    if (dominoes[i] == 'R') {
      rights.push_back(i);
    } else if (dominoes[i] == 'L') {
      lefts.push_back(i);
    }
  }

  std::deque<std::pair<int, bool>> forces;
  while (!rights.empty() || !lefts.empty()) {
    while (!rights.empty()) {
      int position = rights.front();
      rights.pop_front();

      if (position < n - 1 && dominoes[position + 1] == '.') {
        forces.emplace_back(std::make_pair(position + 1, true));
      }
    }
    while (!lefts.empty()) {
      int position = lefts.front();
      lefts.pop_front();

      if (position > 0 && dominoes[position - 1] == '.') {
        forces.emplace_back(std::make_pair(position - 1, false));
      }
    }

    while (!forces.empty()) {
      auto [position, right] = forces.front();
      forces.pop_front();

      if (right) {
        dominoes[position] = 'R';
        rights.push_back(position);
      } else if (dominoes[position] == 'R') {
        dominoes[position] = '.';
      } else {
        dominoes[position] = 'L';
        lefts.push_back(position);
      }
    }
  }

  return dominoes;
}

std::string pushDominoesLinear(std::string dominoes) {
  int n = dominoes.size();
  int lo = -1;
  char left = 'L';
  while (lo < n) {
    int hi = lo + 1;
    while (hi < n && dominoes[hi] == '.') {
      hi++;
    }

    char right = 'R';
    if (hi < n) {
      right = dominoes[hi];
    }

    if (left == 'L' && right == 'L') {
      for (int i = lo + 1; i < hi; i++) {
        dominoes[i] = 'L';
      }
    } else if (left == 'L' && right == 'R') {
      // nothing to do
    } else if (left == 'R' && right == 'R') {
      for (int i = lo + 1; i < hi; i++) {
        dominoes[i] = 'R';
      }
    } else if (left == 'R' && right == 'L') {
      int subLo = lo + 1;
      int subHi = hi - 1;
      while (subLo < subHi) {
        dominoes[subLo++] = 'R';
        dominoes[subHi--] = 'L';
      }
    }

    lo = hi;
    left = right;
  }

  return dominoes;
}

TEST(Dominoes, Incremental) {
  EXPECT_EQ(pushDominoesIncremental("RR.L"), "RR.L");
  EXPECT_EQ(pushDominoesIncremental(".L.R...LR..L.."), "LL.RR.LLRRLL..");
}

TEST(Dominoes, Forces) {
  EXPECT_EQ(pushDominoesForces("R."), "RR");
  EXPECT_EQ(pushDominoesForces(".L"), "LL");
  EXPECT_EQ(pushDominoesForces(".L.R...LR..L.."), "LL.RR.LLRRLL..");
  EXPECT_EQ(pushDominoesForces("RR.L"), "RR.L");
}

TEST(Dominoes, Linear) {
  //EXPECT_EQ(pushDominoesLinear("R."), "RR");
  //EXPECT_EQ(pushDominoesLinear(".L"), "LL");
  EXPECT_EQ(pushDominoesLinear("RR.L"), "RR.L");
  EXPECT_EQ(pushDominoesLinear(".L.R...LR..L.."), "LL.RR.LLRRLL..");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
