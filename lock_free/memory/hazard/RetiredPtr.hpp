#pragma once

#include <functional>

namespace hazard {

using Deleter = std::function<void(void*)>;

struct RetiredPtr {
  void* object{nullptr};
  Deleter deleter;
};



template <typename T>
RetiredPtr Retired(T* ptr) {
  auto deleter = [](void* ptr) {
    delete reinterpret_cast<T*>(ptr);
  };
  return RetiredPtr{ptr, deleter};
}

}  // namespace hazard
