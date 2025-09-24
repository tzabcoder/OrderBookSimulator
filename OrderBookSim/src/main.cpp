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
 *
 * @return int - engine status code
 */
int main(int argc, char* argv[]) {
    int port = 8080;
    std::vector<std::string> exchangeSymbols;

    // Create the new order book manager
    OrderBookManager obManager = OrderBookManager(
        port,
        exchangeSymbols
    );

    // Run the order book manager
    obManager.startListener();

    return 0;
}