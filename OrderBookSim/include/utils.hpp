// Project Includes
#include <Types.hpp>

namespace utils {
    /**
     * @brief Generates a random 6-digit number using the Mersenne
     * Twister randomizer. The randomizer and distribution are static
     * to retain thier seed.
     *
     * @return long long - random 6-digit number
     */
    int generateRandom_6DigitNum();

    /**
     * @brief Generates a timestamp in the format of milliseconds
     * since Unix epoch.
     *
     * @return long long - timesamp in millisecond format
     */
    long long generateMSTimestamp();

    /**
     * @brief Validate whether an order side is within the
     * OrderSide enumeration.
     *
     * @param side - order side to validate
     *
     * @return bool - true if order side exists; false otherwise
     */
    bool validOrderSide(OrderSide side);

    /**
     * @brief Validate whether an order type is within the
     * OrderType enumeration.
     *
     * @param type - order type to validate
     *
     * @return bool - true if order type exists; false otherwise
     */
    bool validOrderType(OrderType type);
}; // utils