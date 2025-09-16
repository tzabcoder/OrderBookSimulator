// Global Includes
#include <list>
#include <string>
#include <vector>

// Project Includes
#include <Types.hpp>
#include <Order.hpp>
#include <Trade.hpp>
#include <utils.hpp>

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
         * NOTE: Order parameters are validated before order processing.
         *
         * @param qty - quantity of the new order
         * @param price - price for order to execute; @see OrderType for use
         * @param side - side of the order; @see OrderSide
         * @param type - type of the order; @see OrderType
         * @param errCode - result status; populated in the function
         *
         * @return std::string - new order ID, "" if fatal error
         */
        std::string createOrder(
            int qty,
            double price,
            OrderSide side,
            OrderType type,
            ErrorCode& errCode
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
         * @param errCode - result status; populated in the function
         *
         * @return std::string - order ID if modified order, "" if invalid
         */
        std::string modifyOrder(
            std::string orderId,
            int qty,
            double price,
            ErrorCode& errCode
        );

        /**
         * @brief Cancel an outstanding order for this order book. The order ID is
         * checked to determine if there is a valid order. If valid, the order is
         * canceled and removed from the order book.
         *
         * @param orderId - ID of the order to cancel
         * @param errCode - result status; populated in the function
         *
         * @return std::string - order ID of the canceled order, "" if invalid
         */
        std::string cancelOrder(
            std::string orderId,
            ErrorCode& errCode
        );

    private:
        /**
         * @brief Find an order in the order book.
         *
         * @param orderId - order ID for order to find
         *
         * @return Order* - pointer to the order; nullptr if order does not exist
         */
        Order* findOrder(std::string orderId);

        void matchOrders(Order& order);

        void addOrderToBook(Order& order);

        /**
         * @brief Remove an order from the order book.
         * NOTE: Order details are validated before removal.
         *
         * @param order - order to remove from the order book
         */
        void removeOrderFromBook(Order& order);

        /**
         * @brief Log an order to the order history. The log stores the order
         * details to file.
         *
         * @param order - order to log to order history.
         */
        void logOrderHistory(Order& order);

        /**
         * @brief Log a trade to the trade history. The log stores the trade
         * details to file.
         *
         * @param trade - trade to log to trade history.
         */
        void logTradeHistory(Trade& trade);

        std::string exchangeSymbol; // Symbol for the order book's traded security

        std::list<Order> buyOrders;  // List of all active buy orders
        std::list<Order> sellOrders; // List of all active sell orders

        std::vector<Order> orderHistory; // History of all orders in the order book
        std::vector<Trade> tradeHistory; // History of all trades in the order book (matched orders)
};