#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int maxProfit(std::vector<int>& prices) {
  if (prices.size() <= 1) {
    return 0;
  }

  prices.push_back(prices.back());

  std::vector<int> maxProfit(prices.size(), -1);

  std::function<int(int)> bestPrice;
  bestPrice = [&](int n) {
    if (n < 2) {
      return 0;
    }

    int cached = maxProfit[n];
    if (cached != -1) {
      return cached;
    }

    int best = bestPrice(n - 1); // wait
    int sellPrice = prices[n - 1];
    for (int i = 2; n - i >= 0; i++) {
      int buyPrice = prices[n - i];
      if (sellPrice <= buyPrice) {
        continue;
      }
      int baseProfit = bestPrice(n - i - 1);
      if (baseProfit + sellPrice < best) {
        break;
      }

      int sell = baseProfit + sellPrice - buyPrice;
      if (sell > best) {
        best = sell;
      }
    }

    maxProfit[n] = best;
    return best;
  };
  
  return bestPrice(prices.size() - 1);
}

TEST(StockTrading, test) {
  std::vector<int> prices{1, 2, 3, 0, 2};
  EXPECT_THAT(maxProfit(prices), 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
