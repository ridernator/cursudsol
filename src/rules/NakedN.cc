#include "NakedN.h"
#include "NDLoop.h"
#include "Order.h"
#include "Rule.h"
#include <algorithm>

namespace cursudsol {
    SolverReturn NakedN::solveStep(Grid& grid,
                                   const bool greedy) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();
        std::set<IntType> allPMs;

        for (const Group group : ALL_GROUPS) {
            for (Cell* groupStart : grid.getGroups(group)) {
                allPMs.clear();

                for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
                    allPMs.insert(runner->getPencilMarks().begin(), runner->getPencilMarks().end());
                }

                NDLoop ndLoop(n, allPMs);

                for (auto pms = ndLoop.next(); !pms.empty(); pms = ndLoop.next()) {
                    std::set<Cell*> cells = findCells(groupStart, group, pms);

                    if (cells.size() == n) {
                        for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
                            if (!cells.contains(runner)) {
                                for (const IntType pm : pms) {
                                    if (runner->containsPencilMark(pm)) {
                                        runner->removePencilMark(pm);

                                        std::get<bool>(returnVal) = true;
                                        std::get<1>(returnVal)[runner].insert(pm);

                                        for (Cell* cell : cells) {
                                            for (IntType becausePM : pms) {
                                                std::get<2>(returnVal)[cell].insert(becausePM);
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

        return returnVal;
    }

    std::set<Cell*> NakedN::findCells(Cell* groupStart,
                                      const Group group,
                                      std::vector<IntType> pms) const {
        std::set<Cell*> returnVal;
        bool badPM;

        for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
            badPM = false;

            for (IntType pm : runner->getPencilMarks()) {
                if (std::find(pms.begin(), pms.end(), pm) == pms.end()) {
                    badPM = true;

                    break;
                }
            }

            if (!badPM) {
                returnVal.insert(runner);
            }
        }

        return returnVal;
    }
}
