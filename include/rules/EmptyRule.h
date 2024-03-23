#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class EmptyRule : public Rule {
        public:
            EmptyRule(const std::string& name = "EmptyRule") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;
    };
}
