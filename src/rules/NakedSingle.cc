#include "NakedSingle.h"
#include "Order.h"
#include <cstddef>

namespace cursudsol {
    bool NakedSingle::solveStep(Grid& grid) {
        for (std::size_t index = 0; index < Order::orderSq * Order::orderSq; ++index) {
            if (!grid.getFlatData()[index].isFound()) {
                if (grid.getFlatData()[index].solve()) {
                    return true;
                }
            }
        }

        return false;
    }
}
