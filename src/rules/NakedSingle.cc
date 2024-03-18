#include "NakedSingle.h"
#include "Order.h"

namespace cursudsol {
    bool NakedSingle::solveStep(Grid& grid,
                                const bool greedy) {
        bool returnVal = false;

        for (IntType index = 0; index < grid.getOrder().order4; ++index) {
            if (!grid.getFlatData()[index]->isFound()) {
                if (grid.getFlatData()[index]->solve()) {
                    if (greedy) {
                        returnVal = true;
                    } else {
                        return true;
                    }
                }
            }
        }

        return returnVal;
    }
}
