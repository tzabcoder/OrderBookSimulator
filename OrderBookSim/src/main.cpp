#include <iostream>

#include <Order.hpp>

int main() {

    // Order creation test
    for (int i = 0; i < 100; i++) {
        // Create the temporary order
        Order t_order = Order(
            "TMP",
            10,
            25.89,
            OrderSide::BUY,
            OrderType::LIMIT
        );

        // Log the order details
        std::cout << t_order.getOrderId() << " | " << t_order.getOrderSymbol() << " | " << t_order.getOrderTimestamp() << std::endl;
    }

    return 0;
}