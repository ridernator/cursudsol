#include "Solver.h"
#include "Rule.h"

#include <dlfcn.h>
#include <filesystem>
#include <iostream>

namespace cursudsol {
    Solver::Solver(Grid& grid) : grid(grid),
                                 ruleIndex(0) {
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
            std::cerr << "Error finding \"createRules\" function from \"" << pluginPath << "\" : " << errorString << std::endl;

            dlclose(handle);

            return {};
        }

        return createRules();
    }

    void Solver::loadPlugins() {
        for (const auto& entry : std::filesystem::directory_iterator(PLUGIN_DIRECTORY)) {
            if (!entry.is_directory()) {
                for (Rule* rule : loadPlugin(entry.path())) {
                    rules[ruleIndex++] = rule;
                }
            }
        }
    }
}
