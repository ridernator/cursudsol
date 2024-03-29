#include "CandidateRemoval.h"
#include "Order.h"
#include "Rule.h"

#include <set>

namespace cursudsol {
    SolverReturn CandidateRemoval::solveStep(Grid& grid,
                                             const bool greedy) const {
        SolverReturn returnVal = DEFAULT_SOLVER_RETURN();

        Cell* cell;

        // Have to use flat data as we need to see found cells
        for (IntType index = 0; index < grid.getOrder().order4; ++index) {
            cell = grid.getFlatData()[index];

            if (cell->isFound()) {
                for (const auto& testCell : cell->getSeenCells()) {
                    if (testCell->containsPencilMark(cell->getValue())) {
                        testCell->removePencilMark(cell->getValue());

                        std::get<bool>(returnVal) = true;
                        std::get<1>(returnVal)[testCell].insert(cell->getValue());
                        std::get<2>(returnVal)[cell];
                    }
                }

                if ((std::get<bool>(returnVal)) &&
                    (!greedy)) {
                    break;
                }
            }
        }

        return returnVal;
    }

    extern "C" std::set<Rule*> createRules() {
        return { new CandidateRemoval() };
    }
}
