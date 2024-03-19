#pragma once

#include "Grid.h"
#include "Order.h"
#include "Rule.h"
#include "Solver.h"

#include <ncurses.h>

namespace cursudsol {
    class Drawer {
        public:
            Drawer(Grid& grid,
                   Solver& solver);
            ~Drawer();

            void draw();

        private:
            static const int MAIN_GRID_COLOUR = 1;
            static const int SUB_GRID_COLOUR  = 2;
            static const int NUM_COLOUR       = 3;
            static const int FOUND_COLOUR     = 4;
            static const int REMOVED_COLOUR   = 5;
            static const int BECAUSE_COLOUR   = 6;

            static const int NUM_SPACING = 3;

            void initColours();

            void drawOuterGrid(WINDOW* window,
                               const int y,
                               const int x);

            void drawInnerGrid(WINDOW* window,
                               const int y,
                               const int x,
                               const int dataY,
                               const int dataX,
                               SolverReturn& solverReturn);

            void drawGrid(WINDOW* window,
                          const int y,
                          const int x,
                          SolverReturn& solverReturn);

            void drawGrid(const int y,
                          const int x,
                          SolverReturn& solverReturn);

            void drawBigNum(WINDOW* window,
                            const int y,
                            const int x,
                            const IntType num);
            Grid& grid;
            Solver& solver;

            const Order& order;
    };
}
