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
  std::vector<int> kBuy(k, INT_MIN);
  std::vector<int> kBuyKSell(k, INT_MIN);
  for (int price : prices) {
    for (int i = 0; i < k; i++) {
      kBuy[i] = std::max(kBuy[i], (i > 0 ? kBuyKSell[i - 1] : 0) - price);
      kBuyKSell[i] = std::max(kBuyKSell[i], kBuy[i] + price);
    }
  }

  int maxProfit = 0;
  for (int profit : kBuyKSell) {
    if (profit > maxProfit) {
      maxProfit = profit;
    }
  }

  return maxProfit;
}

TEST(StockTrading4, test) {
  EXPECT_THAT(maxProfit4(2, std::vector<int>{2, 4, 1}), 2);
  EXPECT_THAT(maxProfit4(2, std::vector<int>{3, 2, 6, 5, 0, 3}), 7);
}

int maxProfitFee(std::vector<int> prices, int fee) {
  int n = prices.size();

  std::vector maxProfitBuyingDp(n, -1);
  std::vector maxProfitSellingDp(n, -1);
  std::function<int(int)> maxProfitBuying;
  std::function<int(int)> maxProfitSelling;
  maxProfitBuying = [&](int startingDay) {
    if (startingDay >= n) {
      return 0;
    }

    int& result = maxProfitBuyingDp[startingDay];
    if (result >= 0) {
      return result;
    }

    int waitingProfit = maxProfitBuying(startingDay + 1);
    int buyingProfit = maxProfitSelling(startingDay + 1) - prices[startingDay] - fee;
    result = std::max(waitingProfit, buyingProfit);
    return result;
  };
  maxProfitSelling = [&](int startingDay) {
    if (startingDay >= n) {
      return 0;
    }

    int& result = maxProfitSellingDp[startingDay];
    if (result >= 0) {
      return result;
    }

    int waitingProfit = maxProfitSelling(startingDay + 1);
    int sellingProfit = maxProfitBuying(startingDay + 1) + prices[startingDay];
    result = std::max(waitingProfit, sellingProfit);
    return result;
  };

  return maxProfitBuying(0);
}

TEST(StockTradingFee, test) {
  EXPECT_THAT(maxProfitFee(std::vector<int>{1, 3, 2, 8, 4, 9}, 2), 8);
  EXPECT_THAT(maxProfitFee(std::vector<int>{1, 3, 7, 5, 10, 3}, 3), 6);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
