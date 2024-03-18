#pragma once

#include "Drawer.h"
#include "Grid.h"
#include "Order.h"
#include "Solver.h"
#include <string>

namespace cursudsol {
    class CurSudSol {
        public:
            CurSudSol(const std::string& initialGrid);

            void draw();

            bool solveStep();

        private:
            Order order;
            Grid grid;
            Drawer drawer;
            Solver solver;
    };
}
