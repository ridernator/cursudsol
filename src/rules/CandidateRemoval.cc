#include "CandidateRemoval.h"
#include "Group.h"
#include "Rule.h"

namespace cursudsol {
    SolverReturn CandidateRemoval::solveStep(Grid& grid,
                                             const bool greedy) {
        SolverReturn returnVal(false, {}, {});

        for (Cell* cell : grid.getGroups(Group::ROW)) {
            for (Cell* runner = cell; runner != nullptr; runner = runner->getNeighbour(Direction::NEXT, Group::ROW)) {
                if (runner->isFound()) {
                    for (const auto& testCell : runner->getSeenCells()) {
                        if ((!testCell->isFound()) &&
                            (testCell->containsPencilMark(runner->getValue()))) {
                            testCell->removePencilMark(runner->getValue());

                            std::get<bool>(returnVal) = true;
                            std::get<1>(returnVal)[testCell].insert(runner->getValue());
                            std::get<2>(returnVal)[runner];
                        }
                    }

                    if ((std::get<bool>(returnVal)) &&
                        (!greedy)) {
                        return returnVal;
                    }
                }
            }
        }

        return returnVal;
    }
}
