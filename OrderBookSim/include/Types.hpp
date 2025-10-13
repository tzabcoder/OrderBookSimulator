// Global Includes
#include <string>

#ifndef TYPES_HPP
#define TYPES_HPP

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

/**
 * @brief Specifies the status of the order events in the order
 * book.
 */
enum class OrderStatus {
    CREATE,
    MODIFY,
    CANCEL
};

/**
 * @brief Error codes used for identifying request processing statuses
 * to return to clients.
 */
enum class ErrorCode {
	OK,
	BAD_REQUEST,  // Invalid message structure (unable to process)
	BAD_QTY,      // Invalid order quantity; must be positive
	BAD_PRICE,    // Invalid order price; must be positive
	BAD_SIDE,     // Invalid order side; See OrderSide
	BAD_TYPE,     // Invalid order type; See OrderType
    BAD_ID,       // Invalid order ID
    PARTIAL_FILL, // Cannot process because order was partially filled
    FATAL         // Unclassified fatal internal error
};

/**
 * @brief Message structure for a new order request.
 * @see OrderSide
 * @see OrderType
 */
struct OrderRequest {
    std::string symbol;  // Symbol for the order
    int qty;             // Quantity of the order
    double price;        // Price of the order
    OrderSide orderSide; // Side of the order
    OrderType orderType; // Type of the order
};

/**
 * @brief Message structure to modify an existing order.
 */
struct OrderModify {
    std::string orderId; // ID of the order to modify
    int qty;             // New quantity of the order
    double price;        // New price of of the order (required; only used for LIMIT, STOP, ICEBERG)
};

/**
 * @brief Message structure to cancel an existing order.
 */
struct OrderCancel {
    std::string orderId; // ID of the order to cancel
};

/**
 * @brief Message structure for a response to a request
 * from a client.
 * @see ErrorCode
 */
struct OrderResponse {
    std::string orderId; // ID of the order processed
    ErrorCode errCode;   // Response code of the request
};

#endif