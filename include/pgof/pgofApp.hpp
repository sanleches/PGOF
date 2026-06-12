/**
 * @file main.hpp
 * @brief Declares the main control structure outlined in design.md.
 *
 * main represents the primary entry/control point from the UML and sequence
 * diagram. It stores total fees, total capacity, and the N1/N2/N3 capacity
 * values returned by GarageCapacityService.
 */

#pragma once

#include "pgof/garage_capacity_service.hpp"

namespace pgof {

/**
 * @brief Main control structure for the PGOF system.
 */
class  {
public:
    float totalFees{};
    int capacity{};
    int N1{};
    int N2{};
    int N3{};

    /**
     * @brief Purpose: call GarageCapacityService and receive N1, N2, and N3.
     * @param None.
     * @return CapacityValue containing the N1, N2, and N3 capacity values.
     *
     * TODO: Store returned capacity values in N1, N2, and N3.
     */

    do{

    }while();
};

}  // namespace pgof
