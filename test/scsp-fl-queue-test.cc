#include "util/concurrent/scsp-fl-queue.h"

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "doctest/doctest.h"

namespace {

template <class TestType>
void test() {
  std::unique_ptr<TestType> const t(new TestType());
  (*t)();
}

template <typename T>
class CorrectTest {
 public:
  CorrectTest() {}

  void operator()() {
    std::thread producer([this] { this->produce(); });
    std::thread consumer([this] { this->consume(); });
    producer.join();
    produce_finish_ = true;
    consumer.join();
  }

  void produce() {}

  void consume() {}

 private:
  SCSPFixedLengthQueue<T> queue_;
  std::vector<T> testdata_;
  std::atomic<bool> produce_finish_;
};

}  // namespace

//////////////////////////////////////////////////////////////////////
TEST_CASE("SCSPFQ correct") {}

TEST_CASE("SCSPFQ perf") {}

TEST_CASE("SCSPFQ destructor") {}

TEST_CASE("SCSPFQ empty and full") {}
