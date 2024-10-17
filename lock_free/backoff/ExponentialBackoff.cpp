#include "ExponentioalBackoff.hpp"

#include <cstdlib>

void ExponentioalBackoff::operator()() {
    ++c;
    unsigned int k = 1u << c;
    usleep(static_cast<useconds_t>(slot_time_u * (rand() % k)));
}
