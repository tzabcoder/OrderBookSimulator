# Order Book Simulatior Specification

**** Work in progress. ****

## Overview

An order book is a list of open buy and sell orders for a particular security, organized by specific attributes such as price or quantity. As new orders are submitted from traders (agents), the order book is updated in real-time. It is a record of market depth and displays the overall supply and demand for the security. The inside quotes are the top "bid" and lowest "ask" prices.

* *bid* - quote that a buyer is willing to pay
* *ask* - quote that a seller is willing to accept

The order book offers information about liquidity at different "levels". A deep order book, characterized by the number of orders at different price levels, suggests that there is high liquidity for the security. **Level I** market depth lists the last traded price, the best bid price, the best ask price, and the volume associated with the best bit and ask. **Level II** market depth shows both the Level I data at each price and cumulative activity information such as the cumulative volume throughout the order book. This project offers a robust and comprehensive order book simulator tool for various use cases.

## **Design**

### **Supported Order Types**

The simulator accepts various types of buy and sell orders:

1. *Market* - order executes imediately at the best available price
2. *Limit* - order executes at a specified price or better
3. *Stop* - order that executes when a particular price is reached
4. *Fill-Or-Kill* - order to be executed immediately, otherwised canceled
5. *Immediate-Or-Cancel* - order to fill as much as possible immediately, remainder is canceled
6. *Iceberg* - large order revealed in smaller chunks

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

`Order` - single order in the orderbook (sent by the trader)

`Trade` - successful match between a buy an sell order (order execution)

`OrderBook` - manages the orders (buy and sell) in the market and actions associated with them; logs/stores the trade history

### **Add-On Classes**

`OrderBookManager` - manages individual OrderBooks for multiple simulated securities/markets

`Agent` - participant in the market (able to submit orders); can be either manual or automated

### Class Design

##### Order Class

The order class is the structure for *created* orders in the system. It contains datatypes to both identify and specify the order. The actions that can be performed on the order are accessing and updating data. While initiated by the agents (client), orders are created on the order book side (server). The agents are able to specify:

* Symbol
* Quantity
* Price
* Order Side
* Order Type

The remaining fields are populated and maintained by the order book.

```cpp
class Order {
	int orderId;         // Order identifier
	int qty;             // Quantity of the security to trade
	int remainingQty;    // Remaining quantity for partial fills
	long timestamp;      // Time order was created
	double price;        // Specified price to trade; relevant for certian order types
	string symbol;       // Symbol of the instrument traded
	bool filled;         // True if FULLY filled, false otherwise
	OrderSide orderSide; // Buy or Sell
	OrderKind orderType; // Kind of order sent
};
```

##### Trade Class

The trade class is the structure for *executed* orders in the system. It contains information about the executed orders (buy and sell); their agreed upon order details. The actions that can be performed on the trade are accessing trade attributes and creating the trade object (order execution).

```cpp
class Trade {
	int tradeId;     // Trade identifier
	int qty;         // Quantity of the security matched (executed)
	int buyOrderId;  // ID for the matched buy order
	int sellOrderId; // ID for the matched sell order
	long timestamp;  // Time order was executed
	double price;    // Price order was executed (matched bid and ask)
	string symbol;   // Symbol of the instrument traded
};
```

##### OrderBook Class

##### OrderBookManager

##### Agent Class
