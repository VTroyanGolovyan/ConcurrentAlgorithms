#ifndef TASK_HPP
#define TASK_HPP

#include <functional>

namespace synchronize {

namespace tp {

// can be replaced with fastest analogue
using Task = std::function<void()>;

}

}

#endif
