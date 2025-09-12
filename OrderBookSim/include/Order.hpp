// Global Includes
#include <string>

/**
 * @brief Specifies the values for valid order sides.
 */
enum class OrderSide {
    BUY,
    SELL
};

/**
 * @brief Specifies the values for valid order types.
 *
 * @note The following order tyes REQUIRE an order price:
 *    - LIMIT
 *    - STOP
 *    - ICEBERG
 */
enum class OrderType {
    MARKET,
    LIMIT,
    STOP,
    FOK,   // Fill-or-kill
    IOC,   // Immediate-or-cancel
    ICEBERG
};

class Order {
    public:
        /**
         * @brief Constructor for a new order object. The constructor
         * parameters are agent specifiable fields.
         *
         * @param symbol - symbol of the security
         * @param qty - quantitiy of the security
         * @param price - price to trade; specified for specifiec orders @see OrderType
         * @param side - order side @see OrderSide
         * @param type - order type @see OrderType
         */
        Order(
            std::string symbol,
            int qty,
            double price,
            OrderSide side,
            OrderType type
        );

        /**
         * @brief Update the remaining order quantity with the quantity that has been
         * executed. This is used for partial fill orders.
         *
         * @param executedQty - quantity that has been filled
         */
        void updateRemainingQty(int executedQty);

        /**
         * @brief Updates the order fill status.
         *
         * @param status - true if FULLY filled; false otherwise
         */
        void updateOrderStatus(bool status);

        /**
         * @brief Accessor functions for the order object (getters).
         *
         * getOrderId() - gets this order's identifier
         * getOrderQty() - gets the submitted quantity for this order
         * getOrderRemainingQty() - gets the remaining order quantity for the order (partial fills)
         * getOrderTimestamp() - gets this orders timestamp (when order was creted on the server)
         * getOrderPrice() - gets the price to execute order (for price conditional orders)
         * getOrderSymbol() - gets the symbol for the security
         * getOrderStatus() - gets the order status; true if fully filled, false otherwise
         * getOrderSide() - gets the side of the order
         * getOrderType() - gets the type of the order submitted
         */
        std::string getOrderId() const;
        int getOrderQty() const;
        int getOrderRemainingQty() const;
        long long getOrderTimestamp() const;
        double getOrderPrice() const;
        std::string getOrderSymbol() const;
        bool getOrderStatus() const;
        OrderSide getOrderSide() const;
        OrderType getOrderType() const;

    private:
        /**
         * @brief Generates an order ID based on the order's timestamp and a random
         * component.
         * @see SPEC.md for order ID structure.
         *
         * @return string - order id for this order
         */
        std::string generateOrderId();

        std::string orderId; // Order identifier
        std::string symbol;  // Symbol of the security traded
        int qty;             // Quantity of the security to trade
        int remainingQty;    // Remaining quantity for partial fills
        long long timestamp; // Time order was created
        double price;        // Specified price to trade; relevant for price-contingent orders
        bool filledStatus;   // True if the order is fully filled, false otherwise

        OrderSide orderSide; // Side of the order @see OrderSide
        OrderType orderType; // Type of the order @see OrderType
};