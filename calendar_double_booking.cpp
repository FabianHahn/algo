#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

class MyCalendar {
public:
  MyCalendar() {

  }

  bool book(int start, int end) {
    if (entries.empty()) {
      entries[start] = end;
      return true;
    }

    auto iter = entries.lower_bound(start);
    if (iter == entries.begin()) {
      if (end > entries.begin()->first) {
        return false;
      } else {
        entries[start] = end;
        return true;
      }
    }

    if (iter != entries.end() && end > iter->first) {
      return false;
    }

    auto previous = std::prev(iter);
    if (previous->second > start) {
      return false;
    }

    entries[start] = end;
    return true;
  }

  std::map<int, int> entries;
};

TEST(CalendarDoubleBooking, test) {
  MyCalendar myCalendar;
  ASSERT_TRUE(myCalendar.book(10, 20));
  ASSERT_FALSE(myCalendar.book(15, 25));
  ASSERT_FALSE(myCalendar.book(5, 15));
  ASSERT_FALSE(myCalendar.book(12, 18));
  ASSERT_TRUE(myCalendar.book(20, 30));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
