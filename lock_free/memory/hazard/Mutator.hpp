#pragma once

#include "fwd.hpp"
#include "thread.hpp"
#include "PtrGuard.hpp"

#include <cstdlib>
#include <algorithm>
#include <iostream>

namespace hazard {

class Mutator {
 public:
  Mutator(Manager* manager, ThreadState* thread)
      : manager_(manager),
        thread_(thread) {
  }

  PtrGuard GetHazardPtr(size_t index) {
    return PtrGuard{&(thread_->slots[index])};
  }

  template <typename T>
  void Retire(T* object) {
    thread_->retired_list[thread_->last_retired++] = Retired(object);
    if (thread_->last_retired < kRetiredCapacity) {
        return;
    }

    std::array<void*, kMaxThreads * kMaxHazardPtrs> all_hazard{};

    size_t cnt = 0;
    for (size_t i = 0; i < kMaxThreads; ++i) {
        for (auto& slot : states[i].slots) {
            auto* ptr = slot.Get();
            if (ptr != nullptr) {
                all_hazard[cnt++] = ptr;
            }
        }
    }

    std::sort(all_hazard.begin(), all_hazard.begin() + cnt);

    std::array<RetiredPtr, kRetiredCapacity> new_retired_list{};
    size_t new_cnt = 0;
    for (auto& retired : thread_->retired_list) {
        if (std::binary_search(all_hazard.begin(), all_hazard.begin() + cnt, retired.object)) {
           new_retired_list[new_cnt++] = retired;
        } else {
           retired.deleter(retired.object);
        }
    }

    std::copy(new_retired_list.begin(), new_retired_list.end(), thread_->retired_list.begin());
    
    thread_->last_retired = new_cnt;
  }

 private:
  [[maybe_unused]] Manager* manager_;
  ThreadState* thread_;
};

}  // namespace hazard
