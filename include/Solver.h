#pragma once

#include <cstddef>
#include <vector>

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class Solver {
        public:
            Solver(Grid& grid);
            ~Solver();

            SolverReturn solveStep();

        private:
            Grid& grid;

            std::vector<Rule*> rules;

            std::size_t ruleIndex;
    };
}
