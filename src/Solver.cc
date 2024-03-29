#include "Solver.h"
#include "Order.h"
#include "Rule.h"
#include "NakedSingle.h"
#include "HiddenSingle.h"
#include "NakedN.h"
#include "HiddenN.h"
#include "IntersectionRemoval.h"
#include "XWing.h"

#include <cstddef>
#include <dlfcn.h>
#include <iostream>

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid),
                                 ruleIndex(0) {
        loadPlugins();

        rules[ruleIndex++] = new NakedSingle();
        rules[ruleIndex++] = new HiddenSingle();
        rules[ruleIndex++] = new NakedN(2, "NakedPair");
        rules[ruleIndex++] = new HiddenN(2, "HiddenPair");
        rules[ruleIndex++] = new NakedN(3, "NakedTriple");
        rules[ruleIndex++] = new HiddenN(3, "HiddenTriple");
        rules[ruleIndex++] = new NakedN(4, "NakedQuad");
        rules[ruleIndex++] = new HiddenN(4, "HiddenQuad");
        rules[ruleIndex++] = new IntersectionRemoval();
        rules[ruleIndex++] = new XWing();
        // rules[ruleIndex++] = new NakedN(5, "NakedQuint");
        // rules[ruleIndex++] = new HiddenN(5, "HiddenQuint");
        // rules[ruleIndex++] = new NakedN(6, "NakedSex");
        // rules[ruleIndex++] = new HiddenN(6, "HiddenSex");
        // rules[ruleIndex++] = new NakedN(7, "NakedSept");
        // rules[ruleIndex++] = new HiddenN(7, "HiddenSept");
        // rules[ruleIndex++] = new NakedN(8, "NakedOct");
        // rules[ruleIndex++] = new HiddenN(8, "HiddenOct");

        loadPlugins();
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

    std::set<Rule*> Solver::loadPlugin(const std::string& pluginPath) {
        char* errorString;

        void* handle = dlopen(pluginPath.c_str(), RTLD_NOW);

        if ((errorString = dlerror()) != nullptr) {
            std::cerr << "Error opening plugin \"" << pluginPath << "\" : " << errorString << std::endl;

            return {};
        }

        std::set<Rule*> (*createRules)();
        createRules = (std::set<Rule*>(*)()) dlsym(handle, "createRules");

        if ((errorString = dlerror()) != nullptr) {
            std::cerr << "Error finding \"createRule\" function from \"" << pluginPath << "\" : " << errorString << std::endl;

            dlclose(handle);

            return {};
        }

        return createRules();
    }

    void Solver::loadPlugins() {
        for (Rule* rule : loadPlugin("plugins/CandidateRemoval/libCandidateRemoval.so")) {
            rules[ruleIndex++] = rule;
        }
    }
}
