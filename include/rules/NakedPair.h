#pragma once

#include "Grid.h"
#include "Order.h"
#include "Rule.h"
#include <string>

namespace cursudsol {
    class NakedPair : public Rule {
        public:
            NakedPair(const std::string& name = "NakedPair") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;

        private:
            bool comparePencilMarks(Cell* a,
                                    Cell* b,
                                    const IntType count) const;
    };
}
