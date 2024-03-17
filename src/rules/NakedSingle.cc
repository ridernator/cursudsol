#include "NakedSingle.h"
#include "Order.h"
#include <cstddef>

namespace cursudsol {
    bool NakedSingle::solveStep(Grid& grid,
                                const bool greedy) {
        bool returnVal = false;

        for (std::size_t index = 0; index < Order::orderSq * Order::orderSq; ++index) {
            if (!grid.getFlatData()[index].isFound()) {
                if (grid.getFlatData()[index].solve()) {
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
