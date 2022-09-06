#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct Line {
  int count;
};

struct Point {
  Point(int x_, int y_) : x{x_}, y{y_} {}

  int x;
  int y;
  std::unordered_map<std::uint64_t, int> lines;
};

int gcd(int a, int b) {
  if (a < 0) {
    return gcd(-a, b);
  } else if (b < 0) {
    return gcd(a, -b);
  } else if (a == b) {
    return a;
  } else if (a < b) {
    return gcd(b, a);
  } else if (a % b == 0) {
    return b;
  } else {
    return gcd(a - b * (a / b), b);
  }
}

std::uint64_t getSlopeKey(int dx, int dy) {
  if (dx == 0) {
    return UINT64_MAX;
  }
  if (dy == 0) {
    return 0;
  }

  if (dx < 0) {
    dx = -dx;
    dy = -dy;
  }

  int slopeGcd = gcd(dx, dy);
  dx /= slopeGcd;
  dy /= slopeGcd;

  return (std::uint64_t) dx * 1000000 + dy;
}

int maxPoints(std::vector<std::vector<int>>& input) {
  std::vector<Point> points;
  std::vector<Line> lines;

  for (auto entry : input) {
    Point newPoint(entry[0], entry[1]);
    for (auto& point : points) {
      int dx = point.x - newPoint.x;
      int dy = point.y - newPoint.y;

      std::uint64_t slopeKey = getSlopeKey(dx, dy);
      if (newPoint.lines.find(slopeKey) != newPoint.lines.end()) {
        // we're already on this line
        continue;
      }

      auto query = point.lines.find(slopeKey);
      if (query == point.lines.end()) {
        auto& line = lines.emplace_back();
        line.count = 2;
        point.lines[slopeKey] = lines.size() - 1;
        newPoint.lines[slopeKey] = lines.size() - 1;
      } else {
        int lineIndex = query->second;
        auto& line = lines[lineIndex];
        line.count++;
        newPoint.lines[slopeKey] = lineIndex;
      }
    }
    points.emplace_back(std::move(newPoint));
  }

  int maxPoints = 1;
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i].count > maxPoints) {
      maxPoints = lines[i].count;
    }
  }

  return maxPoints;
}

int maxPointsTest(std::vector<std::vector<int>> points) { return maxPoints(points); }

TEST(MaxPointsOnLine, Test) {
  EXPECT_EQ(maxPointsTest(std::vector<std::vector<int>>{{1, 1}, {2, 2}, {3, 3}}), 3);
  EXPECT_EQ(
      maxPointsTest(std::vector<std::vector<int>>{{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}),
      4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
