#include "util/concurrent/blocking_queue.h"

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "test/3rdparty/doctest/doctest.h"
#include "test/benchmark.h"

namespace {

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
  CorrectTest(std::uint32_t capacity) : produce_finish_(false) {
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

}  // namespace

//////////////////////////////////////////////////////////////////////
TEST_CASE("BlockingQueue correct") {
//   Benchmark bm;
//   test<CorrectTest<int>, 2>();
//   test<CorrectTest<int>, 0xff>();
//   test<CorrectTest<int>, 0xffff>();
//   test<CorrectTest<int>, 0xffffff>();
//   test<CorrectTest<double>, 2>();
//   test<CorrectTest<double>, 0xff>();
//   test<CorrectTest<double>, 0xffff>();
//   test<CorrectTest<double>, 0xffffff>();
//   test<CorrectTest<std::string>, 2>();
//   test<CorrectTest<std::string>, 0xff>();
//   test<CorrectTest<std::string>, 0xffff>();
//   test<CorrectTest<std::string>, 0xffffff>();
//   bm.count("BlockingQueue correct");
}

TEST_CASE("BlockingQueue perf") {}

TEST_CASE("BlockingQueue destructor") {}

TEST_CASE("BlockingQueue empty and full") {}
