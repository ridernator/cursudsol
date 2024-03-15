#pragma once

#include "Direction.h"
#include "Group.h"
#include "Order.h"

#include <cstddef>
#include <cstdint>

namespace cursudsol {
    class Cell{
        public:
            Cell();

            void setDirectionInGroup(const Direction direction,
                                     const Group group,
                                     Cell* cell);

            Cell* getDirectionInGroup(const Direction direction,
                                      const Group group) const;

            Cell* getNextInGroup(const Group group) const;

            Cell* getPreviousInGroup(const Group group) const;

            Cell* getDirectionInRow(const Direction direction) const;

            Cell* getDirectionInColumn(const Direction direction) const;

            Cell* getDirectionInBlock(const Direction direction) const;

            Cell* getNextInRow() const;

            Cell* getNextInColumn() const;

            Cell* getNextInBlock() const;

            Cell* getPreviousInRow() const;

            Cell* getPreviousInColumn() const;

            Cell* getPreviousInBlock() const;

            void removePencilMark(const std::uint_fast8_t pencilMark);

            bool containsPencilMark(const std::uint_fast8_t pencilMark);

            bool isFound();

            std::uint_fast8_t countPencilMarks();

            bool solve();

            std::uint_fast8_t getValue();

        private:
            std::uint_fast8_t value;

            bool pencilMarks[Order::orderSq];

            Cell* neighbours[(std::size_t) Direction::NUM_DIRECTIONS * (std::size_t) Group::NUM_GROUPS];
    };
}
