#include "CurSudSol.h"

#include <ncurses.h>
#include <string>

namespace cursudsol {
    CurSudSol::CurSudSol(const std::string& initialGrid) : order(3),
                                                           grid(order, initialGrid),
                                                           solver(grid),
                                                           drawer(grid, solver) {
        drawer.init();
    }
}

int main(const int,
         const char** argv) {
    cursudsol::CurSudSol sudsol(*(argv + 1));
}
