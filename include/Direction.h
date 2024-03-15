#pragma once

#include <cstdint>
#include <vector>

namespace cursudsol {
    enum Direction : uint_fast8_t {
        NEXT = 0,
        PREVIOUS = NEXT + 1,
        NUM_DIRECTIONS = PREVIOUS + 1
    };

    static const std::vector<Direction> ALL_DIRECTIONS = {Direction::NEXT, Direction::PREVIOUS};
}
