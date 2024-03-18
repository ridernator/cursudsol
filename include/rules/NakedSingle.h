#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class NakedSingle : public Rule {
        public:
            bool solveStep(Grid& grid,
                           const bool greedy = true) override;
    };
}
