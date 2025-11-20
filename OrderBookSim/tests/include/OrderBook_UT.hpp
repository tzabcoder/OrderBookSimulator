// Global Includes
#include <stdexcept>

// Project Includes
#include <Order.hpp>
#include <OrderBook.hpp>
#include <Types.hpp>
#include <UnitTest.hpp>

class OrderBook_UT : public UnitTest {
    public:
        /**
         * @brief Create the test order book object.
         */
        OrderBook_UT() : orderBook(
            exchangeSymbol
        ) {
            logTestHeader(testName);
        }

        /**
         * @brief Runs all Order Book unit tests.
         *
         * @return true if all unit tests pass; false otherwise
         */
        bool runTests() {
            bool testResult = true;

            // Run order book unit tests
            testResult &= testCreateOrder();
            testResult &= testModifyOrder();
            testResult &= testCancelOrder();

            logTestResults(testName);

            return testResult;
        }

    private:
        // ========== UT Functions ==========
        /**
         * @brief Test creating orders in the order book.
         *
         * @return true if passed test case; false otherwise
         */
        bool testCreateOrder() {
            bool testResult = true;

            // Valid buy order
            ErrorCode errCode;
            std::string orderId = orderBook.createOrder(
                100,
                100.0,
                OrderSide::BUY,
                OrderType::MARKET,
                errCode
            );
            testResult = (orderId != "-1");
            testResult = (errCode == ErrorCode::OK);
            logStatusUpdate("Create valid buy order", testResult);

            // Valid sell order
            orderId = orderBook.createOrder(
                100,
                100.0,
                OrderSide::SELL,
                OrderType::MARKET,
                errCode
            );
            testResult = (orderId != "-1");
            testResult = (errCode == ErrorCode::OK);
            logStatusUpdate("Create valid sell order", testResult);

            // Invalid order quantity
            orderId = orderBook.createOrder(
                -100,
                100.0,
                OrderSide::SELL,
                OrderType::MARKET,
                errCode
            );
            testResult = (orderId == "-1");
            testResult = (errCode == ErrorCode::BAD_QTY);
            logStatusUpdate("Create invalid sell order (qty)", testResult);

            // Invalid order price
            orderId = orderBook.createOrder(
                100,
                -100.0,
                OrderSide::SELL,
                OrderType::MARKET,
                errCode
            );
            testResult = (orderId == "-1");
            testResult = (errCode == ErrorCode::BAD_PRICE);
            logStatusUpdate("Create invalid sell order (price)", testResult);

            // Invalid order side
            orderId = orderBook.createOrder(
                100,
                100.0,
                static_cast<OrderSide>(999),
                OrderType::MARKET,
                errCode
            );
            testResult = (orderId == "-1");
            testResult = (errCode == ErrorCode::BAD_SIDE);
            logStatusUpdate("Create invalid sell order (side)", testResult);

            // Invalid order type
            orderId = orderBook.createOrder(
                100,
                100.0,
                OrderSide::SELL,
                static_cast<OrderType>(999),
                errCode
            );
            testResult = (orderId == "-1");
            testResult = (errCode == ErrorCode::BAD_TYPE);
            logStatusUpdate("Create invalid sell order (type)", testResult);

            processTestResult("OrderBook_UT::testCreateOrder()", testResult);

            return testResult;
        }

        /**
         * @brief Test order modification.
         *
         * @return true if passed test case; false otherwise
         */
        bool testModifyOrder() {
            bool testResult = true;

            // Create the order
            // LIMIT order used because it requires a price
            ErrorCode errCode;
            std::string orderId = orderBook.createOrder(
                100,
                100.0,
                OrderSide::BUY,
                OrderType::LIMIT,
                errCode
            );
            testResult = (orderId != "-1");
            testResult = (errCode == ErrorCode::OK);
            logStatusUpdate("Create valid buy order", testResult);

            std::string modifiedOrderId;

            // Valid order price and quantity
            int newQty = 99;
            double newPrice = 125.5;
            modifiedOrderId = orderBook.modifyOrder(
                orderId,
                newQty,
                newPrice,
                errCode
            );
            testResult = (modifiedOrderId != "-1");
            logStatusUpdate("Modify order", testResult);

            // Validate the order details in the order book
            std::map<double, std::list<Order>> activeBuyOrders = orderBook.getActiveBuyOrders();

            try {
                // Try to get all orders at the price level
                std::list<Order> priceBuyOrders = activeBuyOrders.at(newPrice);

                if (priceBuyOrders.size() > 0) {
                    // There should only be one order at $125.50 price level
                    Order modifiedOrder = priceBuyOrders.front();

                    testResult = (modifiedOrder.getOrderQty() == newQty);
                    testResult = (modifiedOrder.getOrderPrice() == newPrice);
                }
                // No orders at the price level
                else {
                    testResult = false;
                }
            }
            // Price level DNE
            catch (const std::out_of_range &oor) {
                testResult = false;
            }
            logStatusUpdate("Check order modification", testResult);

            // Invalid order quantity
            modifiedOrderId = orderBook.modifyOrder(
                orderId,
                -100,
                100,
                errCode
            );
            testResult = (modifiedOrderId == "-1");
            testResult = (errCode == ErrorCode::BAD_QTY);
            logStatusUpdate("Invalid order modification (qty)", testResult);

            // Invalid order price
            modifiedOrderId = orderBook.modifyOrder(
                orderId,
                100,
                -100,
                errCode
            );
            testResult = (modifiedOrderId == "-1");
            testResult = (errCode == ErrorCode::BAD_PRICE);
            logStatusUpdate("Invalid order modification (price)", testResult);

            processTestResult("OrderBook_UT::testModifyOrder()", testResult);

            return testResult;
        }

        bool testCancelOrder() {
            bool testResult = true;

            processTestResult("OrderBook_UT::testCancelOrder()", testResult);

            return testResult;
        }

        // ========== UT Variables ==========
        const std::string exchangeSymbol = "TEST_OB";

        OrderBook orderBook;

        const std::string testName = "OrderBook_UT";
};