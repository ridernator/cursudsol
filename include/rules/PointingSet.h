#pragma once

#include "Grid.h"
#include "Rule.h"

namespace cursudsol {
    class PointingSet : public Rule {
        public:
            PointingSet(const std::string& name = "PointingSet") : Rule(name) {}

            SolverReturn solveStep(Grid& grid,
                                   const bool greedy = true) const override;

        private:
            std::set<Cell*> findCells(Cell* groupStart,
                                      const Group group,
                                      const IntType pencilMark) const;

            bool areCellsInSameGroup(const std::set<Cell*> cells,
                                     Cell* groupStart,
                                     const Group group) const;
    };
}
