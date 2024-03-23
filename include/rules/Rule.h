#pragma once

#include "Cell.h"
#include "Grid.h"
#include "Order.h"

#include <set>
#include <string>
#include <tuple>
#include <map>

namespace cursudsol {
    typedef std::tuple<bool, std::map<Cell*, std::set<IntType>>, std::map<Cell*, std::set<IntType>>> SolverReturn;

    class Rule {
        public:
            Rule(const std::string& name);

            virtual ~Rule() {}

            virtual SolverReturn solveStep(Grid& grid,
                                           const bool greedy = true) const = 0;

            const std::string& getName() const;

        private:
            const std::string name;
    };
}
