#pragma once

#include "Grid.h"
#include "Rule.h"
#include <string>

namespace cursudsol {
    class NakedSingle : public Rule {
        public:
            NakedSingle(const std::string& name = "NakedSingle") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;
    };
}
