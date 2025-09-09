# Order Book Simulatior Specification

**** Work in progress. ****

### Overview

An order book is a list of open buy and sell orders for a particular security, organized by specific attributes such as price or quantity. As new orders are submitted from traders (agents), the order book is updated in real-time. It is a record of market depth and displays the overall supply and demand for the security. The inside quotes are the top "bid" and lowest "ask" prices.

* *bid* - quote that a buyer is willing to pay
* *ask* - quote that a seller is willing to accept

The order book offers information about liquidity at different "levels". A deep order book, characterized by the number of orders at different price levels, suggests that there is high liquidity for the security. **Level I** market depth lists the last traded price, the best bid price, the best ask price, and the volume associated with the best bit and ask. **Level II** market depth shows both the Level I data at each price and cumulative activity information such as the cumulative volume throughout the order book. This project offers a robust and comprehensive order book simulator tool for various use cases.

### **Design**

##### **Supported Order Types**

The simulator accepts various types of buy and sell orders:

1. *Market* - order executes imediately at the best available price
2. *Limit* - order executes at a specified price or better
3. *Stop* - order that executes when a particular price is reached
4. *Fill-Or-Kill* - order to be executed immediately, otherwised canceled
5. *Immediate-Or-Cancel* - order to fill as much as possible immediately, remainder is canceled
6. *Iceberg* - large order revealed in smaller chunks

##### **Core Classes**

`Order` - single order in the orderbook (sent by the trader)

`Trade` - successful match between a buy an sell order (order execution)

`OrderBook` - manages the orders (buy and sell) in the market and actions associated with them; logs/stores the trade history

##### **Add-On Classes**

`OrderBookManager` - manages individual OrderBooks for multiple simulated securities/markets

`Agent` - participant in the market (able to submit orders); can be either manual or automated
