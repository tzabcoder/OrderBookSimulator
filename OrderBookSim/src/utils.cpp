// Global Includes
#include <chrono>
#include <random>

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
};