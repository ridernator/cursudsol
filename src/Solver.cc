#include "Solver.h"
#include "CandidateRemoval.h"
#include "Order.h"
#include "Rule.h"
#include "NakedPair.h"
#include "NakedSingle.h"
#include "HiddenSingle.h"
#include "HiddenPair.h"

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid) {
        rules[0] = {true, false, new CandidateRemoval()};
        rules[1] = {true, false, new NakedSingle()};
        rules[2] = {true, false, new HiddenSingle()};
        rules[3] = {true, false, new NakedPair()};
        rules[4] = {true, false, new HiddenPair()};
    }

    Solver::~Solver() {
        for (const auto& rule : rules) {
            delete std::get<Rule*>(rule.second);
        }
    }

    bool Solver::solve() {
        while (!grid.isSolved()) {
            if (!std::get<bool>(solveStep())) {
                return false;
            }
        }

        return true;
    }

    SolverReturn Solver::solveStep() {
        SolverReturn returnVal = {false, {}, {}, 100};

        for (const auto& rule : rules) {
            if (std::get<0>(rule.second)) {
                returnVal = std::get<Rule*>(rule.second)->solveStep(grid, std::get<1>(rule.second));

                if (std::get<bool>(returnVal)) {
                    std::get<IntType>(returnVal) = rule.first;

                    grid.compact();

                    break;
                }
            }
        }

        return returnVal;
    }
}
