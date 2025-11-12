// Project Includes
#include <Trade.hpp>
#include <UnitTest.hpp>

class Trade_UT : public UnitTest {
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
            logTestHeader(testName);
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

            logTestResults(testName);

            return testResult;
        }

    private:
        // ========== UT Functions ==========
        /**
         * @brief Test get trade buy order ID.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetBuyOrderID() {
            logTestName("Trade_UT::testGetBuyOrderID()");

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
            logTestName("Trade_UT::testGetSellOrderID()");

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
            logTestName("Trade_UT::testGetSymbol()");

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
            logTestName("Trade_UT::testGetQty()");

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
            logTestName("Trade_UT::testGetPrice()");

            bool testResult = (testTrade.getPrice() == price);
            processTestResult(testResult);

            return testResult;
        }

        // ========== UT Variables ==========
        // Initial trade parameters
        const std::string symbol = "TEST";
        const std::string buyID = "1757529878230_538411";
        const std::string sellID = "1757529878230_538412";
        const int qty = 10;
        const double price = 100.0;

        // Trade for unit test operations
        Trade testTrade;

        const std::string testName = "Trade_UT";
};