// Global Includes
#include <map>
#include <string>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>

// Project Includes
#include <OrderBook.hpp>
#include <Types.hpp>

class OrderBookManager {
    public:
        /**
         * @brief Constructor for a new Order Book Manager object.
         *
         * @param port - listen for OrderRequests
         * @param symbols - symbols to create order books
         */
        OrderBookManager(
            int port,
            std::vector<std::string> symbols
        );

        void startListener();

    private:
        int createSocket();
        int cleanupSocket();

        int obmPort;      // Order book manager port
        SOCKET obmSocket; // Listener socket for order book manager

        // Map of the exchange symbol and the order book
        // Key => exchange symbol, value => associated order book
        std::map<std::string, OrderBook> orderBookMap;
};