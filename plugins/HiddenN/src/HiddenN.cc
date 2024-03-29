#include "HiddenN.h"
#include "NDLoop.h"
#include "Order.h"
#include "Rule.h"
#include <algorithm>

namespace cursudsol {
    SolverReturn HiddenN::solveStep(Grid& grid,
                                    const bool) const {
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
                        for (Cell* cell : cells) {
                            for (IntType pm = 0; pm < grid.getOrder().order2; ++pm) {
                                if ((cell->containsPencilMark(pm)) &&
                                    (std::find(pms.begin(), pms.end(), pm) == pms.end())) {
                                    cell->removePencilMark(pm);

                                    std::get<bool>(returnVal) = true;
                                    std::get<1>(returnVal)[cell].insert(pm);

                                    for (Cell* cell1 : cells) {
                                        for (IntType becausePM : pms) {
                                            std::get<2>(returnVal)[cell1].insert(becausePM);
                                        }
                                    }
                                }
                            }
                        }

                        if (std::get<bool>(returnVal)) {
                            return returnVal;
                        }
                    }
                }
            }
        }

        return returnVal;
    }

    std::set<Cell*> HiddenN::findCells(Cell* groupStart,
                                       const Group group,
                                       std::vector<IntType> pms) const {
        std::set<Cell*> returnVal;
        bool goodCell;

        for (Cell* runner = groupStart; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
            goodCell = false;

            for (const IntType pm : pms) {
                if (runner->containsPencilMark(pm)) {
                    goodCell = true;

                    break;
                }
            }

            if (goodCell) {
                returnVal.insert(runner);
            }
        }

        return returnVal;
    }

    extern "C" std::set<Rule*> createRules() {
        return { new HiddenN(2, "HiddenPair"),
                 new HiddenN(3, "HiddenTriple"),
                 new HiddenN(4, "HiddenQuad") };
    }
}
