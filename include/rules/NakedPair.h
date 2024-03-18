#pragma once

#include "Grid.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    class NakedPair : public Rule {
        public:
            bool solveStep(Grid& grid,
                           const bool greedy = true) override;

        private:
            bool comparePencilMarks(Cell* a,
                                    Cell* b,
                                    const IntType count);
    };
}
