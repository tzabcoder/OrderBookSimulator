
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
};