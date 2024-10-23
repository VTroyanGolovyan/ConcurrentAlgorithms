#ifndef DEFER_HPP
#define DEFER_HPP

#include <functional>

namespace utils {

using Task = std::function<void()>;

class Defer {
public:
    explicit Defer(Task finalize);

    ~Defer();

private:
    Task finalize_;
};

}


#endif