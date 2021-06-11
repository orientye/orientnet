#include "util/concurrent/spin_lock.h"

//std

#include "test/3rdparty/doctest/doctest.h"

//////////////////////////////////////////////////////////////////////
TEST_CASE("SPINLOCK correct") {
    SpinLock sl;
    sl.lock();
    sl.unlock();
}

TEST_CASE("SPINLOCK perf") {}
