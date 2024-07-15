#pragma once

#include "HazardPtr.hpp"
#include <atomic>

namespace hazard {

struct PtrGuard {
  friend class Mutator;

 public:
  PtrGuard(const PtrGuard&) = default;
  PtrGuard& operator=(const PtrGuard&) = default;
  
  PtrGuard(PtrGuard&&) = delete;
  PtrGuard& operator=(PtrGuard&&) = delete;

  template <typename T>
  T* Protect(std::atomic<T*>& atomic_ptr) {
    T* ptr;
    do {
      ptr = atomic_ptr.load();
      slot_->Set(ptr);
    } while (ptr != atomic_ptr.load());
    return ptr;
  }

  void Reset() {
    slot_->Reset();
  }

  ~PtrGuard() {
    Reset();
  }

 private:
  explicit PtrGuard(HazardPtr* slot)
      : slot_(slot) {
  }

 private:
  HazardPtr* slot_;
};

}  // namespace hazard
