#include "Drawer.h"
#include "Order.h"
#include <cstdint>
#include <ncurses.h>

namespace cursudsol {
    Drawer::Drawer(Grid& grid,
                   Solver& solver) : grid(grid),
                                     solver(solver),
                                     order(grid.getOrder()) {
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
        while (true) {
            drawGrid(0, 0);

            refresh();

            if (getch() == 'q') {
                break;
            }

            solver.solveStep();
        }
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

    void Drawer::drawBigNum(WINDOW* window,
                            const int y,
                            const int x,
                            const IntType num) {
        for (std::uint_fast8_t index = 0; index < order.order; ++index) {
            mvwhline(window, y + index, x, ' ', order.order * NUM_SPACING);
        }

        switch (num) {
            case (0) : {
                mvwvline(window, y, x + 4, ACS_VLINE, 3);

                break;
            }

            case (1) : {
                mvwaddch(window, y,     x + 3, ACS_HLINE);
                mvwaddch(window, y,     x + 4, ACS_HLINE);
                mvwaddch(window, y,     x + 5, ACS_URCORNER);
                mvwaddch(window, y + 1, x + 3, ACS_ULCORNER);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_LRCORNER);
                mvwaddch(window, y + 2, x + 3, ACS_LLCORNER);
                mvwaddch(window, y + 2, x + 4, ACS_HLINE);
                mvwaddch(window, y + 2, x + 5, ACS_HLINE);

                break;
            }

            case (2) : {
                mvwaddch(window, y,     x + 3, ACS_HLINE);
                mvwaddch(window, y,     x + 4, ACS_HLINE);
                mvwaddch(window, y,     x + 5, ACS_URCORNER);
                mvwaddch(window, y + 1, x + 3, ACS_HLINE);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_RTEE);
                mvwaddch(window, y + 2, x + 3, ACS_HLINE);
                mvwaddch(window, y + 2, x + 4, ACS_HLINE);
                mvwaddch(window, y + 2, x + 5, ACS_LRCORNER);

                break;
            }

            case (3) : {
                mvwaddch(window, y,     x + 3, ACS_VLINE);
                mvwaddch(window, y,     x + 5, ACS_VLINE);
                mvwaddch(window, y + 1, x + 3, ACS_LLCORNER);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_RTEE);
                mvwaddch(window, y + 2, x + 5, ACS_VLINE);

                break;
            }

            case (4) : {
                mvwaddch(window, y,     x + 3, ACS_ULCORNER);
                mvwaddch(window, y,     x + 4, ACS_HLINE);
                mvwaddch(window, y,     x + 5, ACS_HLINE);
                mvwaddch(window, y + 1, x + 3, ACS_LLCORNER);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_URCORNER);
                mvwaddch(window, y + 2, x + 3, ACS_HLINE);
                mvwaddch(window, y + 2, x + 4, ACS_HLINE);
                mvwaddch(window, y + 2, x + 5, ACS_LRCORNER);

