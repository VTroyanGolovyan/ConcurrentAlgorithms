#include "Defer.hpp"

namespace utils {

using Task = std::function<void()>;

Defer::Defer(Task finalize) : finalize_(std::move(finalize)) {}

Defer::~Defer() { 
    finalize_(); 
}

}
