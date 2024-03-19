#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class CandidateRemoval : public Rule {
        public:
            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) override;
    };
}
