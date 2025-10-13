// Global Includes
#include <iostream>

// Project Includes
#include <Order.hpp>
#include <Types.hpp>

class Order_UT {
    public:
        /**
         * @brief Create the test order for unit tests.
         */
        Order_UT() : testOrder(
                "TEST",
                100,
                100.0,
                OrderSide::BUY,
                OrderType::MARKET
            ) {

            // Log test header
            std::cout << "Order UT: " << testOrder.getOrderId() << " ==========" << std::endl;

            totalTests = 0;
            invalidTests = 0;
        }

        /**
         * @brief Runs all Order unit tests.
         *
         * @return true if all unit tests pass; false otherwise
         */
        bool runTests () {
            bool testResult = true;

            // Run order unit tests
            testResult &= testOrderValues();
            testResult &= testUpdateQty();
            testResult &= testUpdateRemainingQty();
            testResult &= testUpdatePrice();
            testResult &= testUpdateFillPrice();
            testResult &= testUpdateOrderStatus();

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
            std::cout << "Order_UT Results ======================" << std::endl;
            std::cout << "Passed Tests:  " << passedTests << std::endl;
            std::cout << "Invalid Tests: " << invalidTests << std::endl;
            std::cout << "Total Tests:   " << totalTests << std::endl;
            std::cout << "Pass Rate:     " << passRate * 100 << "%" << std::endl;
            std::cout << "=======================================" << std::endl;
        }

        /**
         * @brief Test the order parameters after order creation.
         *
         * @return true if passed test case; false otherwise
         */
        bool testOrderValues() {
            std::cout << "Order_UT:testOrderValues() ";

            bool testResult = true;

            // Validate order parameters
            if (testOrder.getOrderSymbol() != "TEST" ||
                testOrder.getOrderQty() != 100 ||
                testOrder.getOrderPrice() != 100.0 ||
                testOrder.getOrderSide() != OrderSide::BUY ||
                testOrder.getOrderType() != OrderType::MARKET ||
                testOrder.getOrderStatus() != false ||
                testOrder.getOrderFillPrice() != 0.0 ||
                testOrder.getOrderRemainingQty() != 100) {

                testResult = false;
            }

            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test update order quantity.
         *
         * @return true if passed test case; false otherwise
         */
        bool testUpdateQty() {
            std::cout << "Order_UT:testUpdateQty() ";

            bool testResult = true;

            const int newQty = 1000;

            // Positive quantity
            testOrder.updateQty(newQty);
            testResult = (testOrder.getOrderQty() == newQty);

            // Negative quantity
            testOrder.updateQty(-1);
            testResult = (testOrder.getOrderQty() == newQty);

            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test update order remaining quantity.
         *
         * @return true if test case passed; false otherwise
         */
        bool testUpdateRemainingQty() {
            std::cout << "Order_UT:testUpdateRemainingQty() ";

            bool testResult = true;

            // Restore original order quantity
            testOrder.updateQty(100);

            const int executedQty = 10;
            const int remainingQty = 90;

            // Valid remaining quantity (non-zero)
            testOrder.updateRemainingQty(executedQty);
            testResult = (testOrder.getOrderRemainingQty() == remainingQty);

            // Invalid remaining quantity
            testOrder.updateRemainingQty(1000);
            testResult = (testOrder.getOrderRemainingQty() == remainingQty);

            // Valid remaining quantity (zero)
            testOrder.updateRemainingQty(remainingQty);
            testResult = (testOrder.getOrderRemainingQty() == 0);

            // Invalid remaining quanitity
            testOrder.updateRemainingQty(executedQty);
            testResult = (testOrder.getOrderRemainingQty() == 0);

            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test update order price.
         *
         * @return true if test case passed; false otherwise
         */
        bool testUpdatePrice() {
            std::cout << "Order_UT:testUpdatePrice() ";

            bool testResult = true;

            const double newPrice = 200.0;

            // Positive price
            testOrder.updatePrice(newPrice);
            testResult = (testOrder.getOrderPrice() == newPrice);

            // Negative price
            testOrder.updateQty(-1);
            testResult = (testOrder.getOrderPrice() == newPrice);

            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test update order fill price.
         *
         * @return true if test case passed; false otherwise
         */
        bool testUpdateFillPrice() {
            std::cout << "Order_UT:testUpdateFillPrice() ";

            bool testResult = true;

            const double newFillPrice = 200.1;

            // Positive price
            testOrder.updateFillPrice(newFillPrice);
            testResult = (testOrder.getOrderFillPrice() == newFillPrice);

            // Negative price
            testOrder.updateFillPrice(-1);
            testResult = (testOrder.getOrderFillPrice() == newFillPrice);

            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test update order status.
         *
         * @return true if test case passed; false otherwise
         */
        bool testUpdateOrderStatus() {
            std::cout << "Order_UT:testUpdateOrderStatus() ";

            bool testResult = true;

            testOrder.updateOrderStatus(true);
            testResult = (testOrder.getOrderStatus() == true);

            testOrder.updateOrderStatus(false);
            testResult = (testOrder.getOrderStatus() == false);

            processTestResult(testResult);

            return testResult;
        }

        // Order for unit test operations
        Order testOrder;

        // Test counters
        int totalTests;
        int invalidTests;
};