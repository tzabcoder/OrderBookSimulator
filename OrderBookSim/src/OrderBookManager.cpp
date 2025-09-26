// Project Includes
#include <OrderBookManager.hpp>

//#########################################################################
OrderBookManager::OrderBookManager (
    int port,
    std::vector<std::string> symbols,
    bool logging
) : logging(logging),
    obmPort(port),
    obmSocket(INVALID_SOCKET) {

    // Create the Order Book Map
    for (std::string symbol : symbols) {
        orderBookMap.emplace(symbol, OrderBook(symbol));
    }
}
OrderBookManager::~OrderBookManager() {
    cleanupSocket();
}

//#########################################################################
void OrderBookManager::startListener() {
    logMessage(LogLevel::INFO,
               "startListener(): Starting OBM listener socket...",
               logging);

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
    logMessage(LogLevel::INFO,
               "createSocket(): Creating OBM lsitener socket...",
               logging);

    WSADATA wsaData;
    int wsResult;

    // Initialize winsock
    wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        throw std::runtime_error("[ERROR] createSocket(): WSAStartup Failed: " + std::to_string(wsResult));
    }

    // Create the OBM socket
    obmSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (obmSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("[ERROR] createSocket(): Error creating OBM Socket...");
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(obmPort);

    // Log socket information (IP address and port)
    std::string ipString = inet_ntoa(service.sin_addr);

    logMessage(LogLevel::DEBUG,
               "createSocket(): Binding OBM socket to IP=" + ipString +
               ", Port=" + std::to_string(ntohs(service.sin_port)),
               logging);

    // Bind the OBM socket
    if (bind(obmSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cleanupSocket();
        throw std::runtime_error("[ERROR] createSocket(): OBM socket bind failed...");
    }

    // Start listening on the OBM socket
    if (listen(obmSocket, SOMAXCONN) == SOCKET_ERROR) {
        cleanupSocket();
        throw std::runtime_error("[ERROR] createSocket(): OBM socket listen failed...");
    }

    logMessage(LogLevel::INFO,
               "createSocket(): OBM socket created. Listening on port=" + std::to_string(obmPort),
               logging);

    return 1; // Socket created
}

//#########################################################################
int OrderBookManager::cleanupSocket() {
    logMessage(LogLevel::INFO,
               "cleanupSocket(): Closing OBM lsitener socket...",
               logging);

    // Close the socket if there is an existing valid socket
    if (obmSocket != INVALID_SOCKET) {
        closesocket(obmSocket);
        WSACleanup();
        obmSocket = INVALID_SOCKET;

        logMessage(LogLevel::INFO,
               "cleanupSocket(): OBM socket closed.",
               logging);

        return 1; // Socket closed
    }

    logMessage(LogLevel::WARN,
               "cleanupSocket(): Cannon close INVALID socket...",
               logging);

    return -1; // No socket to close
}