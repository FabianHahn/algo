#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

int maxProfitWithCooldown(std::vector<int>& prices) {
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

TEST(StockTradingWithCooldown, test) {
  std::vector<int> prices{1, 2, 3, 0, 2};
  EXPECT_THAT(maxProfitWithCooldown(prices), 3);
}

int maxProfit2(std::vector<int> prices) {
  int n = prices.size();

  int i = 0;
  int profit = 0;
  while (i < n) {
    int bestBuyPrice = INT_MAX;
    while (i < n && prices[i] < bestBuyPrice) {
      bestBuyPrice = prices[i];
      i++;
    }

    if (i >= n) {
      break;
    }

    int bestSellPrice = INT_MIN;
    while (i < n && prices[i] > bestSellPrice) {
      bestSellPrice = prices[i];
      i++;
    }

    if (bestBuyPrice < INT_MAX && bestSellPrice > INT_MIN) {
      profit += bestSellPrice - bestBuyPrice;
    }
  }

  return profit;
}

TEST(StockTrading2, test) {
  EXPECT_THAT(maxProfit2(std::vector<int>{7, 1, 5, 3, 6, 4}), 7);
  EXPECT_THAT(maxProfit2(std::vector<int>{1, 2, 3, 4, 5}), 4);
  EXPECT_THAT(maxProfit2(std::vector<int>{7, 6, 4, 3, 1}), 0);
}

int maxProfit3(std::vector<int> prices) {
  int n = prices.size();
  int k = 2;

  std::vector<int> maxBuyingProfitDp(n * k, -1);
  std::vector<int> maxSellingProfitDp(n * k, -1);
  std::function<int(int, int)> maxBuyingProfit;
  std::function<int(int, int)> maxSellingProfit;
  maxBuyingProfit = [&](int startingDay, int buys) {
    if (startingDay >= n || buys == 0) {
      return 0;
    }

    int& result = maxBuyingProfitDp[startingDay * k + (buys - 1)];
    if (result > -1) {
      return result;
    }

    int waitProfit = maxBuyingProfit(startingDay + 1, buys);
    int buyProfit = maxSellingProfit(startingDay + 1, buys - 1) - prices[startingDay];
    result = std::max(waitProfit, buyProfit);
    return result;
  };
  maxSellingProfit = [&](int startingDay, int buys) {
    if (startingDay >= n) {
      return 0;
    }

    int& result = maxSellingProfitDp[startingDay * k + buys];
    if (result > -1) {
      return result;
    }

    int waitProfit = maxSellingProfit(startingDay + 1, buys);
    int sellProfit = maxBuyingProfit(startingDay + 1, buys) + prices[startingDay];
    result = std::max(waitProfit, sellProfit);
    return result;
  };

  return maxBuyingProfit(0, k);
}

TEST(StockTrading3, test) {
  EXPECT_THAT(maxProfit3(std::vector<int>{3, 3, 5, 0, 0, 3, 1, 4}), 6);
  EXPECT_THAT(maxProfit3(std::vector<int>{1, 2, 3, 4, 5}), 4);
  EXPECT_THAT(maxProfit3(std::vector<int>{7, 6, 4, 3, 1}), 0);
}

int maxProfit4(int k, std::vector<int> prices) {
  int n = prices.size();

  std::vector<int> maxBuyingProfitDp(n * k, -1);
  std::vector<int> maxSellingProfitDp(n * k, -1);
  std::function<int(int, int)> maxBuyingProfit;
  std::function<int(int, int)> maxSellingProfit;
  maxBuyingProfit = [&](int startingDay, int buys) {
    if (startingDay >= n || buys == 0) {
      return 0;
    }

    int& result = maxBuyingProfitDp[startingDay * k + (buys - 1)];
    if (result > -1) {
      return result;
    }

    int waitProfit = maxBuyingProfit(startingDay + 1, buys);
    int buyProfit = maxSellingProfit(startingDay + 1, buys - 1) - prices[startingDay];
    result = std::max(waitProfit, buyProfit);
    return result;
  };
  maxSellingProfit = [&](int startingDay, int buys) {
    if (startingDay >= n) {
      return 0;
    }

    int& result = maxSellingProfitDp[startingDay * k + buys];
    if (result > -1) {
      return result;
    }

    int waitProfit = maxSellingProfit(startingDay + 1, buys);
    int sellProfit = maxBuyingProfit(startingDay + 1, buys) + prices[startingDay];
    result = std::max(waitProfit, sellProfit);
    return result;
  };

  return maxBuyingProfit(0, k);
}

TEST(StockTrading4, test) {
  EXPECT_THAT(maxProfit4(2, std::vector<int>{2, 4, 1}), 2);
  EXPECT_THAT(maxProfit4(2, std::vector<int>{3, 2, 6, 5, 0, 3}), 7);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
