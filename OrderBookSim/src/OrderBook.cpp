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

        // Run matching event
        matchOrders(newOrder);

        errCode = ErrorCode::OK;
    }

    return orderId;
}

std::string OrderBook::modifyOrder(
    std::string orderId,
    int qty,
    double price,
    ErrorCode& errCode
) {
    std::string m_orderId = "";

    // Validate the order exists
    Order* order = findOrder(orderId);

    if (order) {
        // Validate order parameters
        if (qty <= 0) {
            errCode = ErrorCode::BAD_QTY;
        }
        else if (price <= 0.00) {
            errCode = ErrorCode::BAD_PRICE;
        }
        else {
            // Update the order attributes
            order->updateQty(qty);
            order->updatePrice(price);

            m_orderId = order->getOrderId();

            // Run matching event
            matchOrders(*order);

            errCode = ErrorCode::OK;
        }
    }
    // Order not found
    else {
        errCode = ErrorCode::BAD_ID;
    }

    return m_orderId;
}

std::string OrderBook::cancelOrder(
    std::string orderId,
    ErrorCode& errCode
) {
    std::string m_orderId = "";

    // Validate the order exists
    Order* order = findOrder(orderId);

    if (order) {
        removeOrderFromBook(*order);

        errCode = ErrorCode::OK;
    }
    // Order not found
    else {
        errCode = ErrorCode::BAD_ID;
    }

    return m_orderId;
}

Order* OrderBook::findOrder(std::string orderId) {
    // Check the BUY orders
    for (Order& t_order : buyOrders) {
        if (t_order.getOrderId() == orderId) {
            return &t_order;
        }
    }

    // Check SELL orders
    for (Order& t_order: sellOrders) {
        if (t_order.getOrderId() == orderId) {
            return &t_order;
        }
    }

    return nullptr;
}

void OrderBook::matchOrders(Order& order) {

}

void OrderBook::addOrderToBook(Order& order) {

}

void OrderBook::removeOrderFromBook(Order& order) {
    // BUY side
    if (order.getOrderSide() == OrderSide::BUY) {
        for (auto iter = buyOrders.begin(); iter != buyOrders.end(); iter++) {
            if (iter->getOrderId() == order.getOrderId()) {
                // Erase the order and terminate
                buyOrders.erase(iter);
                return;
            }
        }
    }
    // SELL side
    else {
        for (auto iter = sellOrders.begin(); iter != sellOrders.end(); iter++) {
            if (iter->getOrderId() == order.getOrderId()) {
                // Erase the order and terminate
                sellOrders.erase(iter);
                return;
            }
        }
    }
}

void OrderBook::logOrderHistory(Order& order) {
    orderHistory.push_back(order);
}

void OrderBook::logTradeHistory(Trade& trade) {
    tradeHistory.push_back(trade);
}