#pragma once

#include "Cell.h"
#include "Grid.h"
#include "Order.h"

#include <tuple>
#include <map>
#include <vector>

namespace cursudsol {
    typedef std::tuple<bool, std::map<Cell*, std::vector<IntType>>, std::map<Cell*, std::vector<IntType>>> SolverReturn;

    class Rule {
        public:
            virtual ~Rule() {}

            virtual SolverReturn solveStep(Grid& grid,
                                           const bool greedy = true) = 0;
    };
}
