#pragma once

#include "Grid.h"
#include "Rule.h"
#include <string>

namespace cursudsol {
    class HiddenPair : public Rule {
        public:
            HiddenPair(const std::string& name = "HiddenPair") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;
    };
}
