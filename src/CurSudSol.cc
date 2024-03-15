#include "CurSudSol.h"

#include <ncurses.h>
#include <unistd.h>

namespace cursudsol {
    CurSudSol::CurSudSol() : drawer(grid) {
    }

    void CurSudSol::draw() {
        drawer.draw();
    }
}

int main() {
    cursudsol::CurSudSol sudsol;

    while (true) {
        sudsol.draw();

        if (getch() == 'q') {
            break;
        }
    }
}
