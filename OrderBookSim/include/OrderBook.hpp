// Global Includes
#include <list>
#include <string>
#include <vector>

// Project Includes
#include <Order.hpp>
#include <Trade.hpp>

class OrderBook {
    public:
        /**
         * @brief Constructor for a new order book object.
         *
         * @param exchangeSymbol - symbol for this order book
         */
        OrderBook(
            std::string exchangeSymbol
        );

        /**
         * @brief Create a new order for this order book. The new order
         * is added to the correct order book side. The order is then logged
         * in the order history.
         * Once the order is added to the order book, the match orders event
         * is processed.
         *
         * @param qty - quantity of the new order
         * @param price - price for order to execute; @see OrderType
         * @param side - side of the order; @see OrderSide
         * @param type - type of the order; @see OrderType
         *
         * @return std::string - new order ID, "" if fatal error
         */
        std::string createOrder(
            int qty,
            double price,
            OrderSide side,
            OrderType type
        );

        /**
         * @brief Modify an outstanding order in this order book. The order ID
         * is checked to see if it is valid. The correct order is modified, if
         * valid. The order modification is logged in the order history.
         * Once the order modification is processed, the match orders event is
         * run.
         *
         * @param orderId - ID of the order to modify
         * @param qty - quantity of the order
         * @param price - price of the order; Only used for certian order types
         *                @see OrderType
         *
         * @return std::string - order ID if modified order, "" if fatal error
         */
        std::string modifyOrder(
            std::string orderId,
            int qty,
            double price
        );

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