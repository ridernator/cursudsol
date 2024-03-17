#pragma once

#include "Grid.h"

namespace cursudsol {
    class Rule {
        public:
            virtual ~Rule() {}

            virtual bool solveStep(Grid& grid,
                                   const bool greedy = true) = 0;
    };
}
