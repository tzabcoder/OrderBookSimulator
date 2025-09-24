#include <iostream>

#include <Order.hpp>
#include <Trade.hpp>

int main() {
    // Order creation test
    for (int i = 0; i < 100; i++) {
        int qty = 10;
        double price = 25.89;
        std::string symbol = "TMP";

        // Create a market buy order
        Order t_buyOrder = Order(
            symbol,
            qty,
            price, // Un-used field for market orders
            OrderSide::BUY,
            OrderType::MARKET
        );

        // Create a limit sell order
        Order t_sellOrder = Order(
            symbol,
            qty,
            price,
            OrderSide::SELL,
            OrderType::LIMIT
        );

        // Create the trade object
        Trade t_trade = Trade (
            symbol,
            t_buyOrder.getOrderId(),
            t_sellOrder.getOrderId(),
            qty,
            price
        );

        // Log the trade information
        std::cout << t_trade.getTradeId() << " | " << t_trade.getBuyOrderId() << " | " << t_trade.getSellOrderId() << std::endl;
    }

    return 0;
}