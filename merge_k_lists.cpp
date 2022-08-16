#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

std::vector<int> toArray(ListNode* list) {
  std::vector<int> array;
  while (list != nullptr) {
    array.push_back(list->val);
    list = list->next;
  }
  return array;
}

ListNode* mergeTwoLists(ListNode* left, ListNode* right) {
  if (left == nullptr && right == nullptr) {
    return nullptr;
  } else if (left == nullptr) {
    return right;
  } else if (right == nullptr) {
    return left;
  } else if (left->val > right->val) {
    return mergeTwoLists(right, left);
  }

  ListNode *first = left;
  ListNode *current = left;
  left = left->next;
  while (left != nullptr && right != nullptr) {
    if (left->val <= right->val) {
      current->next = left;
      left = left->next;
    } else {
      current->next = right;
      right = right->next;
    }

    current = current->next;
  }

  if (left == nullptr) {
    current->next = right;
  } else {
    current->next = left;
  }

  return first;
}

ListNode* mergeKLists(std::vector<ListNode*> lists) {
  if (lists.empty()) {
    return nullptr;
  }
  if (lists.size() == 1) {
    return lists[0];
  }
  if (lists.size() == 2) {
    return mergeTwoLists(lists[0], lists[1]);
  }

  int mid = lists.size() / 2;
  std::vector<ListNode *> left(lists.begin(), lists.begin() + mid);
  std::vector<ListNode *> right(lists.begin() + mid, lists.end());
  return mergeTwoLists(mergeKLists(left), mergeKLists(right));
}

TEST(MergeKLists, test1) {
  std::vector<ListNode*> lists;
  lists.push_back(new ListNode(1, new ListNode(4, new ListNode(5))));
  lists.push_back(new ListNode(1, new ListNode(3, new ListNode(4))));
  lists.push_back(new ListNode(2, new ListNode(6)));

  EXPECT_THAT(toArray(mergeKLists(lists)), ElementsAre(1, 1, 2, 3, 4, 4, 5, 6));
}

TEST(MergeKLists, test2) {
  std::vector<ListNode*> lists;
  EXPECT_EQ(mergeKLists(lists), nullptr);
}

TEST(MergeKLists, test3) {
  std::vector<ListNode*> lists;
  lists.push_back(nullptr);
  EXPECT_EQ(mergeKLists(lists), nullptr);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
