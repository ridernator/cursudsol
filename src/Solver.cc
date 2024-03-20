#include "Solver.h"
#include "CandidateRemoval.h"
#include "Rule.h"
#include "NakedPair.h"
#include "NakedSingle.h"
#include "HiddenSingle.h"

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid) {
        rules.push_back(new CandidateRemoval());
        rules.push_back(new NakedSingle());
        rules.push_back(new HiddenSingle());
        rules.push_back(new NakedPair());
    }

    Solver::~Solver() {
        for (const Rule* rule : rules) {
            delete rule;
        }
    }

    SolverReturn Solver::solveStep() {
        SolverReturn returnVal;

        for (Rule* rule : rules) {
            returnVal = rule->solveStep(grid, true);

            if (std::get<0>(returnVal)) {
                grid.compact();

                break;
            }
        }

        return returnVal;
    }
}
