#pragma once

#include <cstdint>
#include <vector>

namespace cursudsol {
    enum Group : uint_fast8_t {
        ROW = 0,
        COLUMN = ROW + 1,
        BLOCK = COLUMN + 1,
        NUM_GROUPS = BLOCK + 1
    };

    static const std::vector<Group> ALL_GROUPS = {Group::ROW, Group::COLUMN, Group::BLOCK};
}
