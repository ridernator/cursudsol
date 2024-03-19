#include "NakedSingle.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn NakedSingle::solveStep(Grid& grid,
                                        const bool greedy) {
        SolverReturn returnVal(false, {}, {});

        for (IntType index = 0; index < grid.getOrder().order4; ++index) {
            if (!grid.getFlatData()[index]->isFound()) {
                if (grid.getFlatData()[index]->solve()) {
                    std::get<0>(returnVal) = true;

                    if (!greedy) {
                        break;
                    }
                }
            }
        }

        return returnVal;
    }
}
