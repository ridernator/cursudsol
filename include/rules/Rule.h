#pragma once

#include "Cell.h"
#include "Grid.h"
#include "Order.h"

#include <set>
#include <tuple>
#include <map>

namespace cursudsol {
    typedef std::tuple<bool, std::map<Cell*, std::set<IntType>>, std::map<Cell*, std::set<IntType>>> SolverReturn;

    class Rule {
        public:
            virtual ~Rule() {}

            virtual SolverReturn solveStep(Grid& grid,
                                           const bool greedy = true) = 0;
    };
}
