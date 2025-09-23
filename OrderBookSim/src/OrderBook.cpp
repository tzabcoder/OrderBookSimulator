// Project Includes
#include <OrderBook.hpp>

#include <iostream>

//#########################################################################
OrderBook::OrderBook (std::string exchangeSymbol) :
    exchangeSymbol(exchangeSymbol),
    buyOrders(),
    sellOrders(),
    orderHistory(),
    tradeHistory() {}

//#########################################################################
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

//#########################################################################
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

//#########################################################################
std::string OrderBook::cancelOrder(
    std::string orderId,
    ErrorCode& errCode
) {
    std::string m_orderId = "";

    // Validate the order exists
    Order* order = findOrder(orderId);

    if (order) {
        removeOrder(*order);

        errCode = ErrorCode::OK;
    }
    // Order not found
    else {
        errCode = ErrorCode::BAD_ID;
    }

    return m_orderId;
}

//#########################################################################
Order* OrderBook::findOrder(std::string orderId) {
    auto index = orderIndex.find(orderId);

    if (index != orderIndex.end()) {
        auto [price, orderIterator] = index->second;

        return &(*orderIterator);
    }

    return nullptr;
}

//#########################################################################
void OrderBook::matchOrders(Order& order) {
    std::cout << "Matching Orders..." << std::endl;
}

//#########################################################################
void OrderBook::insertOrder(Order& order) {
    // Get the correct book side
    auto& book = (order.getOrderSide() == OrderSide::BUY) ? buyOrders : sellOrders;

    // Get the orders associated with the order price
    // If no orders, create a new list for the price level
    auto& priceOrders = book[order.getOrderPrice()];
    priceOrders.push_back(order);

    // Save the iterator to the newly inserted order
    auto iterator = std::prev(priceOrders.end());
    orderIndex[order.getOrderId()] = {order.getOrderPrice(), iterator};
}

//#########################################################################
void OrderBook::removeOrder(Order& order) {
    // Get the correct book side
    auto& book = (order.getOrderSide() == OrderSide::BUY) ? buyOrders : sellOrders;

    std::string cancelId = order.getOrderId();

    auto index = orderIndex.find(cancelId);

    if (index != orderIndex.end()) {
        // Extract the order details
        auto [price, orderIterator] = index->second;

        // Remove order from the book
        auto& priceOrders = book[price];
        priceOrders.erase(orderIterator);

        // If there are no more orders for the price level, remove the price
        if (priceOrders.empty()) {
            book.erase(price);
        }

        // Remove the order ID
        orderIndex.erase(index);
    }
}

//#########################################################################
void OrderBook::logOrderHistory(Order& order) {
    orderHistory.push_back(order);
}

//#########################################################################
void OrderBook::logTradeHistory(Trade& trade) {
    tradeHistory.push_back(trade);
}