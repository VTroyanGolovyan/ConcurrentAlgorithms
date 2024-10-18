#include "HazardPtr.hpp"

namespace hazard {

void HazardPtr::Set(void* ptr) {
    ptr_.store(ptr);
}

void* HazardPtr::Get() {
    return ptr_.load();
}

void HazardPtr::Reset() {
    ptr_.store(nullptr);
}

}  // namespace hazard
