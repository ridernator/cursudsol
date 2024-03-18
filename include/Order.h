#pragma once

#include <cstdint>

typedef std::uint64_t IntType;

namespace cursudsol {
    class Order {
        public:
            Order(const IntType order);

            const IntType order;

            const IntType order2;

            const IntType order4;
    };
}
