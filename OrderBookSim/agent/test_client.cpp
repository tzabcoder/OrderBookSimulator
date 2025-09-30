#include <Types.hpp>

int main() {
    int port = 8080;

    // Create the test order request
    OrderRequest orderRequest;
    orderRequest.symbol    = "TEMP";
    orderRequest.qty       = 100;
    orderRequest.price     = 76.50;
    orderRequest.orderSide = OrderSide::BUY;
    orderRequest.orderType = OrderType::LIMIT;

    // create client socket
    // serialize the orderRequest
    // send the orderRequest
    // wait for the orderResponse
    // deserialize the order response

    return 0;
}