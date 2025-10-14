// Global Includes
#include <iostream>

// Project Includes
#include <Trade.hpp>

class Trade_UT {
    public:
        /**
         * @brief Create the test trade object.
         */
        Trade_UT() : testTrade(
            symbol,
            buyID,
            sellID,
            qty,
            price
        ) {
            // Log test header
            std::cout << "Trade UT: " << testTrade.getTradeId() << " ==========" << std::endl;

            totalTests = 0;
            invalidTests = 0;
        }

        /**
         * @brief Runs all Trade unit tests.
         *
         * @return true if all unit tests pass; false otherwise
         */
        bool runTests () {
            bool testResult = true;

            // Run trade unit tests
            testResult &= testGetBuyOrderID();
            testResult &= testGetSellOrderID();
            testResult &= testGetSymbol();
            testResult &= testGetQty();
            testResult &= testGetPrice();

            logTestResults();

            return testResult;
        }

    private:
        /**
         * @brief Processes the unit test results.
         *
         * @param result test result
         */
        void processTestResult(bool result) {
            totalTests += 1;

            // Log test result
            if (result) {
                std::cout << "passed." << std::endl;
            }
            else {
                invalidTests += 1;
                std::cout << "failed..." << std::endl;
            }
        }

        /**
         * @brief Logs the total unit test results.
         */
        void logTestResults() {
            int passedTests = totalTests - invalidTests;
            double passRate = passedTests / totalTests;

            // Log test statistics
            std::cout << "Trade_UT Results ======================" << std::endl;
            std::cout << "Passed Tests:  " << passedTests << std::endl;
            std::cout << "Invalid Tests: " << invalidTests << std::endl;
            std::cout << "Total Tests:   " << totalTests << std::endl;
            std::cout << "Pass Rate:     " << passRate * 100 << "%" << std::endl;
            std::cout << "=======================================" << std::endl;
        }

        /**
         * @brief Test get trade buy order ID.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetBuyOrderID() {
            std::cout << "Trade_UT:testGetBuyOrderID() ";

            bool testResult = (testTrade.getBuyOrderId() == buyID);
            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test get trade sell order ID.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetSellOrderID() {
            std::cout << "Trade_UT:testGetSellOrderID() ";

            bool testResult = (testTrade.getSellOrderId() == sellID);
            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test get trade symbol.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetSymbol() {
            std::cout << "Trade_UT:testGetSymbol() ";

            bool testResult = (testTrade.getSymbol() == symbol);
            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test get trade quantity.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetQty() {
            std::cout << "Trade_UT:testGetQty() ";

            bool testResult = (testTrade.getQty() == qty);
            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test get trade price.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetPrice() {
            std::cout << "Trade_UT:testGetPrice() ";

            bool testResult = (testTrade.getPrice() == price);
            processTestResult(testResult);

            return testResult;
        }

        // Initial trade parameters
        const std::string symbol = "TEST";
        const std::string buyID = "1757529878230_538411";
        const std::string sellID = "1757529878230_538412";
        const int qty = 10;
        const double price = 100.0;

        // Trade for unit test operations
        Trade testTrade;

        // Test counters
        int totalTests;
        int invalidTests;
};