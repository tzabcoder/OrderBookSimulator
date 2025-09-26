// Global Includes
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>

// Project Includes
#include <Logger.h>
#include <OrderBook.hpp>
#include <Types.hpp>

class OrderBookManager {
    public:
        /**
         * @brief Constructor for a new Order Book Manager object.
         *
         * @param port - listen for OrderRequests
         * @param symbols - symbols to create order books
         * @param logging - console logging flag
         */
        OrderBookManager(
            int port,
            std::vector<std::string> symbols,
            bool logging
        );
        ~OrderBookManager();

        /**
         * @brief Start the order book manager socket listener. The socket
         * listens for agent connections for order request messages.
         */
        void startListener();

    private:
        /**
         * @brief Create the order book manager listener socket.
         *
         * @return int - 1 if socket created; -1 if socket not created
         */
        int createSocket();

        /**
         * @brief Close and cleanup the order book manager listener socket.
         *
         * @return int - 1 if socket closed; -1 if socket not invalid before
         * closing
         */
        int cleanupSocket();

        bool logging;     // True to log to console, false otherwise
        int obmPort;      // Order book manager port
        SOCKET obmSocket; // Listener socket for order book manager

        // Map of the exchange symbol and the order book
        // Key => exchange symbol, value => associated order book
        std::map<std::string, OrderBook> orderBookMap;
};