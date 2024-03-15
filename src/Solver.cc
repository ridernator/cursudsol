#include "Solver.h"
#include "CandidateRemoval.h"
#include "NakedSingle.h"

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid) {
        rules.push_back(new NakedSingle());
        // rules.push_back(new CandidateRemoval());
    }

    Solver::~Solver() {
        for (const auto& rule : rules) {
            delete rule;
        }
    }

    bool Solver::solveStep() {
        for (const auto& rule : rules) {
            if (rule->solveStep(grid)) {
                return true;
            }
        }

        return false;
    }
}