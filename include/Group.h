#pragma once

#include <cstdint>
#include <vector>

namespace cursudsol {
    enum class Group : uint_fast8_t {
        ROW,
        COLUMN,
        BLOCK,
    };

    static const std::vector<Group> ALL_GROUPS = {Group::ROW, Group::COLUMN, Group::BLOCK};
}
