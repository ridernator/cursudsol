#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class HiddenPair : public Rule {
        public:
            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) override;
    };
}
