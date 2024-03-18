#pragma once

#include <cstdint>
#include <vector>

namespace cursudsol {
    enum class Direction : uint_fast8_t {
        NEXT,
        PREVIOUS,
    };

    static const std::vector<Direction> ALL_DIRECTIONS = {Direction::NEXT, Direction::PREVIOUS};
}
