// Global Includes
#include <string>

// Project Includes
#include <utils.hpp>

#ifndef TRADE_H
#define TRADE_H

class Trade {
    public:
        /**
         * @brief Constructor for a new trade object.
         *
         * @param symbol - symbol of instrument traded
         * @param buyId - buyer's order ID
         * @param sellId - seller's order ID
         * @param qty - quantity of instrument traded
         * @param price - price of order execution
         */
        Trade(
            std::string symbol,
            std::string buyId,
            std::string sellId,
            int qty,
            double price
        );

        /**
         * @brief Accessor functions for the trade object (getters).
         *
         * getTradeId() - gets the trade identifier
         * getBuyOrderId() - gets the matched buy order's identifier
         * getSellOrderId() - gets the matched sell order's identifier
         * getSymbol() - gets the traded symbol
         * getQty() - gets the traded quantity
         * getTimestamp() - gets the time the trade was executed
         * getPrice() - gets the price the trade was executed at
         */
        std::string getTradeId();
        std::string getBuyOrderId();
        std::string getSellOrderId();
        std::string getSymbol();
        int getQty();
        long long getTimestamp();
        double getPrice();

    private:
        /**
         * @brief Generates a trade ID based on the trade's timestamp and a random
         * component.
         * @see SPEC.md for trade ID structure.
         *
         * @return string - trade ID
         */
        std::string generateTradeId();

        std::string tradeId;     // Trade identifier
        std::string buyOrderId;  // Order ID for the matched buyer
        std::string sellOrderId; // Order ID for the matched seller
        std::string symbol;      // Symbol of the instrument traded
        int qty;                 // Quantity executed
        long long timestamp;     // Time the trade was executed (matched)
        double price;            // Price order was executed (matched)
}; // Trade

#endif // TRADE_H