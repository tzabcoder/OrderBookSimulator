// Global Includes
#include <list>
#include <map>
#include <string>
#include <unordered_map>
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

        /**
         * @brief Match order logic for filling orders in the order book. Orders are filled
         * based on price-time priority. The order matching is run only when a new order is
         * created or an existing order is modified.
         * NOTE: Any partial fills for market orders will discard the remainder. Limit orders
         * are added to the order book.
         *
         * @param order - order that was updated/created
         */
        void matchOrders(Order& order);

        /**
         * @brief Inserts an order into the order book based on price-time priority. The
         * order's price is the first (primary) indexer and the time of arrival is the
         * second indexer for the order book.
         * Each price in the order book has a list of associated orders.
         *
         * @param order - order to insert into the order book
         */
        void insertOrder(Order& order);

        /**
         * @brief Remove an order from the order book.
         * NOTE: Order details are validated before removal.
         *
         * @param order - order to remove from the order book
         */
        void removeOrder(Order& order);

        std::string exchangeSymbol; // Symbol for the order book's traded security

        // Key => price, value => list of orders at that price, sorted by time
        std::map<double, std::list<Order>> buyOrders;  // List of all active buy orders
        std::map<double, std::list<Order>> sellOrders; // List of all active sell orders

        // Map of Order IDs and their indexes
        // Key => order ID, value => pair(price, pointer index)
        std::unordered_map<std::string, std::pair<double, std::list<Order>::iterator>> orderIndex;

        std::vector<std::pair<OrderStatus, Order>> orderHistory; // History of all order events in the order book
        std::vector<Trade> tradeHistory;                         // History of all trades in the order book (matched orders)
};