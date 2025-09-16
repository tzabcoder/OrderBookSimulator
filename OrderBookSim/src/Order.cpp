// Global Includes
#include <sstream>

// Project Includes
#include <Order.hpp>

Order::Order (
    std::string symbol,
    int qty,
    double price,
    OrderSide side,
    OrderType type
) : orderId(""),
    symbol(symbol),
    qty(qty),
    remainingQty(qty),
    timestamp(0),
    price(price),
    filledStatus(false),
    orderSide(side),
    orderType(type) {

    // Set the timestamp
    timestamp = utils::generateMSTimestamp();

    // Generate the order ID
    orderId = generateOrderId();
}

std::string Order::generateOrderId() {
    std::stringstream order_oss;

    // Timestamp set in the constructor
    order_oss << timestamp << "_" << utils::generateRandom_6DigitNum();

    // Return the formed order ID
    return order_oss.str();
}

void Order::updateRemainingQty(int executedQty) {
    remainingQty = remainingQty - executedQty;
}

void Order::updateOrderStatus(bool status) {
    filledStatus = status;
}

void Order::updateQty(int t_qty) {
    qty = t_qty;
}

void Order::updatePrice(double t_price) {
    price = t_price;
}

std::string Order::getOrderId() const {
    return orderId;
}

int Order::getOrderQty() const {
    return qty;
}

int Order::getOrderRemainingQty() const {
    return remainingQty;
}

long long Order::getOrderTimestamp() const {
    return timestamp;
}

double Order::getOrderPrice() const {
    return price;
}

std::string Order::getOrderSymbol() const {
    return symbol;
}

bool Order::getOrderStatus() const {
    return filledStatus;
}

OrderSide Order::getOrderSide() const {
    return orderSide;
}

OrderType Order::getOrderType() const {
    return orderType;
}