#pragma once

#include "HazardPtr.hpp"
#include "RetiredPtr.hpp"
#include "limits.hpp"

#include <array>
#include <list>
#include <iostream>
#include <algorithm>

namespace hazard {

struct ThreadState {
    ThreadState() : last_retired(0) {
        std::fill(retired_list.begin(), retired_list.end(), RetiredPtr{nullptr});
    }

    std::array<HazardPtr, kMaxHazardPtrs> slots{};
    std::array<RetiredPtr, kRetiredCapacity> retired_list{};
    size_t last_retired;
};

static std::array<ThreadState, kMaxThreads> states{};

}  // namespace hazard

