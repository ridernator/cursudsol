#pragma once

#include <cstdint>

namespace cursudsol {
    enum Group : uint_fast8_t {
        ROW = 0,
        COLUMN = ROW + 1,
        BLOCK = COLUMN + 1,
        NUM_GROUPS = BLOCK + 1
    };
}
