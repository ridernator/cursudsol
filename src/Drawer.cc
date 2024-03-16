#include "Drawer.h"
#include "Order.h"
#include <ncurses.h>

namespace cursudsol {
    Drawer::Drawer(Grid& grid) : grid(grid) {
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);

        initColours();

    }

    Drawer::~Drawer() {
        endwin();
    }

    void Drawer::draw() {
        clear();

        drawGrid(0, 0);
    }

    void Drawer::initColours() {
        if (has_colors()) {
            start_color();

            init_pair(MAIN_GRID_COLOUR, COLOR_GREEN, COLOR_BLACK);
            init_pair(SUB_GRID_COLOUR,  COLOR_BLUE,  COLOR_BLACK);
            init_pair(NUM_COLOUR,       COLOR_WHITE, COLOR_BLACK);
            init_pair(FOUND_COLOUR,     COLOR_BLACK, COLOR_GREEN);
        }
    }

    void Drawer::drawOuterGrid(WINDOW* window,
                               const int y,
                               const int x) {
        // Draw lines
        attron(COLOR_PAIR(MAIN_GRID_COLOUR));
        for (int i = 0; i <= Order::order; ++i) {
            mvwhline(window, y + (i * Order::order * (Order::order + 1)), x, ACS_HLINE, Order::orderSq * (Order::order + 1));
            mvwvline(window, y, x + (i * Order::order * (Order::order + 1)), ACS_VLINE, Order::orderSq * (Order::order + 1));
        }

        // Draw corners
        mvwaddch(window, y, x, ACS_ULCORNER);
        mvwaddch(window, y, x + (Order::orderSq * (Order::order + 1)), ACS_URCORNER);
        mvwaddch(window, y + (Order::orderSq * (Order::order + 1)), x, ACS_LLCORNER);
        mvwaddch(window, y + (Order::orderSq * (Order::order + 1)), x + (Order::orderSq * (Order::order + 1)), ACS_LRCORNER);

        // Draw centres
        for (int row = 1; row < Order::order; ++row) {
            for (int col = 1; col < Order::order; ++col) {
                mvwaddch(window, y + (row * Order::order * (Order::order + 1)), x + (col * Order::order * (Order::order + 1)), ACS_PLUS);

            }
        }

        // Draw edge tees
        for (int row = 1; row < Order::order; ++row) {
            mvwaddch(window, y + (row * Order::order * (Order::order + 1)), x, ACS_LTEE);
            mvwaddch(window, y + (row * Order::order * (Order::order + 1)), x + (Order::orderSq * (Order::order + 1)), ACS_RTEE);
        }

        for (int col = 1; col < Order::order; ++col) {
            mvwaddch(window, y, x + (col * Order::order * (Order::order + 1)), ACS_TTEE);
            mvwaddch(window, y + (Order::orderSq * (Order::order + 1)), x + (col * Order::order * (Order::order + 1)), ACS_BTEE);
        }
        attroff(COLOR_PAIR(MAIN_GRID_COLOUR));
    }

    void Drawer::drawInnerGrid(WINDOW* window,
                               const int y,
                               const int x,
                               const int dataY,
                               const int dataX) {
        // Draw lines
        attron(COLOR_PAIR(SUB_GRID_COLOUR));
        for (int row = 1; row < Order::order; ++row) {
            for (int col = 1; col < Order::order; ++col) {
                mvwhline(window, y + (row * (Order::order + 1)), x + 1, ACS_HLINE, (Order::order * (Order::order + 1)) - 1);
                mvwvline(window, y + 1, x + (col * (Order::order + 1)), ACS_VLINE, (Order::order * (Order::order + 1)) - 1);
            }
        }

        // Draw centres
        for (int row = 1; row < Order::order; ++row) {
            for (int col = 1; col < Order::order; ++col) {
                mvwaddch(window, y + (row * (Order::order + 1)), x + (col * (Order::order + 1)), ACS_PLUS);
            }
        }
        attroff(COLOR_PAIR(SUB_GRID_COLOUR));

        // Draw pencil marks
        attron(COLOR_PAIR(NUM_COLOUR));
        // for (int row = 0; row < 1; ++row) {
        //     for (int col = 0; col < 1; ++col) {
        for (int row = 0; row < Order::order; ++row) {
            for (int col = 0; col < Order::order; ++col) {
                Cell* cell = grid.getFlatData() + dataX + col + ((dataY + row) * Order::orderSq);

                if (cell->isFound()) {
                    attron(COLOR_PAIR(FOUND_COLOUR));
                    mvwaddch(window,
                             y + (row * (Order::order + 1)) + ((Order::orderSq / 2) / Order::order) + 1,
                             x + (col * (Order::order + 1)) + ((Order::orderSq / 2) % Order::order) + 1,
                             cell->getValue() + 48 + 1);
                    attroff(COLOR_PAIR(FOUND_COLOUR));
                } else {
                    for (int num = 0; num < Order::orderSq; ++num) {
                        if (cell->containsPencilMark(num)) {
                            mvwaddch(window,
                                    y + (row * (Order::order + 1)) + (num / Order::order) + 1,
                                    x + (col * (Order::order + 1)) + (num % Order::order) + 1,
                                    num + 48 + 1);
                        }
                    }
                }
            }
        }
        attroff(COLOR_PAIR(NUM_COLOUR));
    }

    void Drawer::drawGrid(WINDOW* window,
                          const int y,
                          const int x) {
        drawOuterGrid(window, y, x);

        for (int row = 0; row < Order::order; ++row) {
            for (int col = 0; col < Order::order; ++col) {
                drawInnerGrid(window,
                              y + (row * Order::order * (Order::order + 1)),
                              x + (col * Order::order * (Order::order + 1)),
                              row * Order::order,
                              col * Order::order);
            }
        }
    }

    void Drawer::drawGrid(const int y,
                          const int x) {
        drawGrid(stdscr, y, x);
    }

}
