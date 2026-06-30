/**
 * @file fee_handler.cpp
 * @brief Source skeleton for FeeHandler from design.md.
 *
 * This file outlines fee logging and exit-time total calculation. No file I/O
 * or fee calculation logic is implemented yet.
 */

#include "pgof/fee_handler.hpp"

/**
 * @brief Purpose: log fees to a local file.
 * @param None.
 * @return Nothing.
 *
 * TODO: Implement local fee logging.
 */
void FeeHandler::logFeesToFile() {
    // TODO: Implement fee logging to a local file.
}

float FeeHandler::getTotalFees() const {
    return totalfees;
}

void FeeHandler::addFee(float fee) {
    totalfees += fee;
}

float FeeHandler::calculateIndividualFee(int carSize, int requestedTime) {
    return carSize * requestedTime * 1.0F;
}

void FeeHandler::CalculateIndividualFee(int carSize, int requestedTime, bool addToTotal) {
    if (addToTotal) {
        addFee(calculateIndividualFee(carSize, requestedTime));
    }
}
