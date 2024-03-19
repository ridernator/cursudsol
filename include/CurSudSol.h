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

        private:
            Order order;
            Grid grid;
            Solver solver;
            Drawer drawer;
    };
}
