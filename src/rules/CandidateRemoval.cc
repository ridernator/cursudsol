#include "CandidateRemoval.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"
#include <cstdint>

namespace cursudsol {
    bool CandidateRemoval::solveStep(Grid& grid) {
        for (std::uint_fast8_t index = 0; index < Order::orderSq; ++index) {
            Cell* cell = grid.getRow(index);
            Cell* testCell;

            while (cell != nullptr) {
                if (cell->isFound()) {
                    for (const auto& direction : ALL_DIRECTIONS) {
                        for (const auto& group : ALL_GROUPS) {
                            testCell = cell->getDirectionInGroup(direction, group);

                            while (testCell != nullptr) {
                                if (testCell->containsPencilMark(cell->getValue())) {
                                    testCell->removePencilMark(cell->getValue());

                                    return true;
                                }

                                testCell = cell->getDirectionInGroup(direction, group);
                            }
                        }
                    }
                }

                cell = cell->getNextInRow();
            }
        }

        return false;
    }
}
