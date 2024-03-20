#include "Cell.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"

#include <algorithm>

namespace cursudsol {
    Cell::Cell(const Order& order) : order(order),
                                     value(order.order2) {
        for (IntType index = 0; index < order.order2; ++index) {
            pencilMarks[index] = true;
        }

        for (const Direction direction : ALL_DIRECTIONS) {
            for (const Group group : ALL_GROUPS) {
                neighbours[direction][group] = nullptr;
            }
        }
    }

    void Cell::setValue(const IntType value) {
        this->value = value;
    }

    void Cell::setNeighbour(const Direction direction,
                            const Group group,
                            Cell* cell) {
        neighbours[direction][group] = cell;
    }

    Cell* Cell::getNeighbour(const Direction direction,
                             const Group group) {
        return neighbours[direction][group];
    }

    void Cell::removePencilMark(const IntType pencilMark) {
        pencilMarks[pencilMark] = false;
    }

    bool Cell::containsPencilMark(const IntType pencilMark) {
        return pencilMarks[pencilMark];
    }

    bool Cell::isFound() const {
        return (value < order.order2);
    }

    IntType Cell::countPencilMarks() const {
        return std::count_if(pencilMarks.begin(), pencilMarks.end(), [] (const std::pair<IntType, bool>& value) {
            return value.second;
        });
    }

    bool Cell::solve() {
        if (countPencilMarks() == 1) {
            setValue(std::find_if(pencilMarks.begin(), pencilMarks.end(), [] (const std::pair<IntType, bool>& value) {
                return value.second;
            })->first);

            return true;
        }

        return false;
    }

    IntType Cell::getValue() const {
        return value;
    }

    void Cell::initSeenCells() {
        for (const Direction direction : ALL_DIRECTIONS) {
            for (const Group group : ALL_GROUPS) {
                for (Cell* cell = getNeighbour(direction, group); cell != nullptr; cell = cell->getNeighbour(direction, group)) {
                    seenCells.insert(cell);
                }
            }
        }
    }

    std::set<Cell*>& Cell::getSeenCells() {
        return seenCells;
    }
}
