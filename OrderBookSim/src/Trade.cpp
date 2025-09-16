// Global Includes
#include <sstream>

// Project Includes
#include <Trade.hpp>

Trade::Trade (
    std::string symbol,
    std::string buyId,
    std::string sellId,
    int qty,
    double price
) : tradeId(""),
    buyOrderId(buyId),
    sellOrderId(sellId),
    symbol(symbol),
    qty(qty),
    timestamp(0),
    price(price) {

    // Set the trade timestamp
    timestamp = utils::generateMSTimestamp();

    // Generate the trade ID
    tradeId = generateTradeId();
}

std::string Trade::generateTradeId() {
    std::stringstream trade_oss;

    // Timestamp set in the constructor
    trade_oss << timestamp << "_" << utils::generateRandom_6DigitNum();

    // Return the formed order ID
    return trade_oss.str();
}

std::string Trade::getTradeId() {
    return tradeId;
}

std::string Trade::getBuyOrderId() {
    return buyOrderId;
}

std::string Trade::getSellOrderId() {
    return sellOrderId;
}

std::string Trade::getSymbol() {
    return symbol;
}

int Trade::getQty() {
    return qty;
}

long long Trade::getTimestamp() {
    return timestamp;
}

double Trade::getPrice() {
    return price;
}