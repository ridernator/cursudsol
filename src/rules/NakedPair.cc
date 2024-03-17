#include "NakedPair.h"
#include "Group.h"
#include "Order.h"
#include <cstddef>
#include <set>

namespace cursudsol {
    bool NakedPair::solveStep(Grid& grid,
                              const bool greedy) {
        bool returnVal = false;

        for (const auto group : ALL_GROUPS) {
            for (std::size_t index = 0; index < Order::orderSq; ++index) {
                Cell* cell1 = grid.getGroup(group, index);

                while (cell1 != nullptr) {
                    bool success = false;

                    if ((!cell1->isFound()) && (cell1->countPencilMarks() == 2)) {
                        Cell* cell2 = cell1->getNextInGroup(group);

                        while (cell2 != nullptr) {
                            if ((!cell2->isFound()) &&
                                (cell2->countPencilMarks() == 2) &&
                                (cell2->getPencilMarks() == cell1->getPencilMarks())) {
                                // Found matching pair. Now check there aren't any others
                                Cell* badCell = cell2->getNextInGroup(group);
                                bool thirdMatch = false;

                                while (badCell != nullptr) {
                                    if ((!badCell->isFound()) &&
                                        (badCell->countPencilMarks() == 2) &&
                                        (badCell->getPencilMarks() == cell1->getPencilMarks())) {
                                        // Give up. Found 3rd candidate
                                        thirdMatch = true;

                                        break;
                                    }

                                    badCell = badCell->getNextInGroup(group);
                                }

                                if (!thirdMatch) {
                                    // Get rid
                                    for (std::uint_fast8_t remove = 0; remove < Order::orderSq; ++remove) {
                                        if (cell1->containsPencilMark(remove)) {
                                            Cell* remover = grid.getGroup(group, index);

                                            while (remover != nullptr) {
                                                if ((remover != cell1) &&
                                                    (remover != cell2) &&
                                                    (remover->containsPencilMark(remove))) {
                                                    remover->removePencilMark(remove);

                                                    success = true;
                                                    returnVal = true;
                                                }

                                                remover = remover->getNextInGroup(group);
                                            }
                                        }
                                    }
                                }

                                break;
                            }

                            cell2 = cell2->getNextInGroup(group);
                        }
                    }

                    if ((returnVal) && (!greedy)) {
                        return true;
                    }

                    if (success) {
                        break;
                    }

                    cell1 = cell1->getNextInGroup(group);
                }
            }
        }

        return returnVal;
    }
}
