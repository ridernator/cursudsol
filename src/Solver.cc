#include "Solver.h"
#include "CandidateRemoval.h"
#include "Order.h"
#include "Rule.h"
#include "NakedPair.h"
#include "NakedSingle.h"
#include "HiddenSingle.h"
#include "HiddenPair.h"
#include "NakedN.h"
#include <cstddef>

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid) {
        std::size_t i = 0;
        rules[i++] = new CandidateRemoval();
        rules[i++] = new NakedSingle();
        rules[i++] = new HiddenSingle();
        rules[i++] = new NakedN(2, "NakedPair");
        rules[i++] = new NakedN(3, "NakedTriple");
        rules[i++] = new NakedN(4, "NakedQuad");
        rules[i++] = new NakedN(5, "NakedQuint");
        rules[i++] = new NakedN(6, "NakedSex");
        rules[i++] = new NakedN(7, "NakedSept");
        rules[i++] = new NakedN(8, "NakedOct");
        rules[i++] = new HiddenPair();
    }

    Solver::~Solver() {
        for (const auto& rule : rules) {
            delete rule.second;
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
            if (rule.second->isEnabled()) {
                returnVal = rule.second->solveStep(grid, true);

                if (std::get<bool>(returnVal)) {
                    std::get<IntType>(returnVal) = rule.first;

                    grid.compact();

                    break;
                }
            }
        }

        return returnVal;
    }

    std::map<IntType, Rule*>& Solver::getRules() {
        return rules;
    }
}
