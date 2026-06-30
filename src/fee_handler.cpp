/**
 * @file fee_handler.cpp
 * @brief Source skeleton for FeeHandler from design.md.
 *
 * This file outlines fee logging and exit-time total calculation. No file I/O
 * or fee calculation logic is implemented yet.
 */

#include "pgof/fee_handler.hpp"
#include <fstream>
#include <chrono>

/**
 * @brief Purpose: log fees to a local file.
 * @param None.
 * @return Nothing.
 *
 * TODO: Implement local fee logging.
 */
void pgof::FeeHandler::logFeesToFile() {
    std::ofstream logFile("fees.log", std::ios::app);
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        logFile << "Timestamp: " << std::ctime(&time);
        logFile << "Total Fees: " << totalfees << std::endl;
        logFile << "---" << std::endl;
        logFile.close();
    }
}

float pgof::FeeHandler::getTotalFees() const {
    return totalfees;
}

void pgof::FeeHandler::addFee(float fee) {
    totalfees += fee;
}

float pgof::FeeHandler::calculateIndividualFee(int carSize, int requestedTime) {
    return carSize * requestedTime * 1.0F;
}

void pgof::FeeHandler::CalculateIndividualFee(int carSize, int requestedTime, bool addToTotal) {
    if (addToTotal) {
        addFee(calculateIndividualFee(carSize, requestedTime));
    }
}
