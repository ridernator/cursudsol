#pragma once

#include "Grid.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    class HiddenN : public Rule {
        public:
            HiddenN(const IntType n,
                    const std::string& name) : Rule(name),
                                               n(n) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;

        private:
            std::set<Cell*> findCells(Cell* groupStart,
                                      const Group group,
                                      std::vector<IntType> pms) const;

            const IntType n;
    };
}
