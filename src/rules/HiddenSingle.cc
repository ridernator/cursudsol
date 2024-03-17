#include "HiddenSingle.h"
#include "Group.h"
#include "Order.h"

#include <cstdint>

namespace cursudsol {
    bool HiddenSingle::solveStep(Grid& grid,
                                 const bool greedy) {
        bool returnVal = false;

        for (const auto& group : ALL_GROUPS) {
            for (std::uint_fast8_t groupIndex = 0; groupIndex < Order::orderSq; ++groupIndex) {
                for (std::uint_fast8_t num = 0; num < Order::orderSq; ++num) {
                    Cell* cell = *(grid.getGroups(group) + groupIndex);
                    Cell* candidate;
                    std::uint_fast8_t count = 0;

                    // Count pencil marks with this number in the group
                    while (cell != nullptr) {
                        if (!cell->isFound()) {
                            if (cell->containsPencilMark(num)) {
                                candidate = cell;

                                if (++count > 1) {
                                    break;
                                }
                            }
                        }

                        cell = cell->getNextInGroup(group);
                    }

                    if (count == 1) {
                        for (std::uint_fast8_t otherNum = 0; otherNum < Order::orderSq; ++otherNum) {
                            if (otherNum != num) {
                                candidate->removePencilMark(otherNum);
                            }
                        }

                        if (greedy) {
                            returnVal = true;
                        } else {
                            return candidate->solve();
                        }
                    }
                }
            }
        }

        return returnVal;
    }
}
