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

            SolverReturn solveStep();

            bool solve();

        private:
            Grid& grid;

            std::map<IntType, std::tuple<bool, bool, Rule*>> rules;

            std::size_t ruleIndex;
    };
}
