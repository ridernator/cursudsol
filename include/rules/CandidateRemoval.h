#pragma once

#include "Grid.h"
#include "Rule.h"
#include <string>

namespace cursudsol {
    class CandidateRemoval : public Rule {
        public:
            CandidateRemoval(const std::string& name = "CandidateRemoval") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;
    };
}
