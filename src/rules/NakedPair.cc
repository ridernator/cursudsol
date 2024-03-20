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

        Cell* cell1;
        Cell* cell2;
        Cell* badCell;
        Cell* remover;

        const Order& order = grid.getOrder();

        for (const auto& group : ALL_GROUPS) {
            for (const auto& cell : grid.getGroups(group)) {
                cell1 = cell;

                while (cell1 != nullptr) {
                    success = false;

                    if ((!cell1->isFound()) && (cell1->countPencilMarks() == 2)) {
                        cell2 = cell1->getNeighbour(Direction::NEXT, group);

                        while (cell2 != nullptr) {
                            if ((!cell2->isFound()) &&
                                (cell2->countPencilMarks() == 2) &&
                                (comparePencilMarks(cell2, cell1, order.order2))) {
                                // Found matching pair. Now check there aren't any others
                                badCell = cell2->getNeighbour(Direction::NEXT, group);
                                thirdMatch = false;

                                while (badCell != nullptr) {
                                    if ((!badCell->isFound()) &&
                                        (badCell->countPencilMarks() == 2) &&
                                        (comparePencilMarks(badCell, cell1, order.order2))) {
                                        // Give up. Found 3rd candidate
                                        thirdMatch = true;

                                        break;
                                    }

                                    badCell = badCell->getNeighbour(Direction::NEXT, group);
                                }

                                if (!thirdMatch) {
                                    // Get rid
                                    for (IntType remove = 0; remove < order.order2; ++remove) {
                                        if (cell1->containsPencilMark(remove)) {
                                            remover = cell;

                                            while (remover != nullptr) {
                                                if ((!remover->isFound()) &&
                                                    (remover != cell1) &&
                                                    (remover != cell2) &&
                                                    (remover->containsPencilMark(remove))) {
                                                    remover->removePencilMark(remove);

                                                    std::get<0>(returnVal) = true;
                                                    std::get<1>(returnVal)[remover].insert(remove);
                                                    std::get<2>(returnVal)[cell1].insert(remove);
                                                    std::get<2>(returnVal)[cell2].insert(remove);

                                                    if (greedy) {
                                                        success = true;
                                                    } else {
                                                        return returnVal;
                                                    }
                                                }

                                                remover = remover->getNeighbour(Direction::NEXT, group);
                                            }
                                        }
                                    }
                                }

                                break;
                            }

                            cell2 = cell2->getNeighbour(Direction::NEXT, group);
                        }
                    }

                    if (success) {
                        break;
                    }

                    cell1 = cell1->getNeighbour(Direction::NEXT, group);
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
