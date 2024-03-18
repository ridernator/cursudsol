#include "CurSudSol.h"

#include <ncurses.h>
#include <string>

namespace cursudsol {
    CurSudSol::CurSudSol(const std::string& initialGrid) : order(3),
                                                           grid(order, initialGrid),
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
