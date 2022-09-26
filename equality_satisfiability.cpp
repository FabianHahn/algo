#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

bool equationsPossible(std::vector<std::string>& equations) {
  std::vector<std::vector<char>> equivalences;
  std::vector<int> charEquivalence(26, -1);
  std::vector<std::pair<char, char>> inequalities;

  for (const auto& equation : equations) {
    char x = equation[0];
    char y = equation[3];
    bool isEqual = equation[1] == '=';
    if (!isEqual) {
      inequalities.emplace_back(std::make_pair(x, y));
      continue;
    }

    int xIndex = x - 'a';
    int yIndex = y - 'a';

    int xEquivalence = charEquivalence[xIndex];
    int yEquivalence = charEquivalence[yIndex];
    if (xEquivalence == -1 && yEquivalence == -1) {
      auto& equivalence = equivalences.emplace_back();
      equivalence.emplace_back(x);
      equivalence.emplace_back(y);
      charEquivalence[xIndex] = equivalences.size() - 1;
      charEquivalence[yIndex] = equivalences.size() - 1;
    } else if (xEquivalence == -1 && yEquivalence != -1) {
      auto& equivalence = equivalences[yEquivalence];
      equivalence.emplace_back(x);
      charEquivalence[xIndex] = yEquivalence;
    } else if (xEquivalence != -1 && yEquivalence == -1) {
      auto& equivalence = equivalences[xEquivalence];
      equivalence.emplace_back(y);
      charEquivalence[yIndex] = xEquivalence;
    } else if (xEquivalence != yEquivalence) {
      auto& equivalence = equivalences[xEquivalence];
      for (char c : equivalences[yEquivalence]) {
        int cIndex = c - 'a';

        equivalence.push_back(c);
        charEquivalence[cIndex] = xEquivalence;
      }
      equivalences[yEquivalence].clear();
    }
  }

  for (auto& [x, y] : inequalities) {
    if (x == y) {
      return false;
    }

    int xIndex = x - 'a';
    int yIndex = y - 'a';

    int xEquivalence = charEquivalence[xIndex];
    int yEquivalence = charEquivalence[yIndex];

    if (xEquivalence != -1 && yEquivalence != -1 && xEquivalence == yEquivalence) {
      return false;
    }
  }

  return true;
}

bool equationsPossibleTest(std::vector<std::string> equations) {
  return equationsPossible(equations);
}

TEST(EquationsSatisfiability, test) {
  EXPECT_EQ(equationsPossibleTest(std::vector<std::string>{"a==b", "a!=b"}), false);
  EXPECT_EQ(equationsPossibleTest(std::vector<std::string>{"b==a", "a==b"}), true);
  EXPECT_EQ(equationsPossibleTest(std::vector<std::string>{"a==b", "c==d", "b==c"}), true);
  EXPECT_EQ(equationsPossibleTest(std::vector<std::string>{"a==b", "c==d", "b==c", "a!=d"}), false);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
