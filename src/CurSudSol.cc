#include "CurSudSol.h"

#include <ncurses.h>

namespace cursudsol {
    CurSudSol::CurSudSol(const char* initialGrid) : grid(initialGrid),
                                                    drawer(grid),
                                                    solver(grid) {
    }

    void CurSudSol::draw() {
        drawer.draw();
    }

    bool CurSudSol::solveStep() {
        return solver.solveStep();
    }
}

int main(const int,
         const char** argv) {
    cursudsol::CurSudSol sudsol(*(argv + 1));

    while (true) {
        sudsol.draw();

        if (getch() == 'q') {
            break;
        }

        sudsol.solveStep();
    }
}
