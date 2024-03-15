#include "Cell.h"
#include "Direction.h"
#include "Group.h"
#include "Order.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace cursudsol {
    Cell::Cell() : value(Order::orderSq) {
        for (std::size_t pencilMark = 0; pencilMark < Order::orderSq; ++pencilMark) {
            *(pencilMarks + pencilMark) = true;
        }

        for (const auto& direction : ALL_DIRECTIONS) {
            for (const auto& group : ALL_GROUPS) {
                *(neighbours + group + (direction * (std::size_t) Group::NUM_GROUPS)) = nullptr;
            }
        }
    }

    void Cell::setDirectionInGroup(const Direction direction,
                                   const Group group,
                                   Cell* cell) {
        *(neighbours + group + (direction * (std::size_t) Group::NUM_GROUPS)) = cell;
    }

    Cell* Cell::getDirectionInGroup(const Direction direction,
                                    const Group group) const {
        return *(neighbours + group + (direction * (std::size_t) Group::NUM_GROUPS));
    }

    Cell* Cell::getNextInGroup(const Group group) const {
        return getDirectionInGroup(Direction::NEXT, group);
    }

    Cell* Cell::getPreviousInGroup(const Group group) const {
        return getDirectionInGroup(Direction::PREVIOUS, group);
    }

    Cell* Cell::getDirectionInRow(const Direction direction) const {
        return getDirectionInGroup(direction, Group::ROW);
    }

    Cell* Cell::getDirectionInColumn(const Direction direction) const {
        return getDirectionInGroup(direction, Group::COLUMN);
    }

    Cell* Cell::getDirectionInBlock(const Direction direction) const {
        return getDirectionInGroup(direction, Group::BLOCK);
    }

    Cell* Cell::getNextInRow() const {
        return getDirectionInGroup(Direction::NEXT, Group::ROW);
    }

    Cell* Cell::getNextInColumn() const {
        return getDirectionInGroup(Direction::NEXT, Group::COLUMN);
    }

    Cell* Cell::getNextInBlock() const {
        return getDirectionInGroup(Direction::NEXT, Group::BLOCK);
    }

    Cell* Cell::getPreviousInRow() const {
        return getDirectionInGroup(Direction::PREVIOUS, Group::ROW);
    }

    Cell* Cell::getPreviousInColumn() const {
        return getDirectionInGroup(Direction::PREVIOUS, Group::COLUMN);
    }

    Cell* Cell::getPreviousInBlock() const {
        return getDirectionInGroup(Direction::PREVIOUS, Group::BLOCK);
    }

    void Cell::removePencilMark(const std::uint_fast8_t pencilMark) {
        *(pencilMarks + pencilMark) = false;
    }

    bool Cell::containsPencilMark(const std::uint_fast8_t pencilMark) {
        return *(pencilMarks + pencilMark);
    }

    bool Cell::isFound() {
        return (value < Order::orderSq);
    }

    std::uint_fast8_t Cell::countPencilMarks() {
        std::uint_fast8_t returnVal = 0;

        for (std::uint_fast8_t index = 0; index < Order::orderSq; ++index) {
            if (*(pencilMarks + index)) {
                ++returnVal;
            }
        }

        return returnVal;
    }

    bool Cell::solve() {
        std::uint_fast8_t returnVal = 0;
        std::uint_fast8_t valueToSet;

        for (std::uint_fast8_t index = 0; index < Order::orderSq; ++index) {
            if (*(pencilMarks + index)) {
                valueToSet = index;

                if (++returnVal > 1) {
                    return false;
                }
            }
        }

        if (returnVal == 1) {
            value = valueToSet;

            return true;
        }

        return false;
    }

    std::uint_fast8_t Cell::getValue() {
        return value;
    }
}
