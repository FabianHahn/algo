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

class Semaphore {
public:
  Semaphore(int count) : count_{count} {}

  void acquire() {
    std::unique_lock<std::mutex> lock{mutex_};
    conditionVariable_.wait(lock, [&]() {
      return count_ > 0;
    });
    count_--;
  }

  void release() {
    {
      std::lock_guard lock{mutex_};
      count_++;
    }
    conditionVariable_.notify_one();
  }

private:
  int count_;
  std::condition_variable conditionVariable_;
  std::mutex mutex_;
};

TEST(SemaphoreTest, test) {
  Semaphore semaphore{10};
  std::atomic<bool> done{false};
  std::vector<std::thread> producers;
  std::array<int, 10> maxNumber{};
  int shared = 0;
  for (int i = 0; i < 10; i++) {
    producers.emplace_back([&, i]() {
      while (!done) {
        semaphore.acquire();
        maxNumber[i] = std::max(maxNumber[i], shared);
        semaphore.release();
      }
    });
  }

  for (int j = 0; j < 100; j++) {
    for (int i = 0; i < 10; i++) {
      semaphore.acquire();
    }

    shared++;
    std::this_thread::sleep_for(std::chrono::milliseconds{1});

    for (int i = 0; i < 10; i++) {
      assert(maxNumber[i] < shared);
    }

    for (int i = 0; i < 10; i++) {
      semaphore.release();
    }
  }

  done = true;

  for (int i = 0; i < 10; i++) {
    producers[i].join();
    std::cout << "reader " << i << ": " << maxNumber[i] << " max" << std::endl;
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
