#pragma once

#include "Cell.h"
#include "Order.h"

namespace cursudsol {
    class Grid{
        public:
            Grid();

            Cell* getFlatData();

        private:
            Cell flatData[Order::orderSq * Order::orderSq];
    };
}
