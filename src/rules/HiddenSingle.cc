#include "HiddenSingle.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn HiddenSingle::solveStep(Grid& grid,
                                         const bool) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();

        const Order& order = grid.getOrder();
        Cell* candidate;
        IntType count;

        for (const Group group : ALL_GROUPS) {
            for (Cell* cell : grid.getGroups(group)) {
                for (IntType num = 0; num < order.order2; ++num) {
                    count = 0;

                    // Count pencil marks with this number in the group
                    for (Cell* runner = cell; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
                        if (runner->containsPencilMark(num)) {
                            candidate = runner;

                            if (++count > 1) {
                                break;
                            }
                        }
                    }

                    if (count == 1) {
                        for (IntType otherNum = 0; otherNum < order.order2; ++otherNum) {
                            if (otherNum != num) {
                                candidate->removePencilMark(otherNum);
                            }
                        }
                        candidate->solve();

                        std::get<bool>(returnVal) = true;
                        std::get<2>(returnVal)[candidate];

                        return returnVal;
                    }
                }
            }
        }

        return returnVal;
    }
}
