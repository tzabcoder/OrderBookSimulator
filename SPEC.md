# Order Book Simulatior Specification

**** Work in progress. ****

## Overview

An order book is a list of open buy and sell orders for a particular security, organized by specific attributes such as price or quantity. As new orders are submitted from traders (agents), the order book is updated in real-time. It is a record of market depth and displays the overall supply and demand for the security. The inside quotes are the highest "bid" and lowest "ask" prices.

* *bid* - quote that a buyer is willing to pay
* *ask* - quote that a seller is willing to accept

The order book offers information about liquidity at different "levels". A deep order book, characterized by the number of orders at different price levels, suggests that there is high liquidity for the security. **Level I** market depth lists the last traded price, the best bid and ask price, and the volume associated with the best bit and ask. **Level II** market depth shows both the Level I data at each price and cumulative activity information such as the cumulative volume throughout the order book. This project offers a robust and comprehensive order book simulator tool for various use cases.

## **Design**

### **Supported Order Types**

The simulator accepts various types of **buy** and **sell** orders:

1. *Market* - order executes imediately at the best available ask price
2. *Limit* - order executes at a specified price or better
3. *Stop* - order that executes when a particular price is reached
4. *Fill-Or-Kill* - order to be executed immediately, otherwised canceled
5. *Immediate-Or-Cancel* - order to fill as much as possible immediately, remainder is canceled
6. *Iceberg* - large order revealed in smaller chunks

Limit, stop, and iceberg orders require a price to be specified. If a price is specified for the other order types, it will be ignored.

```cpp
enum class OrderSide {
	BUY,
	SELL
};
```

```cpp
enum class OrderType {
	MARKET,
	LIMIT,
	STOP,
	FOK,   // Fill-Or-Kill
	IOC,   // Immediate-Or-Cancel
	ICEBERG
};
```

### **Core Classes**

`Order` - single order in the orderbook (information populated when a trade request is recieved)

`Trade` - successful match between a buy and sell order (order execution)

`OrderBook` - manages the orders in the market and actions associated with orders; logs/stores the order and trade history

### **Add-On Classes**

`OrderBookManager` - manages individual OrderBooks for multiple simulated securities/markets (server)

`Agent` - participant in the market (able to submit orders); can be either manual or automated (client)

### Class Design

##### Order Class

The order class is the structure for *created* orders in the system. It contains datatypes to both identify and specify the order. The actions that can be performed on the order are accessing and updating data. While initiated by the agents (client), orders are created on the order book side (server). The agents are able to specify:

* Symbol
* Quantity
* Price
* Order Side
* Order Type

The remaining fields are populated and maintained by the order book.

The order ID is a unique identifier for a particular order in an order book. It consists of a timestamp and a random component. The timestamp is derived from the timestamp, which is in milliseconds. The random component ensures that orders submitted at the same time from various agents has a low probability of collision. The random component is a 6-digit integer.

Order ID: {timestamp}_{random component}

Example Order ID: 1757529878230_538411

```cpp
class Order {
	string orderId;      // Order identifier
	int qty;             // Quantity of the security to trade
	int remainingQty;    // Remaining quantity for partial fills
	long long timestamp; // Time order was created
	double price;        // Specified price to trade; relevant for certian order types
	string symbol;       // Symbol of the instrument traded
	bool filled;         // True if FULLY filled, false otherwise
	OrderSide orderSide; // Buy or Sell
	OrderType orderType; // Type of order sent
};
```

##### Trade Class

The trade class is the structure for *executed* orders in the system. It contains information about the executed orders (buy and sell) and their agreed upon order details. The actions that can be performed on the trade are accessing trade attributes.

Trade ID: {timestamp}_{random component}

Example Trade ID: 1757529878230_698557

```cpp
class Trade {
	string tradeId;  // Trade identifier
	int qty;         // Quantity of the security matched (executed)
	int buyOrderId;  // ID for the matched buy order
	int sellOrderId; // ID for the matched sell order
	long timestamp;  // Time order was executed
	double price;    // Price order was executed (matched bid and ask)
	string symbol;   // Symbol of the instrument traded
};
```

##### OrderBook Class

The order book class is the main structure that maintains the list of open buy and sell orders. When an order is routed to the order book, it is added to the active orders list for processing. The order list (both buy and sell) are sorted by order price, from low to high. The order book is ranked on *price-time priority*, meaning limit orders are first sorted by price, then by arrival time (see `Order.timestamp`). This means that multiple orders at the same price levels are executed by first time of arrival. All orders, regardless of status, are added to the order history list.

Once a buy and sell order are matched, a trade object is created and the order's quantites are reduced/removed from the order book. The trade is then added to the trade history list.

The following interactions would change the order book:

* Create order - order arrives to the order book; added to the correct side (buy or sell)
* Modify order - modify agent editable fields of an order (see `Order` for editable fields)
* Cancel order - cancel an order in the order book
* Match orders - execute a trade (matching orders in the order book)

```cpp
class OrderBook {
	string instrumentSymbol;         // Symbol for the order book's security
	std::list<Order> buyOrders;      // Active buy orders; sorted by price, then by time
	std::list<Order> sellOrders;     // Active sell orders; sorted by price, then by time
	std::vector<Trade> tradeHistory; // History of all trades in the order book (matched orders)
	std::vector<Order> orderHistory; // History of all orders in the order book (all order arrivals)
};
```

##### OrderBookManager Class

The order book manager is the service that manages all order books for individual securities. The server accepts order requests from agents and routes them to the correct order book. The order response is sent back to the agent. This is a multi-threaded server application to handle many connections and order requests/responses. The interactions with the order book manager come from the `OrderRequest` and `OrderResponse` messages (see message structure section for detailed message information).

Based on the order request, the order book manager uses the symbol to call the correct order book's create order, modify order, or cancel order function.

```cpp
class OrderBookManager {
	std::map<string, OrderBook> orderBookMap; // Maps the security symbol to the corresponding order book
};
```

##### Agent Class

The agent (also known as a trader) can send `OrderRequest` messages to the order book manager. Once the order request is made, a `OrderResponse` will be sent by the server to indicate the order status.

***NOTE*:** In future versions, the agent will be simulated using a trader model, and can specify N number of agents to simulate. This will require an `AgentManager` class.

```cpp
class Agent {
	int traderId; // Agent identifier
};
```

### Order Matching Mechanics

### Order Request/Response Message Structure
