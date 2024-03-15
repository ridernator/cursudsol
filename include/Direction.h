#pragma once

#include <cstdint>

namespace cursudsol {
    enum Direction : uint_fast8_t {
        NEXT = 0,
        PREVIOUS = NEXT + 1,
        NUM_DIRECTIONS = PREVIOUS + 1
    };
}
