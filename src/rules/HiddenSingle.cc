#include "HiddenSingle.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn HiddenSingle::solveStep(Grid& grid,
                                         const bool) {
        const Order& order = grid.getOrder();
        SolverReturn returnVal(false, {}, {});
        Cell* looper;
        Cell* candidate;
        IntType count;

        for (const auto& group : ALL_GROUPS) {
            for (const auto& cell : grid.getGroups(group)) {
                for (IntType num = 0; num < order.order2; ++num) {
                    looper = cell;
                    count = 0;

                    // Count pencil marks with this number in the group
                    while (looper != nullptr) {
                        if ((!looper->isFound()) &&
                            (looper->containsPencilMark(num))) {
                            candidate = looper;

                            if (++count > 1) {
                                break;
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
                        candidate->solve();

                        std::get<0>(returnVal) = true;

                        return returnVal;
                    }
                }
            }
        }

        return returnVal;
    }
}
