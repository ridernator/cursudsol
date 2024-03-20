#include "CandidateRemoval.h"
#include "Group.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn CandidateRemoval::solveStep(Grid& grid,
                                             const bool greedy) {
        SolverReturn returnVal(false, {}, {});
        Cell* runner;

        for (const auto& cell : grid.getGroups(Group::ROW)) {
            runner = cell;

            while (runner != nullptr) {
                if (runner->isFound()) {
                    for (const auto& testCell : runner->getSeenCells()) {
                        if ((!testCell->isFound()) &&
                            (testCell->containsPencilMark(runner->getValue()))) {
                            testCell->removePencilMark(runner->getValue());

                            std::get<0>(returnVal) = true;
                            std::get<1>(returnVal)[testCell].insert(runner->getValue());
                            std::get<2>(returnVal)[runner];

                            if (!greedy) {
                                return returnVal;
                            }
                        }
                    }
                }

                runner = runner->getNeighbour(Direction::NEXT, Group::ROW);
            }
        }

        return returnVal;
    }
}
