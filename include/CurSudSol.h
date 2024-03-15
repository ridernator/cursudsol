#pragma once

#include "Drawer.h"
#include "Grid.h"
#include "Solver.h"

namespace cursudsol {
    class CurSudSol {
        public:
            CurSudSol();

            void draw();

            bool solveStep();

        private:
            Grid grid;
            Drawer drawer;
            Solver solver;
    };
}