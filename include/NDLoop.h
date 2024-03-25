#pragma once

#include "Order.h"

#include <cstddef>
#include <set>
#include <vector>

namespace cursudsol {
    class NDLoop {
        public:
            NDLoop(const std::size_t n,
                   const std::set<IntType> pencilMarks);

            ~NDLoop() {}

            std::vector<IntType> next();

        private:
            std::vector<IntType> pencilMarks;
            std::vector<std::size_t> indices;
            std::vector<IntType> returnVal;

            const std::size_t n;
    };
}
