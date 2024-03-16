#include "NakedSingle.h"
#include "Order.h"
#include <cstddef>

namespace cursudsol {
    bool NakedSingle::solveStep(Grid& grid) {
        bool returnVal = false;

        for (std::size_t index = 0; index < Order::orderSq * Order::orderSq; ++index) {
            if (!grid.getFlatData()[index].isFound()) {
                returnVal |= grid.getFlatData()[index].solve();
            }
        }

        return returnVal;
    }
}
