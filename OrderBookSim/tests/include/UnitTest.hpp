// Global Includes
#include <iostream>
#include <string>

#ifndef UNITTEST_H
#define UNITTEST_H

class UnitTest {
    public:
        UnitTest() : totalTests(0), invalidTests(0) {}

        /**
         * @brief Log the unit test header.
         *
         * @param unitTestName - name of the unit test
         */
        void logTestHeader(const std::string unitTestName) {
            std::cout << unitTestName  << " ====================" << std::endl;
        }

        /**
         * @brief Log the unit test name.
         *
         * @param testName - name of the individual test.
         */
        void logTestName(const std::string testName) {
            std::cout << testName << " ";
        }

        /**
         * @brief Log the result status and update the
         * test counters.
         *
         * @param result - true if passed test; false otherwise
         */
        void processTestResult(bool result){
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
         * @brief Logs the unit test results.
         *
         * @param unitTestName - name of the unit test
         */
        void logTestResults(const std::string unitTestName) {
            int passedTests = totalTests - invalidTests;
            double passRate = passedTests / totalTests;

            // Log test statistics
            std::cout << unitTestName << " Results ======================" << std::endl;
            std::cout << "Passed Tests:  " << passedTests << std::endl;
            std::cout << "Invalid Tests: " << invalidTests << std::endl;
            std::cout << "Total Tests:   " << totalTests << std::endl;
            std::cout << "Pass Rate:     " << passRate * 100 << "%" << std::endl;
            std::cout << "=======================================" << std::endl;
        }

    private:
        int totalTests;
        int invalidTests;
};

#endif // UNITTEST_H