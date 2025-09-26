#pragma once

// Global Includes
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Specifies the system logging levels.
 */
enum class LogLevel {
    INFO,  // Informational logging
    DEBUG, // Debug logging
    WARN,  // Warning logging
    ERR    // Error logging
};

/**
 * @brief Get the current timestamp in string format. The timestamp
 * format is: %Y-%m-%d %H:%M:%S
 *
 * @return std::string - string of the current timestamp
 */
inline std::string currentTimestamp() {
    auto now     = std::chrono::system_clock::now();
    auto time_t  = std::chrono::system_clock::to_time_t(now);
    auto ms      = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) % 1000;

    // Build the timestamp string
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

/**
 * @brief Log a message to the console at the correct logging level.
 *
 * @param level - level to log the message
 * @param message - message to log to the console
 * @param logEnabled - true if logging enabled; false to not log message
 */
inline void logMessage(LogLevel level,
                       const std::string& message,
                       bool logEnabled = false) {

    // Logging not enabled
    if (!logEnabled) return;

    std::cout << "[" << currentTimestamp() << "] ";

    // Log the correct level information
    switch (level) {
        case LogLevel::INFO:  std::cout << "[INFO] ";  break;
        case LogLevel::DEBUG: std::cout << "[DEBUG] "; break;
        case LogLevel::WARN:  std::cout << "[WARN] ";  break;
        case LogLevel::ERR:   std::cout << "[ERROR] "; break;
    }

    std::cout << message << std::endl;
}