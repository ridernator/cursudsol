#pragma once

#include <cstddef>
#include <map>

#include "Grid.h"
#include "Order.h"
#include "Rule.h"

namespace cursudsol {
    class Solver {
        public:
            Solver(Grid& grid);
            ~Solver();

            SolverReturn solveStep();

            bool solve();

            std::map<IntType, Rule*>& getRules();

        private:
            bool loadRulesFromPlugin(const std::string& pluginPath);

            void loadPluginRules();

            static const inline std::string PLUGIN_DIRECTORY = "plugins";

            Grid& grid;

            std::map<IntType, Rule*> rules;

            std::size_t ruleIndex;
    };
}
