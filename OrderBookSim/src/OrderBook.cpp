// Project Includes
#include <OrderBook.hpp>

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
    std::string orderId = "-1";

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
        orderHistory.push_back({OrderStatus::CREATE, newOrder});

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
    std::string m_orderId = "-1";

    // Validate the order exists
    Order* order = findOrder(orderId);

    if (order) {
        // Check if order was partially filled
        if (order->getOrderQty() == order->getOrderRemainingQty()) {
            // Validate order parameters
            if (qty <= 0) {
                errCode = ErrorCode::BAD_QTY;
            }
            else if (price <= 0.00) {
                errCode = ErrorCode::BAD_PRICE;
            }
            else {
                // Create a local copy to preserve iterator pointer
                // Copy the order ID to preserve order details
                Order modifiedOrder = *order;
                modifiedOrder.copyOrderId(order->getOrderId());

                // Update the order attributes
                modifiedOrder.updateQty(qty);

                // Only update the order price if specific order type
                //! NOTE: LIMIT, STOP, ICEBERG orders need prices
                //! NOTE: MARKET, FOK, IOC orders ignore price
                if (modifiedOrder.getOrderType() == OrderType::LIMIT ||
                    modifiedOrder.getOrderType() == OrderType::STOP ||
                    modifiedOrder.getOrderType() == OrderType::ICEBERG) {
                    modifiedOrder.updatePrice(price);

                    // Remove the order from the old price level
                    removeOrder(*order);
                    insertOrder(modifiedOrder);
                }

                orderHistory.push_back({OrderStatus::MODIFY, *order});

                m_orderId = modifiedOrder.getOrderId();

                // Run matching event
                matchOrders(modifiedOrder);

                errCode = ErrorCode::OK;
            }
        }
        // Order was partially filled
        else {
            errCode = ErrorCode::PARTIAL_FILL;
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
    std::string m_orderId = "-1";

    // Validate the order exists
    Order* order = findOrder(orderId);
    orderHistory.push_back({OrderStatus::CANCEL, *order});

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
    // Average execution price
    int totalShares = order.getOrderQty() - order.getOrderRemainingQty();
    double totalValue = order.getOrderFillPrice();

    // Opposite order book
    auto& oppBook = (order.getOrderSide() == OrderSide::BUY) ? sellOrders : buyOrders;

    // Loop through the order book prices (while there is an remaining order quantity)
    for (auto bookItr = oppBook.begin(); bookItr != oppBook.end() && order.getOrderRemainingQty() > 0;) {
        // Check price crossing conditions
        bool priceCross = (order.getOrderSide() == OrderSide::BUY)
                          ? (order.getOrderPrice() >= bookItr->first)
                          : (order.getOrderPrice() <= bookItr->first);

        if (order.getOrderType() == OrderType::LIMIT ||
            order.getOrderType() == OrderType::STOP  ||
            order.getOrderType() == OrderType::ICEBERG) {

            if (!priceCross) {
                break;
            }
        }

        auto& restingOrders = bookItr->second;

        // Loop through the resting orders at the given price level
        for (auto restingItr = restingOrders.begin(); restingItr != restingOrders.end() && order.getOrderRemainingQty() > 0;) {
            // Get the resting order
            Order& restingOrder = *restingItr;

            // Min ensures that updated quantity is never negative
            int matchQty = std::min(order.getOrderRemainingQty(), restingOrder.getOrderRemainingQty());
            totalShares += matchQty;

            // Create the trade object
            std::string buyId = (order.getOrderSide() == OrderSide::BUY) ? order.getOrderId() : restingOrder.getOrderId();
            std::string sellId = (order.getOrderSide() == OrderSide::SELL) ? order.getOrderId() : restingOrder.getOrderId();

            Trade trade(
                exchangeSymbol,
                buyId,
                sellId,
                matchQty,
                restingOrder.getOrderPrice()
            );
            tradeHistory.push_back(trade);

            // Execute the trade
            order.updateRemainingQty(matchQty);
            restingOrder.updateRemainingQty(matchQty);
            totalValue += restingOrder.getOrderPrice() * matchQty;

            // Fully filled resting order
            if (restingOrder.getOrderRemainingQty() == 0) {
                orderIndex.erase(restingOrder.getOrderId());
                restingItr = restingOrders.erase(restingItr);
            }
            else {
                // Move to the next order (at the current price level)
                restingItr++;
            }
        }

        // Fully exhausted all orders at the current price level
        if (restingOrders.empty()) {
            bookItr = oppBook.erase(bookItr);
        }
        else {
            // Move to the next price level
            bookItr++;
        }
    }

    if (totalShares > 0) {
        order.updateFillPrice(totalValue / totalShares);
    }

    // Partial order fill
    // Partial market orders are thrown away
    if (order.getOrderRemainingQty() > 0) {
        if (order.getOrderType() == OrderType::LIMIT) {
            insertOrder(order);
        }

        order.updateOrderStatus(false);
    }
    // Fully filled
    else {
        order.updateOrderStatus(true);
    }
}

//#########################################################################
void OrderBook::insertOrder(Order& order) {
    // Get the correct book side
    auto& book = (order.getOrderSide() == OrderSide::BUY) ? buyOrders : sellOrders;

    // Get the orders associated with the order price
    // If no orders, create a new list for the price level
    if (book.find(order.getOrderPrice()) != book.end()) {
        auto& priceOrders = book.at(order.getOrderPrice());
        priceOrders.push_back(order);

        // Save the iterator to the newly inserted order
        auto iterator = std::prev(priceOrders.end());
        orderIndex[order.getOrderId()] = {order.getOrderPrice(), iterator};
    }
    else {
        // Create the new price level
        book.insert({order.getOrderPrice(), {order}});

        // Save the iterator to the newly inserted order
        auto iterator = std::prev(book[order.getOrderPrice()].end());
        orderIndex[order.getOrderId()] = {order.getOrderPrice(), iterator};
    }
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
std::string OrderBook::getOrderBookExchangeSymbol() {
    return exchangeSymbol;
}

//#########################################################################
std::vector<Trade> OrderBook::getTradeHistory() {
    return tradeHistory;
}

//#########################################################################
std::vector<std::pair<OrderStatus, Order>> OrderBook::getOrderBookHistory() {
    return orderHistory;
}

//#########################################################################
std::map<double, std::list<Order>> OrderBook::getActiveBuyOrders() {
    return buyOrders;
}

//#########################################################################
std::map<double, std::list<Order>> OrderBook::getActiveSellOrders() {
    return sellOrders;
}