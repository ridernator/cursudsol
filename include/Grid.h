#pragma once

#include "Cell.h"
#include "Order.h"
#include <cstddef>

namespace cursudsol {
    class Grid{
        public:
            Grid();

            Cell* getFlatData();

            Cell* getGroup(const Group group,
                           const std::size_t index);

            Cell** getGroups(const Group group);

            Cell* getRow(const std::size_t index);

            Cell** getRows();

            Cell* getColumn(const std::size_t index);

            Cell** getColumns();

            Cell* getBlock(const std::size_t index);

            Cell** getBlocks();

        private:
            Cell flatData[Order::orderSq * Order::orderSq];

            Cell* groups[Group::NUM_GROUPS][Order::orderSq];
    };
}
