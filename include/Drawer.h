#pragma once

#include <ncurses.h>

#include "Grid.h"

namespace cursudsol {
    class Drawer {
        public:
            Drawer(Grid& grid);
            ~Drawer();

            void draw();

        private:
            static const int MAIN_GRID_COLOUR = 1;
            static const int SUB_GRID_COLOUR  = 2;
            static const int NUM_COLOUR       = 3;
            static const int FOUND_COLOUR     = 4;

            void initColours();

            void drawOuterGrid(WINDOW* window,
                               const int y,
                               const int x);

            void drawInnerGrid(WINDOW* window,
                               const int y,
                               const int x,
                               const int dataY,
                               const int dataX);

            void drawGrid(WINDOW* window,
                          const int y,
                          const int x);

            void drawGrid(const int y,
                          const int x);

            void drawBigNum(WINDOW* window,
                            const int y,
                            const int x,
                            const std::uint_fast8_t num);
            Grid& grid;
    };
}
