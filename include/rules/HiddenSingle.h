#pragma once

#include "Grid.h"
#include "Rule.h"
#include <string>

namespace cursudsol {
    class HiddenSingle : public Rule {
        public:
            HiddenSingle(const std::string& name = "HiddenSingle") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;
    };
}
