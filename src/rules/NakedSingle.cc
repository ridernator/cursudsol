#include "NakedSingle.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn NakedSingle::solveStep(Grid& grid,
                                        const bool greedy) {
        SolverReturn returnVal(false, {}, {});
        Cell* runner;

        for (const auto& cell : grid.getGroups(Group::ROW)) {
            runner = cell;

            while (runner != nullptr) {
                if (!runner->isFound()) {
                    if (runner->solve()) {
                        std::get<0>(returnVal) = true;
                        std::get<2>(returnVal)[runner];

                        if (!greedy) {
                            break;
                        }
                    }
                }

                runner = runner->getNeighbour(Direction::NEXT, Group::ROW);
            }
        }

        return returnVal;
    }
}
