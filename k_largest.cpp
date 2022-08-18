#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct Comp {
  bool operator()(int a, int b) { return a > b; }
};

class KthLargest {
public:
  KthLargest(int k_, std::vector<int> nums) : k{k_} {
    for (int num : nums) {
      add(num);
    }
  }

  int add(int val) {
    if (heap.size() == k) {
      if (val > heap[0]) {
        std::pop_heap(heap.begin(), heap.end(), comp);
        heap.back() = val;
        std::push_heap(heap.begin(), heap.end(), comp);
      }
    } else {
      heap.push_back(val);
      std::push_heap(heap.begin(), heap.end(), comp);
    }
    return heap[0];
  }

private:
  Comp comp;
  int k;
  std::vector<int> heap;
};

TEST(KLargest, test) {
  KthLargest kthLargest{3, std::vector<int>{4, 5, 8, 2}};
  ASSERT_EQ(kthLargest.add(3), 4);
  ASSERT_EQ(kthLargest.add(5), 5);
  ASSERT_EQ(kthLargest.add(10), 5);
  ASSERT_EQ(kthLargest.add(9), 8);
  ASSERT_EQ(kthLargest.add(4), 8);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
