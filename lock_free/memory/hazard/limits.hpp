#pragma once

#include <cstdlib>

namespace hazard {

static constexpr size_t kMaxHazardPtrs = 6;  // Arbitrary
static constexpr size_t kMaxThreads = 100;  // Arbitrary
static constexpr size_t kRetiredCapacity = 2 *  kMaxThreads * kMaxHazardPtrs;

}  // namespace hazard
