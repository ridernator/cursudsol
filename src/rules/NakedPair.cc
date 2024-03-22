#include "NakedPair.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn NakedPair::solveStep(Grid& grid,
                                      const bool greedy) {
        SolverReturn returnVal(false, {}, {});
        bool success;
        bool thirdMatch;

        const Order& order = grid.getOrder();

        for (const Group group : ALL_GROUPS) {
            for (Cell* groupStart : grid.getGroups(group)) {
                for (Cell* cell1 = groupStart; cell1 != nullptr; cell1 = cell1->getNeighbour(Direction::NEXT, group)) {
                    success = false;

                    if (cell1->countPencilMarks() == 2) {
                        for (Cell* cell2 = cell1->getNeighbour(Direction::NEXT, group); cell2 != nullptr; cell2 = cell2->getNeighbour(Direction::NEXT, group)) {
                            if ((cell2->countPencilMarks() == 2) &&
                                (comparePencilMarks(cell2, cell1, order.order2))) {
                                // Found matching pair. Now check there aren't any others
                                thirdMatch = false;
                                for (Cell* badCell = cell2->getNeighbour(Direction::NEXT, group); badCell != nullptr; badCell = badCell->getNeighbour(Direction::NEXT, group)) {
                                    if ((badCell->countPencilMarks() == 2) &&
                                        (comparePencilMarks(badCell, cell1, order.order2))) {
                                        // Give up. Found 3rd candidate
                                        thirdMatch = true;

                                        break;
                                    }
                                }

                                if (!thirdMatch) {
                                    // Get rid
                                    for (const IntType remove : cell1->getPencilMarks()) {
                                        if (cell1->containsPencilMark(remove)) {
                                            for (Cell* remover = groupStart; remover != nullptr; remover = remover->getNeighbour(Direction::NEXT, group)) {
                                                if ((remover != cell1) &&
                                                    (remover != cell2) &&
                                                    (remover->containsPencilMark(remove))) {
                                                    remover->removePencilMark(remove);

                                                    std::get<bool>(returnVal) = true;
                                                    std::get<1>(returnVal)[remover].insert(remove);

                                                    for (const IntType because : cell1->getPencilMarks()) {
                                                        std::get<2>(returnVal)[cell1].insert(because);
                                                        std::get<2>(returnVal)[cell2].insert(because);
                                                    }

                                                    success = true;
                                                }
                                            }
                                        }
                                    }

                                    if ((std::get<bool>(returnVal)) &&
                                        (!greedy)) {
                                        return returnVal;
                                    }
                                }

                                break;
                            }
                        }
                    }

                    if (success) {
                        break;
                    }
                }
            }
        }

        return returnVal;
    }

    bool NakedPair::comparePencilMarks(Cell* a,
                                       Cell* b,
                                       const IntType count) {
        for (IntType index = 0; index < count; ++index) {
            if (a->containsPencilMark(index) != b->containsPencilMark(index)) {
                return false;
            }
        }

        return true;
    }
}
