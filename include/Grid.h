#pragma once

#include "Cell.h"
#include "Order.h"

#include <map>
#include <vector>
#include <string>

namespace cursudsol {
    class Grid{
        public:
            Grid(const Order& order,
                 const std::string& initialGrid);

            ~Grid();

            Cell** getFlatData();

            std::vector<Cell*>& getGroups(const Group group);

            const Order& getOrder() const;

        private:
            const Order& order;

            Cell** flatData;

            std::map<Group, std::vector<Cell*>> groups;
    };
}
