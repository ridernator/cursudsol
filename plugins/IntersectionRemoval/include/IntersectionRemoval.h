#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class IntersectionRemoval : public Rule {
        public:
            IntersectionRemoval(const std::string& name = "IntersectionRemoval") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;

        private:
            std::set<Cell*> findCells(Cell* groupStart,
                                      const Group group,
                                      const IntType pencilMark) const;

            bool areCellsInSameGroup(const std::set<Cell*>& cells,
                                     Cell* groupStart,
                                     const Group group) const;
    };
}
