#include "NakedSingle.h"
#include "Direction.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn NakedSingle::solveStep(Grid& grid,
                                        const bool greedy) {
        SolverReturn returnVal(false, {}, {});

        for (Cell* cell : grid.getGroups(Group::ROW)) {
            for (Cell* runner = cell; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, Group::ROW)) {
                if (runner->solve()) {
                    std::get<bool>(returnVal) = true;
                    std::get<2>(returnVal)[runner];

                    if (!greedy) {
                        return returnVal;
                    }
                }
            }
        }

        return returnVal;
    }
}
