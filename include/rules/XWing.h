#pragma once

#include "Grid.h"
#include "Group.h"
#include "Rule.h"

namespace cursudsol {
    class XWing : public Rule {
        public:
            XWing(const std::string& name = "X-Wing") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;

        private:
            std::set<Cell*> getGroupStarts(const std::set<Cell*>& cells,
                                           const Group groupType) const;
    };
}
