#pragma once

#include <atomic>

namespace hazard {

struct HazardPtr {
  HazardPtr() = default;

  void Set(void* ptr);

  void* Get();

  void Reset();

 private:
  std::atomic<void*> ptr_{nullptr};
};

}  // namespace hazard
