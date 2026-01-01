// Copyright (c) 2021 The orientnet Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef UTIL_CONCURRENT_MPMC_QUEUE_H_
#define UTIL_CONCURRENT_MPMC_QUEUE_H_

template <typename T>
struct MPMCQueue {
  explicit MPMCQueue(std::uint32_t capacity) {}

  ~MPMCQueue() {}

  MPMCQueue(const MPMCQueue&) = delete;
  MPMCQueue& operator=(const MPMCQueue&) = delete;
  MPMCQueue(MPMCQueue&&) = delete;
  MPMCQueue& operator=(MPMCQueue&&) = delete;
};

#endif  // UTIL_CONCURRENT_MPMC_QUEUE_H_
