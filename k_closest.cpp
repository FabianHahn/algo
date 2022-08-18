#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> points, int k) {
  std::vector<std::pair<double, int>> heap(points.size());
  for(int i = 0; i < points.size(); i++) {
    int x = points[i][0];
    int y = points[i][1];
    double d2 = 1.0f / (double) (x * x + y * y);
    heap[i] = std::make_pair(d2, i);
  }

  std::make_heap(heap.begin(), heap.end());

  std::vector<std::vector<int>> result(k);
  for (int i = 0; i < k; i++) {
    result[i] = points[heap[0].second];
    std::pop_heap(heap.begin(), heap.end());
    heap.pop_back();
  }
  return result;
}

TEST(KClosest, test) {
  ASSERT_THAT(
      kClosest(std::vector<std::vector<int>>{{1, 3}, {-2, 2}}, 1),
      UnorderedElementsAre(ElementsAre(-2, 2)));
  ASSERT_THAT(
      kClosest(std::vector<std::vector<int>>{{3, 3}, {5, -1}, {-2, 4}}, 2),
      UnorderedElementsAre(ElementsAre(3, 3), ElementsAre(-2, 4)));
  ASSERT_THAT(
      kClosest(std::vector<std::vector<int>>{{9997, 9997}, {9996, 9998}}, 1),
      UnorderedElementsAre(ElementsAre(9997, 9997)));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
