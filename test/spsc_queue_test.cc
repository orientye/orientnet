// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "util/concurrent/spsc_queue.h"

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "test/3rdparty/doctest/doctest.h"
#include "test/benchmark.h"

namespace SQT {

template <typename T>
struct TestDataGenerator {
  T limit() const { return 1 << 24; }
  T generate() const { return rand() % 80; }
};

template <>
struct TestDataGenerator<std::string> {
  unsigned int limit() const { return 1 << 24; }
  std::string generate() const { return std::string(12, ' '); }
};

template <class TestType, std::uint32_t capacity>
void test() {
  std::unique_ptr<TestType> const t(new TestType(capacity));
  (*t)();
}

template <typename T>
class CorrectTest {
 public:
  explicit CorrectTest(std::uint32_t capacity)
      : queue_(), produce_finish_(false) {
    const size_t sz = test_data_generator_.limit();
    test_data_.reserve(sz);
    for (size_t i = 0; i < sz; ++i) {
      test_data_.push_back(test_data_generator_.generate());
    }
  }

  void operator()() {
    std::thread producer([this] { this->produce(); });
    std::thread consumer([this] { this->consume(); });
    producer.join();
    produce_finish_ = true;
    consumer.join();
  }

  void produce() {
    for (auto& data : test_data_) {
      queue_.enqueue(data);
    }
  }

  void consume() {
    for (auto expect : test_data_) {
    again:
      T data;
      if (!queue_.dequeue(data)) {
        if (produce_finish_) {
          if (!queue_.dequeue(data)) {
            FAIL("produce_finish_ too early");
            return;
          }
        } else {
          goto again;
        }
      }
      CHECK(data == expect);
    }
  }

 private:
  SPSCQueue<T> queue_;
  std::vector<T> test_data_;
  TestDataGenerator<T> test_data_generator_;
  std::atomic<bool> produce_finish_;
};

}  // namespace SQT

//////////////////////////////////////////////////////////////////////
TEST_CASE("SPSCQueue correct") {
  Benchmark bm;
  SQT::test<SQT::CorrectTest<int>, 2>();
  SQT::test<SQT::CorrectTest<int>, 0xff>();
  SQT::test<SQT::CorrectTest<int>, 0xffff>();
  SQT::test<SQT::CorrectTest<int>, 0xffffff>();
  SQT::test<SQT::CorrectTest<double>, 2>();
  SQT::test<SQT::CorrectTest<double>, 0xff>();
  SQT::test<SQT::CorrectTest<double>, 0xffff>();
  SQT::test<SQT::CorrectTest<double>, 0xffffff>();
  SQT::test<SQT::CorrectTest<std::string>, 2>();
  SQT::test<SQT::CorrectTest<std::string>, 0xff>();
  SQT::test<SQT::CorrectTest<std::string>, 0xffff>();
  SQT::test<SQT::CorrectTest<std::string>, 0xffffff>();
  bm.count("SPSCQueue correct");
}

TEST_CASE("SPSCQueue perf") {}

TEST_CASE("SPSCQueue destructor") {}

TEST_CASE("SPSCQueue empty and full") {}
