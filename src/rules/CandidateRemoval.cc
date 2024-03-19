#include "CandidateRemoval.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"

namespace cursudsol {
    bool CandidateRemoval::solveStep(Grid& grid,
                                     const bool greedy) {
        bool returnVal = false;
        Cell* cell;
        Cell* testCell;

        for (IntType index = 0; index < grid.getOrder().order4; ++index) {
            cell = grid.getFlatData()[index];

            if (cell->isFound()) {
                for (const auto& direction : ALL_DIRECTIONS) {
                    for (const auto& group : ALL_GROUPS) {
                        testCell = cell->getNeighbour(direction, group);

                        while (testCell != nullptr) {
                            if ((!testCell->isFound()) &&
                                (testCell->containsPencilMark(cell->getValue()))) {
                                testCell->removePencilMark(cell->getValue());

                                if (greedy) {
                                    returnVal = true;
                                } else {
                                    return true;
                                }
                            }

                            testCell = testCell->getNeighbour(direction, group);
                        }
                    }
                }
            }
        }

        return returnVal;
    }
}
