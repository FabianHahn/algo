#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int maxProfit(std::vector<int>& prices) {
  prices.push_back(prices.back());
  int n = prices.size();

  std::vector<int> wait(n, -1);
  std::vector<int> hold(n * 1001, -1);

  std::function<int(int, int)> bestPrice;
  bestPrice = [&](int i, int k) {
    if (k == -1) { // waiting
      if (i < 0) {
        return 0;
      }

      int cached = wait[i];
      if (cached != -1) {
        return cached;
      }

      int best = bestPrice(i - 1, -1); // wait
      if (i > 0) {
        for (int j = 0; j <= 1000; j++) {
          if (j >= prices[i - 1]) {
            break;
          }

          int sell = bestPrice(i - 2, j) + prices[i - 1] - j;
          if (sell > best) {
            best = sell;
          }
        }
      }

      wait[i] = best;
      return best;
    } else { // holding
      if (i < 0) {
        return INT_MIN;
      }

      int cached = hold[i * 1001 + k];
      if (cached != -1) {
        return cached;
      }

      int best = bestPrice(i - 1, k); // hold
      if (k == prices[i]) {
        int buy = bestPrice(i - 1, -1); // buy
        if (buy > best) {
          best = buy;
        }
      }
      hold[i * 1001 + k] = best;
      return best;
    }
  };

  for (int i = 0; i < n; i++) {
    bestPrice(i, -1);
    // std::cout << "best price " << i << ": " << bestPrice(i, -1) << std::endl;
  }
  return bestPrice(n - 1, -1);
}

TEST(StockTrading, test) {
  std::vector<int> prices{1, 2, 3, 0, 2};
  EXPECT_THAT(maxProfit(prices), 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
