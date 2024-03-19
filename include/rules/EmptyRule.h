#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class EmptyRule : public Rule {
        public:
            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) override;
    };
}
