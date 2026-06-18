/**
 * @file pgofApp.hpp
 * @brief Declares the PGOF application controller outlined in design.md.
 *
 * PgofApp represents the primary PGOF controller from the UML and sequence
 * diagram. main.cpp is only an executable entry point that uses this library.
 */

#pragma once

#include "pgof/garage_capacity.hpp"

namespace pgof {

/**
 * @brief Application controller for the PGOF system.
 */
class PgofApp {
public:
    float totalFees{};
    int capacity{};
    int N1{};
    int N2{};
    int N3{};

    /**
     * @brief Purpose: call GarageCapacityService and receive N1, N2, and N3.
     * @return void
     *
     * TODO: Store returned capacity values in N1, N2, and N3.
     */
    void callGarageCapacityService();
};

}  // namespace pgof
