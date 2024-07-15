#pragma once

#include <unistd.h>

struct ExponentioalBackoff {
    void operator()();
private:
    float slot_time_u{51.2};
    int c{0};
};
