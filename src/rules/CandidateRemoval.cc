#include "CandidateRemoval.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn CandidateRemoval::solveStep(Grid& grid,
                                             const bool greedy) {
        SolverReturn returnVal(false, {}, {});
        Cell* cell;

        for (IntType index = 0; index < grid.getOrder().order4; ++index) {
            cell = grid.getFlatData()[index];

            if (cell->isFound()) {
                for (const auto& testCell : cell->getSeenCells()) {
                    if ((!testCell->isFound()) &&
                        (testCell->containsPencilMark(cell->getValue()))) {
                        testCell->removePencilMark(cell->getValue());

                        std::get<0>(returnVal) = true;
                        std::get<1>(returnVal)[testCell].push_back(cell->getValue());

                        if (!greedy) {
                            return returnVal;
                        }
                    }
                }
            }
        }

        return returnVal;
    }
}
