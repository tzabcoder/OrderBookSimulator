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

        /**
         * @brief Handle the order request message.
         *
         * @param buffer - string message from client
         *
         * @return OrderReponse - response of the order request.
         */
        OrderResponse handleMessage(std::string& buffer);

        /**
         * @brief Serialize an Order Response message from the order book.
         * Converts a OrderResponse message (struct) to a string that can be sent
         * over the socket.
         *
         * @param response - order response message from the order book
         *
         * @return std::string - serializes (string) of the response
         */
        std::string serialize(const OrderResponse& response);

        /**
         * @brief Deserialize an Order Request message sent by the client.
         * Converts a string buffer to an OrderResponse (struct) message.
         *
         * @param buffer - string (serialized) order request message
         *
         * @return OrderRequest - order request message
         */
        OrderRequest deserialize(const std::string& buffer);


        bool logging;     // True to log to console, false otherwise
        int obmPort;      // Order book manager port
        int BUFFER_SIZE;  // Size of the receive buffer
        SOCKET obmSocket; // Listener socket for order book manager

        // Map of the exchange symbol and the order book
        // Key => exchange symbol, value => associated order book
        std::map<std::string, OrderBook> orderBookMap;
};