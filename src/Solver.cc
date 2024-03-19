#include "Solver.h"
#include "CandidateRemoval.h"
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
        for (const auto& rule : rules) {
            delete rule;
        }
    }

    bool Solver::solveStep() {
        for (const auto& rule : rules) {
            if (rule->solveStep(grid, false)) {
                return true;
            }
        }

        return false;
    }
}