                break;
            }

            case (5) : {
                mvwaddch(window, y,     x + 3, ACS_VLINE);
                mvwaddch(window, y + 1, x + 3, ACS_LTEE);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_URCORNER);
                mvwaddch(window, y + 2, x + 3, ACS_LLCORNER);
                mvwaddch(window, y + 2, x + 4, ACS_HLINE);
                mvwaddch(window, y + 2, x + 5, ACS_LRCORNER);

                break;
            }

            case (6) : {
                mvwaddch(window, y,     x + 3, ACS_HLINE);
                mvwaddch(window, y,     x + 4, ACS_HLINE);
                mvwaddch(window, y,     x + 5, ACS_URCORNER);
                mvwaddch(window, y + 1, x + 5, ACS_VLINE);
                mvwaddch(window, y + 2, x + 5, ACS_VLINE);

                break;
            }

            case (7) : {
                mvwaddch(window, y,     x + 3, ACS_ULCORNER);
                mvwaddch(window, y,     x + 4, ACS_HLINE);
                mvwaddch(window, y,     x + 5, ACS_URCORNER);
                mvwaddch(window, y + 1, x + 3, ACS_LTEE);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_RTEE);
                mvwaddch(window, y + 2, x + 3, ACS_LLCORNER);
                mvwaddch(window, y + 2, x + 4, ACS_HLINE);
                mvwaddch(window, y + 2, x + 5, ACS_LRCORNER);

                break;
            }

            case (8) : {
                mvwaddch(window, y,     x + 3, ACS_ULCORNER);
                mvwaddch(window, y,     x + 4, ACS_HLINE);
                mvwaddch(window, y,     x + 5, ACS_URCORNER);
                mvwaddch(window, y + 1, x + 3, ACS_LLCORNER);
                mvwaddch(window, y + 1, x + 4, ACS_HLINE);
                mvwaddch(window, y + 1, x + 5, ACS_RTEE);
                mvwaddch(window, y + 2, x + 5, ACS_VLINE);

                break;
            }
        }
    }

    void Drawer::drawOuterGrid(WINDOW* window,
                               const int y,
                               const int x) {
        // Draw lines
        attron(COLOR_PAIR(MAIN_GRID_COLOUR));
        for (IntType i = 0; i <= order.order; ++i) {
            mvwhline(window, y + (i * order.order * (order.order + 1)), x, ACS_HLINE, order.order2 * ((order.order * NUM_SPACING) + 1));
            mvwvline(window, y, x + (i * order.order * ((order.order * NUM_SPACING) + 1)), ACS_VLINE, order.order2 * (order.order + 1));
        }

        // Draw corners
        mvwaddch(window, y, x, ACS_ULCORNER);
        mvwaddch(window, y, x + (order.order2 * ((order.order * NUM_SPACING) + 1)), ACS_URCORNER);
        mvwaddch(window, y + (order.order2 * (order.order + 1)), x, ACS_LLCORNER);
        mvwaddch(window, y + (order.order2 * (order.order + 1)), x + (order.order2 * ((order.order * NUM_SPACING) + 1)), ACS_LRCORNER);

        // Draw centres
        for (IntType row = 1; row < order.order; ++row) {
            for (IntType col = 1; col < order.order; ++col) {
                mvwaddch(window, y + (row * order.order * (order.order + 1)), x + (col * order.order * ((order.order * NUM_SPACING) + 1)), ACS_PLUS);

            }
        }

        // Draw edge tees
        for (IntType row = 1; row < order.order; ++row) {
            mvwaddch(window, y + (row * order.order * (order.order + 1)), x, ACS_LTEE);
            mvwaddch(window, y + (row * order.order * (order.order + 1)), x + (order.order2 * ((order.order * NUM_SPACING) + 1)), ACS_RTEE);
        }

        for (IntType col = 1; col < order.order; ++col) {
            mvwaddch(window, y, x + (col * order.order * ((order.order * NUM_SPACING) + 1)), ACS_TTEE);
            mvwaddch(window, y + (order.order2 * (order.order + 1)), x + (col * order.order * ((order.order * NUM_SPACING) + 1)), ACS_BTEE);
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
        for (IntType row = 1; row < order.order; ++row) {
            for (IntType col = 1; col < order.order; ++col) {
                mvwhline(window, y + (row * (order.order + 1)), x + 1, ACS_HLINE, (order.order * ((order.order * NUM_SPACING) + 1)) - 1);
                mvwvline(window, y + 1, x + (col * ((order.order * NUM_SPACING) + 1)), ACS_VLINE, (order.order * (order.order + 1)) - 1);
            }
        }

        // Draw centres
        for (IntType row = 1; row < order.order; ++row) {
            for (IntType col = 1; col < order.order; ++col) {
                mvwaddch(window, y + (row * (order.order + 1)), x + (col * ((order.order * NUM_SPACING) + 1)), ACS_PLUS);
            }
        }
        attroff(COLOR_PAIR(SUB_GRID_COLOUR));

        // Draw pencil marks
        attron(COLOR_PAIR(NUM_COLOUR));
        for (IntType row = 0; row < order.order; ++row) {
            for (IntType col = 0; col < order.order; ++col) {
                Cell* cell = grid.getFlatData()[dataX + col + ((dataY + row) * order.order2)];

                if (cell->isFound()) {
                    attron(COLOR_PAIR(FOUND_COLOUR));
                    drawBigNum(window, y + (row * (order.order + 1)) + 1, x + (col * ((order.order * NUM_SPACING) + 1)) + 1, cell->getValue());
                    attroff(COLOR_PAIR(FOUND_COLOUR));
                } else {
                    for (IntType num = 0; num < order.order2; ++num) {
                        if (cell->containsPencilMark(num)) {
                            mvwaddch(window,
                                    y + (row * (order.order + 1)) + (num / order.order) + 1,
                                    x + (col * ((order.order * NUM_SPACING) + 1)) + ((num % order.order) * NUM_SPACING) + 1 + 1,
                                    num + 48 + 1);
                        } else {
                            mvwaddch(window,
                                    y + (row * (order.order + 1)) + (num / order.order) + 1,
                                    x + (col * ((order.order * NUM_SPACING) + 1)) + ((num % order.order) * NUM_SPACING) + 1 + 1,
                                    ' ');
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

        for (IntType row = 0; row < order.order; ++row) {
            for (IntType col = 0; col < order.order; ++col) {
                drawInnerGrid(window,
                              y + (row * order.order * (order.order + 1)),
                              x + (col * order.order * ((order.order * NUM_SPACING) + 1)),
                              row * order.order,
                              col * order.order);
            }
        }
    }

    void Drawer::drawGrid(const int y,
                          const int x) {
        drawGrid(stdscr, y, x);
    }
}
