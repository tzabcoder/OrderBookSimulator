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
            bool testResult = (testTrade.getBuyOrderId() == buyID);

            processTestResult("Trade_UT::testGetBuyOrderID()", testResult);

            return testResult;
        }

        /**
         * @brief Test get trade sell order ID.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetSellOrderID() {
            bool testResult = (testTrade.getSellOrderId() == sellID);

            processTestResult("Trade_UT::testGetSellOrderID()", testResult);

            return testResult;
        }

        /**
         * @brief Test get trade symbol.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetSymbol() {
            bool testResult = (testTrade.getSymbol() == symbol);

            processTestResult("Trade_UT::testGetSymbol()", testResult);

            return testResult;
        }

        /**
         * @brief Test get trade quantity.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetQty() {
            bool testResult = (testTrade.getQty() == qty);

            processTestResult("Trade_UT::testGetQty()", testResult);

            return testResult;
        }

        /**
         * @brief Test get trade price.
         *
         * @return true if passed test case; false otherwise
         */
        bool testGetPrice() {
            bool testResult = (testTrade.getPrice() == price);

            processTestResult("Trade_UT::testGetPrice()", testResult);

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