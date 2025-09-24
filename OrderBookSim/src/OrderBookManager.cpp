// Project Includes
#include <OrderBookManager.hpp>

//#########################################################################
OrderBookManager::OrderBookManager (
    int port,
    std::vector<std::string> symbols
) : obmPort(port),
    obmSocket(INVALID_SOCKET) {

    // Create the Order Book Map
    for (std::string symbol : symbols) {
        orderBookMap.emplace(symbol, OrderBook(symbol));
    }
}

//#########################################################################
void OrderBookManager::startListener() {
    createSocket();

    while (true) {
        // Accept client connection
        // Read Order request
        // Process order request
        // Send order response
    }

    cleanupSocket();
}

//#########################################################################
int OrderBookManager::createSocket() {
    WSADATA wsaData;
    int wsResult;

    // Initialize winsock
    wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        std::runtime_error("WSAStartup Failed: " + std::to_string(wsResult));
    }

    // Create the OBM socket
    obmSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (obmSocket == INVALID_SOCKET) {
        WSACleanup();
        std::runtime_error("Error creating OBM Socket...");
    }

    // Bind the OBM socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(obmPort);

    if (bind(obmSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cleanupSocket();
        throw std::runtime_error("Error: OBM socket bind failed...");
    }

    // Start listening on the OBM socket
    if (listen(obmSocket, SOMAXCONN) == SOCKET_ERROR) {
        cleanupSocket();
        throw std::runtime_error("Error: OBM socket listen failed...");
    }

    return 1; // Socket created
}

//#########################################################################
int OrderBookManager::cleanupSocket() {
    // Close the socket if there is an existing valid socket
    if (obmSocket != INVALID_SOCKET) {
        closesocket(obmSocket);
        WSACleanup();
        obmSocket = INVALID_SOCKET;
        return 1; // Socket closed
    }

    return -1; // No socket to close
}