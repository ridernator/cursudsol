#include "IntersectionRemoval.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn IntersectionRemoval::solveStep(Grid& grid,
                                                const bool greedy) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();
        std::set<IntType> allPMs;
        std::set<Cell*> cells;

        for (const Group group : ALL_GROUPS) {
            for (Cell* groupStart : grid.getGroups(group)) {
                allPMs.clear();

                for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
                    allPMs.insert(runner->getPencilMarks().begin(), runner->getPencilMarks().end());
                }

                for (IntType pm : allPMs) {
                    cells = findCells(groupStart, group, pm);

                    if ((!cells.empty()) &&
                        (cells.size() <= grid.getOrder().order)) {
                        for (const Group intersectingGroup : ALL_GROUPS) {
                            if (intersectingGroup != group) {
                                Cell* gs = *cells.begin();
                                while (gs->getNeighbour(Direction::PREVIOUS, intersectingGroup) != nullptr) {
                                    gs = gs->getNeighbour(Direction::PREVIOUS, intersectingGroup);
                                }

                                if (areCellsInSameGroup(cells, gs, intersectingGroup)) {
                                    for (Cell* runner = gs; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, intersectingGroup)) {
                                        if (!cells.contains(runner)) {
                                            if (runner->containsPencilMark(pm)) {
                                                runner->removePencilMark(pm);

                                                std::get<bool>(returnVal) = true;
                                                std::get<1>(returnVal)[runner].insert(pm);

                                                for (Cell* because : cells) {
                                                    std::get<2>(returnVal)[because].insert(pm);
                                                }
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

        return returnVal;
    }

    std::set<Cell*> IntersectionRemoval::findCells(Cell* groupStart,
                                                   const Group group,
                                                   const IntType pencilMark) const {
        std::set<Cell*> returnVal;

        for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
            if (runner->containsPencilMark(pencilMark)) {
                returnVal.insert(runner);
            }
        }

        return returnVal;
    }

    bool IntersectionRemoval::areCellsInSameGroup(const std::set<Cell*>& cells,
                                                  Cell* groupStart,
                                                  const Group group) const {
        Cell* runner;

        for (Cell* cell : cells) {
            runner = cell;

            while (runner->getNeighbour(Direction::PREVIOUS, group) != nullptr) {
                runner = runner->getNeighbour(Direction::PREVIOUS, group);
            }

            if (runner != groupStart) {
                return false;
            }
        }

        return true;
    }
}
