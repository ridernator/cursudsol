#pragma once

#include "Drawer.h"
#include "Grid.h"

namespace cursudsol {
    class CurSudSol {
        public:
            CurSudSol();

            void draw();

        private:
            Grid grid;
            Drawer drawer;
    };
}
