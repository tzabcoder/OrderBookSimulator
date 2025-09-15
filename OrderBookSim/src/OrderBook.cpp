// Project Includes
#include <OrderBook.hpp>

OrderBook::OrderBook (std::string exchangeSymbol) :
    exchangeSymbol(exchangeSymbol),
    buyOrders(),
    sellOrders(),
    orderHistory(),
    tradeHistory() {}

std::string OrderBook::createOrder(
    int qty,
    double price,
    OrderSide side,
    OrderType type
) {

}

std::string OrderBook::modifyOrder(
    std::string orderId,
    int qty,
    double price
) {

}