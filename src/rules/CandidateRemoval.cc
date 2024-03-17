#include "CandidateRemoval.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"
#include <cstdint>

namespace cursudsol {
    bool CandidateRemoval::solveStep(Grid& grid,
                                     const bool greedy) {
        bool returnVal = false;

        for (std::uint_fast8_t index = 0; index < Order::orderSq * Order::orderSq; ++index) {
            Cell* cell = grid.getFlatData() + index;
            Cell* testCell;

            if (cell->isFound()) {
                for (const auto& direction : ALL_DIRECTIONS) {
                    for (const auto& group : ALL_GROUPS) {
                        testCell = cell->getDirectionInGroup(direction, group);

                        while (testCell != nullptr) {
                            if (testCell->containsPencilMark(cell->getValue())) {
                                testCell->removePencilMark(cell->getValue());

                                if (greedy) {
                                    returnVal = true;
                                } else {
                                    return true;
                                }
                            }

                            testCell = testCell->getDirectionInGroup(direction, group);
                        }
                    }
                }
            }
        }

        return returnVal;
    }
}
