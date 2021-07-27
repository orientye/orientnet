// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "util/concurrent/blocking_queue.h"

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "test/3rdparty/doctest/doctest.h"
#include "test/benchmark.h"

namespace BQT {

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
  explicit CorrectTest(std::uint32_t capacity) : produce_finish_(false) {
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
      T data;
      queue_.dequeue(data);
      CHECK(data == expect);
    }
  }

 private:
  BlockingQueue<T> queue_;
  std::vector<T> test_data_;
  TestDataGenerator<T> test_data_generator_;
  std::atomic<bool> produce_finish_;
};

}  // namespace BQT

//////////////////////////////////////////////////////////////////////
TEST_CASE("BlockingQueue correct") {
    Benchmark bm;
    BQT::test<BQT::CorrectTest<int>, 2>();
    BQT::test<BQT::CorrectTest<int>, 0xff>();
    BQT::test<BQT::CorrectTest<int>, 0xffff>();
    BQT::test<BQT::CorrectTest<int>, 0xffffff>();
    BQT::test<BQT::CorrectTest<double>, 2>();
    BQT::test<BQT::CorrectTest<double>, 0xff>();
    BQT::test<BQT::CorrectTest<double>, 0xffff>();
    BQT::test<BQT::CorrectTest<double>, 0xffffff>();
    BQT::test<BQT::CorrectTest<std::string>, 2>();
    BQT::test<BQT::CorrectTest<std::string>, 0xff>();
    BQT::test<BQT::CorrectTest<std::string>, 0xffff>();
    BQT::test<BQT::CorrectTest<std::string>, 0xffffff>();
    bm.count("BlockingQueue correct");
}

TEST_CASE("BlockingQueue perf") {}

TEST_CASE("BlockingQueue destructor") {}

TEST_CASE("BlockingQueue empty and full") {}
