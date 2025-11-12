// Project Includes
#include <Order.hpp>
#include <UnitTest.hpp>

class Order_UT : public UnitTest {
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
            logTestHeader(testName);
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

            logTestResults(testName);

            return testResult;
        }

    private:
        // ========== UT Functions ==========
        /**
         * @brief Test the order parameters after order creation.
         *
         * @return true if passed test case; false otherwise
         */
        bool testOrderValues() {
            logTestName("Order_UT::testOrderValues()");

            bool testResult = true;

            // Validate order parameters
            if (testOrder.getOrderSymbol() !="TEST" ||
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
            logTestName("Order_UT::testUpdateQty()");

            bool testResult = true;

            const int newQty = 1000;

            // Positive valid quantity
            testOrder.updateQty(newQty);
            testResult = (testOrder.getOrderQty() == newQty);

            // Zero invalid quantity (qty should not change)
            testOrder.updateQty(0);
            testResult = (testOrder.getOrderQty() == newQty);

            // Negative invalid quantity (qty should not change)
            testOrder.updateQty(-1);
            testResult = (testOrder.getOrderQty() == newQty);

            processTestResult(testResult);

            return testResult;
        }

        /**
         * @brief Test update remaining order quantity.
         *
         * @return true if test case passed; false otherwise
         */
        bool testUpdateRemainingQty() {
            logTestName("Order_UT::testUpdateRemainingQty()");

            bool testResult = true;

            // Restore original order quantity
            testOrder.updateQty(100);

            const int executedQty = 10;
            const int remainingQty = 90;
            const int invalidQty = 1000;

            // Valid remaining quantity (not all remaining shares)
            testOrder.updateRemainingQty(executedQty);
            testResult = (testOrder.getOrderRemainingQty() == remainingQty);

            // Invalid remaining quantity
            testOrder.updateRemainingQty(invalidQty);
            testResult = (testOrder.getOrderRemainingQty() == remainingQty);

            // Valid remaining quantity (all remaining shares)
            testOrder.updateRemainingQty(remainingQty);
            testResult = (testOrder.getOrderRemainingQty() == 0);

            // Invalid remaining quanitity, after no remaining qty
            testOrder.updateRemainingQty(invalidQty);
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
            logTestName("Order_UT::testUpdatePrice()");

            bool testResult = true;

            const double newPrice = 200.0;

            // Positive price
            testOrder.updatePrice(newPrice);
            testResult = (testOrder.getOrderPrice() == newPrice);

            // Zero price
            testOrder.updatePrice(0);
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
            logTestName("Order_UT::testUpdateFillPrice()");

            bool testResult = true;

            const double newFillPrice = 200.1;

            // Positive price
            testOrder.updateFillPrice(newFillPrice);
            testResult = (testOrder.getOrderFillPrice() == newFillPrice);

            // Zero price
            testOrder.updateFillPrice(0);
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
            logTestName("Order_UT::testUpdateOrderStatus()");

            bool testResult = true;

            testOrder.updateOrderStatus(true);
            testResult = (testOrder.getOrderStatus() == true);

            testOrder.updateOrderStatus(false);
            testResult = (testOrder.getOrderStatus() == false);

            processTestResult(testResult);

            return testResult;
        }

        // ========== UT Variables ==========
        // Order for unit test operations
        Order testOrder;

        const std::string testName =")Order_UT";
};