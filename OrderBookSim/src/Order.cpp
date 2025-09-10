// Global Includes
#include <chrono>
#include <sstream>
#include <random>

// Project Includes
#include <Order.hpp>

Order::Order (
    std::string symbol,
    int qty,
    double price,
    OrderSide side,
    OrderType type
) : orderId(""),
    timestamp(0),
    filledStatus(false),
    symbol(symbol),
    qty(qty),
    remainingQty(qty),
    price(price),
    orderSide(side),
    orderType(type) {

    // Set the timestamp
    timestamp = getTimestamp();

    // Generate the order ID
    orderId = generateOrderId();
}

long long Order::getTimestamp() {
    // Generate the number of milliseconds since the last epoch
    return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count();
}

std::string Order::generateOrderId() {
    std::stringstream order_oss;
    order_oss << timestamp << "_" << generateRandomOrderId();

    // Return the formed order ID
    return order_oss.str();
}

long long Order::generateRandomOrderId() {
    // Seed randomizer (Mersenne Twister)
    static std::mt19937 t_gen(std::random_device{}());

    // Uniform integer distribution
    static std::uniform_int_distribution<long long> t_dist(lowerBound, upperBound);

    // Return the random number
    return t_dist(t_gen);
}

void Order::updateRemainingQty(int executedQty) {
    remainingQty = remainingQty - executedQty;
}

void Order::updateOrderStatus(bool status) {
    filledStatus = status;
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