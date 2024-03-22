#include "Grid.h"
#include "Cell.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"

namespace cursudsol {
    Grid::Grid(const Order& order,
               const std::string& initialGrid) : order(order) {
        flatData = new Cell*[order.order4];

        for (IntType index = 0; index < order.order4; ++index) {
            flatData[index] = new Cell(order);
            if ((initialGrid[index] > '0') && ((IntType) initialGrid[index] - 48 <= order.order2)) {
                flatData[index]->setValue((initialGrid[index] - 48) - 1);
            }
        }

        // Create start of rows, columns and blocks
        for (IntType index = 0; index < order.order2; ++index) {
            groups[Group::ROW].push_back(flatData[index * order.order2]);
            groups[Group::COLUMN].push_back(flatData[index]);

            int blockStartRow = order.order * (index / order.order);
            int blockStartCol = order.order * (index % order.order);
            groups[Group::BLOCK].push_back(flatData[blockStartCol + (blockStartRow * order.order2)]);
        }

        // Link cells
        for (IntType index = 0; index < order.order4; ++index) {
            // Rows
            if (index % order.order2 != order.order2 - 1) {
                flatData[index]->setNeighbour(Direction::NEXT, Group::ROW, flatData[index + 1]);
            }

            if (index % order.order2 != 0) {
                flatData[index]->setNeighbour(Direction::PREVIOUS, Group::ROW, flatData[index - 1]);
            }

            // Columns
            if (index < order.order2 * (order.order2 - 1)) {
                flatData[index]->setNeighbour(Direction::NEXT, Group::COLUMN, flatData[index + order.order2]);
            }

            if (index >= order.order2) {
                flatData[index]->setNeighbour(Direction::PREVIOUS, Group::COLUMN, flatData[index - order.order2]);
            }

            // Blocks
            if (index % order.order == order.order - 1) {
                if ((index / order.order2) % order.order != order.order - 1) {
                    flatData[index]->setNeighbour(Direction::NEXT, Group::BLOCK, flatData[index + order.order2 - (order.order - 1)]);
                }
            } else {
                flatData[index]->setNeighbour(Direction::NEXT, Group::BLOCK, flatData[index]->getNeighbour(Direction::NEXT, Group::ROW));
            }

            if (index % order.order == 0) {
                if ((index / order.order2) % order.order != 0) {
                    flatData[index]->setNeighbour(Direction::PREVIOUS, Group::BLOCK, flatData[index - order.order2 + (order.order - 1)]);
                }
            } else {
                flatData[index]->setNeighbour(Direction::PREVIOUS, Group::BLOCK, flatData[index]->getNeighbour(Direction::PREVIOUS, Group::ROW));
            }
        }

        // Calculate seen cells
        for (IntType index = 0; index < order.order4; ++index) {
            flatData[index]->initSeenCells();
        }
    }

    Grid::~Grid() {
        for (IntType index = 0; index < order.order4; ++index) {
            delete flatData[index];
        }

        delete [] flatData;
    }

    Cell** Grid::getFlatData() {
        return flatData;
    }

    std::vector<Cell*>& Grid::getGroups(const Group group) {
        return groups[group];
    }

    const Order& Grid::getOrder() const {
        return order;
    }

    void Grid::compact() {
        for (IntType index = 0; index < order.order4; ++index) {
            if (!flatData[index]->isFound()) {
                std::erase_if(flatData[index]->getSeenCells(), [] (const Cell* cell) {
                    return cell->isFound();
                });
            }
        }

        // Cell* runner;
        // Cell* previous;
        //
        // for (Group group : ALL_GROUPS) {
        //     for (Cell* start : getGroups(group)) {
        //         while ((start != nullptr) &&
        //                (start->isFound())) {
        //             start = start->getNeighbour(Direction::NEXT, group);
        //         }
        //
        //         runner = start;
        //
        //         while (runner != nullptr) {
        //             if (runner->isFound()) {
        //                 previous->setNeighbour(Direction::NEXT, group, runner->getNeighbour(Direction::NEXT, group));
        //
        //                 if (runner->getNeighbour(Direction::NEXT, group) != nullptr) {
        //                     runner->getNeighbour(Direction::NEXT, group)->setNeighbour(Direction::PREVIOUS, group, previous);
        //                 }
        //             } else {
        //                 previous = runner;
        //             }
        //
        //             runner = runner->getNeighbour(Direction::NEXT, group);
        //         }
        //     }
        // }
    }
}
