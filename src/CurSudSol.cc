#include "CurSudSol.h"

#include <ncurses.h>

namespace cursudsol {
    CurSudSol::CurSudSol() : drawer(grid),
                             solver(grid) {
    }

    void CurSudSol::draw() {
        drawer.draw();
    }

    bool CurSudSol::solveStep() {
        return solver.solveStep();
    }
}

int main() {
    cursudsol::CurSudSol sudsol;

    while (true) {
        sudsol.draw();

        if (getch() == 'q') {
            break;
        }

        sudsol.solveStep();
    }
}
