#include "HiddenPair.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn HiddenPair::solveStep(Grid& grid,
                                      const bool) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();

        Cell* start;
        std::set<IntType> allPMs;
        std::set<Cell*> cellSet;

        for (const Group& group : ALL_GROUPS) {
            for (IntType groupIndex = 0; groupIndex < grid.getOrder().order2; ++groupIndex) {
                start = grid.getGroups(group)[groupIndex];
                allPMs.clear();

                for (Cell* runner = start; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
                    allPMs.insert(runner->getPencilMarks().begin(), runner->getPencilMarks().end());
                }

                if (allPMs.size() > 2) {
                    for (auto index1 = allPMs.begin(); index1 != allPMs.end(); ++index1) {
                        for (auto index2 = index1; ++index2 != allPMs.end();) {
                            cellSet.clear();

                            for (Cell* runner = start; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, group)) {
                                if ((runner->containsPencilMark(*index1)) ||
                                    (runner->containsPencilMark(*index2))) {
                                    cellSet.insert(runner);
                                }
                            }

                            if (cellSet.size() == 2) {
                                for (Cell* remover : cellSet) {
                                    for (IntType remove = 0; remove < grid.getOrder().order2; ++remove) {
                                        if ((remove != *index1) &&
                                            (remove != *index2) &&
                                            (remover->containsPencilMark(remove))) {
                                            remover->removePencilMark(remove);

                                            std::get<bool>(returnVal) = true;
                                            std::get<1>(returnVal)[remover].insert(remove);
                                            std::get<2>(returnVal)[remover].insert(*index1);
                                            std::get<2>(returnVal)[remover].insert(*index2);
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
            }
        }

        return returnVal;
    }
}
