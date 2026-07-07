/**
 * @file fee_handler.cpp
 * @brief Source skeleton for FeeHandler from design.md.
 *
 * This file implements fee tracking and simple runtime file logging.
 */

#include "pgof/fee_handler.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

namespace {

constexpr const char* feeLogPath = "fees.log";
constexpr const char* operationLogPath = "operations.log";

std::string timestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::string value = std::ctime(&time);

    if (!value.empty() && value.back() == '\n') {
        value.pop_back();
    }

    return value;
}

void appendLogLine(const char* path, const std::string& message) {
    std::ofstream logFile(path, std::ios::app);
    if (logFile.is_open()) {
        logFile << '[' << timestamp() << "] " << message << '\n';
    }
}

}  // namespace

/**
 * @brief Purpose: log fees to a local file.
 * @param None.
 * @return Nothing.
 */
void pgof::FeeHandler::logFeesToFile() const {
    appendLogLine(feeLogPath, "final_total=" + std::to_string(totalfees));
}

void pgof::FeeHandler::logFeeCollected(float fee) const {
    appendLogLine(feeLogPath, "fee_collected=" + std::to_string(fee)
        + " running_total=" + std::to_string(totalfees));
}

void pgof::FeeHandler::logOperation(const std::string& operation) const {
    appendLogLine(operationLogPath, operation);
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
