#pragma once

#include <cstddef>
#include <map>

#include "Grid.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    class Solver {
        public:
            Solver(Grid& grid);
            ~Solver();

            SolverReturn solveStep(const bool greedy = true);

            bool solve();

        private:
            Grid& grid;

            std::map<IntType, Rule*> rules;

            std::size_t ruleIndex;
    };
}
