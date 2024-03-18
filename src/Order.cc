#include "Order.h"

namespace cursudsol {
    Order::Order(const IntType order) : order(order),
                                        order2(order * order),
                                        order4(order2 * order2) {

    }
}
