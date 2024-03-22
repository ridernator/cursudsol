#include "Solver.h"
#include "CandidateRemoval.h"
#include "Rule.h"
#include "NakedPair.h"
#include "NakedSingle.h"
#include "HiddenSingle.h"
#include "HiddenPair.h"

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid) {
        rules[0] = new CandidateRemoval();
        rules[1] = new NakedSingle();
        rules[2] = new HiddenSingle();
        rules[3] = new NakedPair();
        rules[4] = new HiddenPair();
    }

    Solver::~Solver() {
        for (const auto& rule : rules) {
            delete rule.second;
        }
    }

    SolverReturn Solver::solveStep() {
        SolverReturn returnVal;

        for (const auto& rule : rules) {
            returnVal = rule.second->solveStep(grid, false);

            if (std::get<bool>(returnVal)) {
                grid.compact();

                break;
            }
        }

        return returnVal;
    }
}
