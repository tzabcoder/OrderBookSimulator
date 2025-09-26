// Global Includes
#include <iostream>
#include <string>
#include <vector>

// Project Includes
#include <OrderBookManager.hpp>

/**
 * @brief Runs the order book simulation engine
 *
 * @param argc - number of command line arguements
 * @param argv - command line arguements
 *
 * Command line arguements
 * -p (port) : port for the order book simulator
 * -s (symbols) : symbols for the order books (will
 * create one for each symbol)
 * -l : for order book manager console logging
 *
 * @return int - engine status code
 */
int main(int argc, char* argv[]) {
    // Default parameters
    int port = 8080;
    bool consoleLog = true; // TEST => will be set to false
    std::vector<std::string> exchangeSymbols = {"TEMP"}; // TEST => will be empty

    // Create the new order book manager
    OrderBookManager obManager = OrderBookManager(
        port,
        exchangeSymbols,
        consoleLog
    );

    // Run the order book manager
    obManager.startListener();

    return 0;
}