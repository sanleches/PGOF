/**
 * @file fee_handler.hpp
 * @brief Declares the FeeHandler runtime logger outlined in design.md.
 *
 * FeeHandler is the runtime logger responsible for logging fees to a local file
 * and calculating total fees on exit. Only the structure is represented here.
 */

#pragma once

namespace pgof {

/**
 * @brief Runtime logger for fee-related behavior.
 */
class FeeHandler {
public:
    float totalfees{};


    /**
     * @brief Purpose: log fees to a local file.
     * @param None.
     * @return Nothing.
     *
     * TODO: Define file location, format, and when this should be called.
     */
    void logFeesToFile();

    /**
     * @brief Purpose: calculate total fees when the system exits.
     * @param None.
     * @return Total fees as a floating-point value.
     *
     * TODO: Define whether this reads from memory, a file, or both.
     */
    float getTotalFees() const;

    void addFee(float fee);

    float calculateIndividualFee(int carSize, int requestedTime);

    void CalculateIndividualFee(int carSize, int requestedTime, bool addToTotal);
};

}  // namespace pgof
