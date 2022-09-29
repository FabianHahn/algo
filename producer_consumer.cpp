#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

TEST(ProducerConsumer, test) {
  std::atomic<bool> done{false};
  std::array<std::deque<int>, 10> queues;
  std::array<std::atomic<int>, 10> queueSizes{};
  std::array<std::mutex, 10> mutexes;
  std::vector<std::thread> producers;
  for (int i = 0; i < 10; i++) {
    producers.emplace_back([&queues, &queueSizes, &mutexes, &done, i]() {
      while (!done) {
        if (queueSizes[i] < 10) {
          std::lock_guard lock{mutexes[i]};
          queues[i].push_back(i);
          queueSizes[i]++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
  }

  std::vector<int> counts(10, 0);
  int nextQueue = 0;
  for (int j = 0; j < 10000; j++) {
    while(true) {
      if (queueSizes[nextQueue] > 0) {
        int entry;
        {
          std::lock_guard lock{mutexes[nextQueue]};
          entry = queues[nextQueue].front();
          queues[nextQueue].pop_front();
          queueSizes[nextQueue]--;
        }

        assert(entry == nextQueue);
        counts[nextQueue]++;
        break;
      } else {
        nextQueue = (nextQueue + 1) % 10;
        std::this_thread::yield();
      }
    }
  }

  done = true;

  for (int i = 0; i < 10; i++) {
    producers[i].join();
    std::cout << "producer " << i << ": " << counts[i] << " read" << std::endl;
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
