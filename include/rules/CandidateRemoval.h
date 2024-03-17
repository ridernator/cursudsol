#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class CandidateRemoval : public Rule {
        bool solveStep(Grid& grid,
                       const bool greedy = true) override;
    };
}
