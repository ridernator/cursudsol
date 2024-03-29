#include "XWing.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"
#include <cstddef>

namespace cursudsol {
    SolverReturn XWing::solveStep(Grid& grid,
                                  const bool greedy) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();
        std::set<IntType> allPMs;
        std::set<Cell*> cells1;
        std::set<Cell*> cells2;
        std::set<Cell*> allCells;
        std::set<Cell*> groupStarts;
        IntType order2 = grid.getOrder().order2;

        for (Group group1 : ALL_GROUPS) {
            for (Group group2 : ALL_GROUPS) {
                if (group1 != group2) {
                    for (IntType pm = 0; pm < order2; ++pm) {
                        for (std::size_t index1 = 0; index1 < order2; ++index1) {
                            cells1 = findCellsWithPencilMark(grid.getGroups(group1)[index1], group1, pm);
                            if (cells1.size() == 2) {
                                for (std::size_t index2 = index1 + 1; index2 < order2; ++index2) {
                                    cells2 = findCellsWithPencilMark(grid.getGroups(group1)[index2], group1, pm);

                                    if (cells2.size() == 2) {
                                        allCells.clear();
                                        allCells.insert(cells1.begin(), cells1.end());
                                        allCells.insert(cells2.begin(), cells2.end());

                                        groupStarts = getGroupStarts(allCells, group2);

                                        if (groupStarts.size() == 2) {
                                            for (Cell* cell : groupStarts) {
                                                for (Cell* runner = cell; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group2)) {
                                                    if (!allCells.contains(runner)) {
                                                        if (runner->containsPencilMark(pm)) {
                                                            runner->removePencilMark(pm);

                                                            std::get<bool>(returnVal) = true;
                                                            std::get<1>(returnVal)[runner].insert(pm);

                                                            for (Cell* because : allCells) {
                                                                std::get<2>(returnVal)[because].insert(pm);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    if ((std::get<bool>(returnVal)) &&
                                        (!greedy)) {
                                        return returnVal;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return returnVal;
    }

    std::set<Cell*> XWing::getGroupStarts(const std::set<Cell*>& cells,
                                          const Group groupType) const {
        std::set<Cell*> returnVal;

        for (const Cell* cell : cells) {
            returnVal.insert(getGroupStart(cell, groupType));
        }

        return returnVal;
    }

    extern "C" std::set<Rule*> createRules() {
        return { new XWing() };
    }
}
