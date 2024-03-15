#include <ncurses.h>

#define MAIN_GRID_COLOUR 1
#define SUB_GRID_COLOUR  2
#define NUM_COLOUR       3

void initColours() {
    if (has_colors()) {
        start_color();

        init_pair(MAIN_GRID_COLOUR, COLOR_GREEN, COLOR_BLACK);
        init_pair(SUB_GRID_COLOUR,  COLOR_BLUE,  COLOR_BLACK);
        init_pair(NUM_COLOUR,       COLOR_WHITE, COLOR_BLACK);
    }
}

void drawOuterGrid(WINDOW* window,
                   const int y,
                   const int x,
                   const int order) {
    int orderSq = order * order;

    // Draw lines
    attron(COLOR_PAIR(MAIN_GRID_COLOUR));
    for (int i = 0; i <= order; ++i) {
        mvwhline(window, y + (i * order * (order + 1)), x, ACS_HLINE, orderSq * (order + 1));
        mvwvline(window, y, x + (i * order * (order + 1)), ACS_VLINE, orderSq * (order + 1));
    }

    // Draw corners
    mvwaddch(window, y, x, ACS_ULCORNER);
    mvwaddch(window, y, x + (orderSq * (order + 1)), ACS_URCORNER);
    mvwaddch(window, y + (orderSq * (order + 1)), x, ACS_LLCORNER);
    mvwaddch(window, y + (orderSq * (order + 1)), x + (orderSq * (order + 1)), ACS_LRCORNER);

    // Draw centres
    for (int row = 1; row < order; ++row) {
        for (int col = 1; col < order; ++col) {
            mvwaddch(window, y + (row * order * (order + 1)), x + (col * order * (order + 1)), ACS_PLUS);

        }
    }

    // Draw edge tees
    for (int row = 1; row < order; ++row) {
        mvwaddch(window, y + (row * order * (order + 1)), x, ACS_LTEE);
        mvwaddch(window, y + (row * order * (order + 1)), x + (orderSq * (order + 1)), ACS_RTEE);
    }

    for (int col = 1; col < order; ++col) {
        mvwaddch(window, y, x + (col * order * (order + 1)), ACS_TTEE);
        mvwaddch(window, y + (orderSq * (order + 1)), x + (col * order * (order + 1)), ACS_BTEE);
    }
    attroff(COLOR_PAIR(MAIN_GRID_COLOUR));
}

void drawInnerGrid(WINDOW* window,
                   const int y,
                   const int x,
                   const int order) {
    // Draw lines
    attron(COLOR_PAIR(SUB_GRID_COLOUR));
    for (int row = 1; row < order; ++row) {
        for (int col = 1; col < order; ++col) {
            mvwhline(window, y + (row * (order + 1)), x + 1, ACS_HLINE, (order * (order + 1)) - 1);
            mvwvline(window, y + 1, x + (col * (order + 1)), ACS_VLINE, (order * (order + 1)) - 1);
        }
    }

    // Draw centres
    for (int row = 1; row < order; ++row) {
        for (int col = 1; col < order; ++col) {
            mvwaddch(window, y + (row * (order + 1)), x + (col * (order + 1)), ACS_PLUS);
        }
    }
    attroff(COLOR_PAIR(SUB_GRID_COLOUR));

    // Draw pencil marks
    attron(COLOR_PAIR(NUM_COLOUR));
    for (int row = 0; row < order; ++row) {
        for (int col = 0; col < order; ++col) {
            int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

            for (int num = 0; num < 9; ++num) {
                mvwaddch(window,
                         y + (row * (order + 1)) + (num / order) + 1,
                         x + (col * (order + 1)) + (num % order) + 1,
                         *(nums + num) + 48);
            }
        }
    }
    attroff(COLOR_PAIR(NUM_COLOUR));
}

void drawGrid(WINDOW* window,
              const int y,
              const int x,
              const int order = 3) {
    drawOuterGrid(window, y, x, order);

    for (int row = 0; row < order; ++row) {
        for (int col = 0; col < order; ++col) {
            drawInnerGrid(window, y + (row * order * (order + 1)), x + (col * order * (order + 1)), order);
        }
    }
}

void drawGrid(const int y,
              const int x,
              const int order = 3) {
    drawGrid(stdscr, y, x, order);
}

int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    initColours();

    while (true) {
        clear();

        drawGrid(5, 5);

        refresh();

        if (getch() == 'q') {
            break;
        }
    }

    endwin();
}
