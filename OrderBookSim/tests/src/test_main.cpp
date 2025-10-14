// Project Includes
#include <Order_UT.hpp>
#include <OrderBook_UT.hpp>
#include <OrderBookManager_UT.hpp>
#include <Trade_UT.hpp>

#include <iostream>

int main() {
    // Run order unit tests
    Order_UT orderUT;
    orderUT.runTests();

    std::cout << "TRADE UTs" << std::endl;
    // Run trade unit tests
    Trade_UT tradeUT;
    tradeUT.runTests();

    // Run order book unit tests

    // Run order book manager unit tests

    return 0;
}