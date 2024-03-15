#include "Cell.h"
#include "Direction.h"
#include "Group.h"
#include <cstddef>
#include <cstdint>

namespace cursudsol {
    Cell::Cell() : value(0) {
        for (std::size_t pencilMark = 0; pencilMark < Order::orderSq; ++pencilMark) {
            *(pencilMarks + pencilMark) = true;
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
}
