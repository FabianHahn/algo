#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

class MyCalendar {
public:
  MyCalendar() {}

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

class MyCalendarTwo {
public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    auto lo = numBookings.upper_bound(start);
    auto hi = numBookings.lower_bound(end);
    if (lo != numBookings.begin()) {
      --lo;
    }

    for (auto iter = lo; iter != hi; ++iter) {
      if (iter->second == 2) {
        return false;
      }
    }

    int prevCount = 0;
    int postCount = 0;
    for (auto iter = lo; iter != hi; ++iter) {
      if (iter->first <= start) {
        prevCount = iter->second;
      }
      if (iter->first <= end) {
        postCount = iter->second;
      }

      if (iter->first > start && iter->first < end) {
        iter->second++;
      }
    }

    numBookings[start] = prevCount + 1;
    if (numBookings.find(end) == numBookings.end()) {
      numBookings[end] = postCount;
    }

    return true;
  }

  std::map<int, int> numBookings;
};

TEST(CalendarDoubleBooking, test2) {
  {
    MyCalendarTwo myCalendar;
    ASSERT_TRUE(myCalendar.book(10, 20));
    ASSERT_TRUE(myCalendar.book(50, 60));
    ASSERT_TRUE(myCalendar.book(10, 40));
    ASSERT_FALSE(myCalendar.book(5, 15));
    ASSERT_TRUE(myCalendar.book(5, 10));
    ASSERT_TRUE(myCalendar.book(25, 55));
  }

  {
    MyCalendarTwo myCalendar;
    ASSERT_TRUE(myCalendar.book(10, 20));
    ASSERT_TRUE(myCalendar.book(10, 40));
    ASSERT_FALSE(myCalendar.book(15, 25));
  }

  {
    MyCalendarTwo myCalendar;
    ASSERT_TRUE(myCalendar.book(10, 20));
    ASSERT_TRUE(myCalendar.book(30, 40));
    ASSERT_TRUE(myCalendar.book(50, 60));
    ASSERT_TRUE(myCalendar.book(0, 100));
    ASSERT_FALSE(myCalendar.book(55, 100));
    ASSERT_TRUE(myCalendar.book(70, 80));
  }

  {
    std::vector<std::pair<int, int>> bookings = {
        {89, 100}, {30, 43}, {92, 100}, {31, 49},  {59, 76},  {60, 73}, {31, 49}, {80, 99},
        {48, 60},  {36, 52}, {67, 82},  {96, 100}, {22, 35},  {18, 32}, {9, 24},  {11, 27},
        {94, 100}, {12, 22}, {61, 74},  {3, 20},   {14, 28},  {27, 37}, {5, 20},  {1, 11},
        {96, 100}, {33, 44}, {90, 100}, {40, 54},  {23, 35},  {18, 32}, {78, 89}, {56, 66},
        {83, 93},  {45, 59}, {40, 59},  {94, 100}, {99, 100}, {86, 96}, {43, 61}, {29, 45},
        {21, 36},  {13, 31}, {17, 30},  {16, 30},  {80, 94},  {38, 50}, {15, 30}, {62, 79},
        {25, 39},  {73, 85}, {39, 56},  {80, 97},  {42, 57},  {32, 47}, {59, 78}, {35, 53},
        {56, 74},  {75, 85}, {39, 54},  {63, 82}};
    std::vector<bool> expected = {
        true,  true,  true,  true,  true,  true,  false, false, true,  false, false, false,
        false, false, true,  true,  false, false, false, false, false, false, false, true,
        false, false, false, false, false, false, true,  false, false, false, false, false,
        false, false, false, false, false, false, false, false, false, false, false, false,
        false, true,  false, false, false, false, false, false, false, false, false, false};

    MyCalendarTwo myCalendar;
    for (int i = 0; i < bookings.size(); i++) {
      bool result = myCalendar.book(bookings[i].first, bookings[i].second);
      ASSERT_EQ(result, expected[i]);
    }
  }

  {
    std::vector<std::pair<int, int>> bookings = {
        {33, 44}, {85, 95},  {20, 37}, {91, 100}, {89, 100}, {77, 87}, {80, 95}, {42, 61},
        {40, 50}, {85, 99},  {74, 91}, {70, 82},  {5, 17},   {77, 89}, {16, 26}, {21, 31},
        {30, 43}, {96, 100}, {27, 39}, {44, 55},  {15, 34},  {85, 99}, {74, 93}, {84, 94},
        {82, 94}, {46, 65},  {31, 49}, {58, 73},  {86, 99},  {73, 84}, {68, 80}, {5, 18},
        {75, 87}, {88, 100}, {25, 41}, {66, 79},  {28, 41},  {60, 70}, {62, 73}, {16, 33}};
    std::vector<bool> expected = {
        true,  true,  true,  true,  false, true,  false, true,  false, false, false,
        true,  true,  false, true,  false, false, true,  false, true,  false, false,
        false, false, false, false, false, true,  false, false, false, false, false,
        false, false, false, false, false, false, false

    };

    MyCalendarTwo myCalendar;
    for (int i = 0; i < bookings.size(); i++) {
      bool result = myCalendar.book(bookings[i].first, bookings[i].second);
      ASSERT_EQ(result, expected[i]);
    }
  }
}

class MyCalendarThree {
public:
  MyCalendarThree() {}

  int book(int start, int end) {
    auto lo = numBookings.upper_bound(start);
    auto hi = numBookings.lower_bound(end);
    if (lo != numBookings.begin()) {
      --lo;
    }

    int prevCount = 0;
    int postCount = 0;
    for (auto iter = lo; iter != hi; ++iter) {
      if (iter->first <= start) {
        prevCount = iter->second;
      }
      if (iter->first <= end) {
        postCount = iter->second;
      }

      if (iter->first > start && iter->first < end) {
        iter->second++;
        if (iter->second > maxCount) {
          maxCount = iter->second;
        }
      }
    }

    numBookings[start] = prevCount + 1;
    if (numBookings[start] > maxCount) {
      maxCount = numBookings[start];
    }
    if (numBookings.find(end) == numBookings.end()) {
      numBookings[end] = postCount;
    }

    return maxCount;
  }

  std::map<int, int> numBookings;
  int maxCount;
};


TEST(CalendarDoubleBooking, test3) {
  {
    MyCalendarThree myCalendar;
    ASSERT_EQ(myCalendar.book(10, 20), 1);
    ASSERT_EQ(myCalendar.book(50, 60), 1);
    ASSERT_EQ(myCalendar.book(10, 40), 2);
    ASSERT_EQ(myCalendar.book(5, 15), 3);
    ASSERT_EQ(myCalendar.book(5, 10), 3);
    ASSERT_EQ(myCalendar.book(25, 55), 3);
    ASSERT_EQ(myCalendar.book(0, 100), 4);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
