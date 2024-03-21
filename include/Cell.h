#pragma once

#include "Direction.h"
#include "Group.h"
#include "Order.h"

#include <map>
#include <set>

namespace cursudsol {
    class Cell{
        public:
            Cell(const Order& order);

            void setValue(const IntType value);

            void setNeighbour(const Direction direction,
                              const Group group,
                              Cell* cell);

            Cell* getNeighbour(const Direction direction,
                               const Group group);

            void removePencilMark(const IntType pencilMark);

            bool containsPencilMark(const IntType pencilMark);

            bool isFound() const;

            IntType countPencilMarks() const;

            bool solve();

            IntType getValue() const;

            void initSeenCells();

            std::set<Cell*>& getSeenCells();

            std::set<IntType>& getPencilMarks();

        private:
            const Order& order;

            IntType value;

            std::set<IntType> pencilMarks;

            std::map<Direction, std::map<Group, Cell*>> neighbours;

            std::set<Cell*> seenCells;
    };
}
