#pragma once

#include "Mutator.hpp"

namespace hazard {

static std::atomic<size_t> last_thread_id{0};

thread_local size_t state_id{last_thread_id.fetch_add(1)};

class Manager {
  friend class Mutator;
 public:
  static Manager& Get()  {
    return manager_;
  }

  Mutator MakeMutator() {
    return Mutator(this, &states[state_id]);
  }

  ~Manager() = default;

 private:
  static Manager manager_;
};

Manager Manager::manager_ = {};

}  // namespace hazard

