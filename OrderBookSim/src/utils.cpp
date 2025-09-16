// Global Includes
#include <chrono>
#include <random>

// Project Includes
#include <utils.hpp>

namespace utils {
    #define sixDigitLower 100000 // Lower bound for 6-digit number
    #define sixDigitUpper 999999 // Upper bound for 6-digit number

    int generateRandom_6DigitNum() {
        // Seed randomizer (Mersenne Twister)
        static std::mt19937 t_gen(std::random_device{}());

        // Uniform integer distribution
        static std::uniform_int_distribution<int> t_dist(sixDigitLower, sixDigitUpper);

        // Return the random number
        return t_dist(t_gen);
    }

    long long generateMSTimestamp() {
        // Generate the number of milliseconds since the last epoch
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                ).count();
    }

    bool validOrderSide(OrderSide side) {
        bool valid = false;

        switch (side) {
            case OrderSide::BUY:
            case OrderSide::SELL:
                valid = true;
                break;
            default:
                valid = false;
                break;
        }

        return valid;
    }

    bool validOrderType(OrderType type) {
        bool valid = false;

        switch (type) {
            case OrderType::MARKET:
            case OrderType::LIMIT:
            case OrderType::STOP:
            case OrderType::FOK:
            case OrderType::IOC:
            case OrderType::ICEBERG:
                valid = true;
                break;
            default:
                valid = false;
                break;
        }

        return valid;
    }
};