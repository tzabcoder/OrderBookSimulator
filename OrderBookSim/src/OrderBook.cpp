// Project Includes
#include <OrderBook.hpp>

OrderBook::OrderBook (std::string exchangeSymbol) :
    exchangeSymbol(exchangeSymbol),
    buyOrders(),
    sellOrders(),
    orderHistory(),
    tradeHistory() {}

void OrderBook::addOrderToBook(Order& order) {
    // BUY order
    if (order.getOrderSide() == OrderSide::BUY) {
        buyOrders.push_front(order);
    }
    // SELL order
    else {
        sellOrders.push_front(order);
    }
}

void OrderBook::logOrderHistory(Order& order) {
    orderHistory.push_back(order);
}

void OrderBook::logTradeHistory(Trade& trade) {
    tradeHistory.push_back(trade);
}

std::string OrderBook::createOrder(
    int qty,
    double price,
    OrderSide side,
    OrderType type,
    ErrorCode& errCode
) {
    std::string orderId = "";

    // Validate order parameters
    if (qty <= 0) {
        errCode = ErrorCode::BAD_QTY;
    }
    else if (price <= 0.00) {
        errCode = ErrorCode::BAD_PRICE;
    }
    else if (!utils::validOrderSide(side)) {
        errCode = ErrorCode::BAD_SIDE;
    }
    else if (!utils::validOrderType(type)) {
        errCode = ErrorCode::BAD_TYPE;
    }
    else {
        // Create the new order
        Order newOrder = Order(
            exchangeSymbol,
            qty,
            price,
            side,
            type
        );

        orderId = newOrder.getOrderId();

        logOrderHistory(newOrder);
        addOrderToBook(newOrder);
        matchOrders();
    }

    return orderId;
}

std::string OrderBook::modifyOrder(
    std::string orderId,
    int qty,
    double price,
    ErrorCode& errCode
) {

}

bool OrderBook::cancelOrder(
    std::string orderId,
    ErrorCode& errCode
) {

}