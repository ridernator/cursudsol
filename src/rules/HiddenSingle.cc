#include "HiddenSingle.h"
#include "Group.h"
#include "Order.h"

#include <cstdint>

namespace cursudsol {
    bool HiddenSingle::solveStep(Grid& grid,
                                 const bool greedy) {
        const Order& order = grid.getOrder();
        bool returnVal = false;
        Cell* looper;
        Cell* candidate;
        IntType count;

        for (const auto& group : ALL_GROUPS) {
            for (const auto& cell : grid.getGroups(group)) {
                for (std::uint_fast8_t num = 0; num < order.order2; ++num) {
                    looper = cell;
                    count = 0;

                    // Count pencil marks with this number in the group
                    while (looper != nullptr) {
                        if (!looper->isFound()) {
                            if (looper->containsPencilMark(num)) {
                                candidate = looper;

                                if (++count > 1) {
                                    break;
                                }
                            }
                        }

                        looper = looper->getNeighbour(Direction::NEXT, group);
                    }

                    if (count == 1) {
                        for (IntType otherNum = 0; otherNum < order.order2; ++otherNum) {
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
