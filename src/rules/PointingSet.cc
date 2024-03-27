#include "PointingSet.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn PointingSet::solveStep(Grid& grid,
                                        const bool greedy) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();
        std::set<IntType> allPMs;

        for (Cell* groupStart : grid.getGroups(Group::BLOCK)) {
            allPMs.clear();

            for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, Group::BLOCK)) {
                allPMs.insert(runner->getPencilMarks().begin(), runner->getPencilMarks().end());
            }

            for (IntType pm : allPMs) {
                std::set<Cell*> cells = findCells(groupStart, Group::BLOCK, pm);

                if ((!cells.empty()) &&
                    (cells.size() <= grid.getOrder().order)) {
                    for (const Group group : ALL_GROUPS) {
                        if (group != Group::BLOCK) {
                            Cell* gs = *cells.begin();
                            while (gs->getNeighbour(Direction::PREVIOUS, group) != nullptr) {
                                gs = gs->getNeighbour(Direction::PREVIOUS, group);
                            }

                            if (areCellsInSameGroup(cells, gs, group)) {
                                for (Cell* runner = gs; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
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

        return returnVal;
    }

    std::set<Cell*> PointingSet::findCells(Cell* groupStart,
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

    bool PointingSet::areCellsInSameGroup(const std::set<Cell*> cells,
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
