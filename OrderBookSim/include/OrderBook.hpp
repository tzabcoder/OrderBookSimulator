// Global Includes
#include <list>
#include <string>
#include <vector>

// Project Includes
#include <Order.hpp>
#include <Trade.hpp>

class OrderBook {
    public:
        OrderBook(
            std::string exchangeSymbol
        );

        // Create Order
        bool createOrder();

        // Modify Order
        bool modifyOrder();

        // Cancel Order
        bool cancelOrder();

    private:
        // Match Orders (event-driven)
        void matchOrders();

        std::string exchangeSymbol; // Symbol for the order book's traded security

        std::list<Order> buyOrders;  // List of all active buy orders
        std::list<Order> sellOrders; // List of all active sell orders

        std::vector<Order> orderHistory; // History of all orders in the order book
        std::vector<Trade> tradeHistory; // History of all trades in the order book (matched orders)
};