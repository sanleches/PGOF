/**
 * @file pgofApp.cpp
 * @brief Source skeleton for PgofApp from design.md.
 *
 * This file outlines the setup action where PgofApp requests capacity from
 * GarageCapacityService, stores N1/N2/N3, and later passes those values to
 * ParkingLotHandler. No system loop or setup logic is implemented yet.
 */

#include "pgof/pgofApp.hpp"

namespace pgof {

/**
 * @brief Purpose: call GarageCapacityService and receive N1, N2, and N3.
 * @param None.
 * @return CapacityValue containing the N1, N2, and N3 capacity values.
 *
 * TODO: Request capacity value from GarageCapacityService and store N1/N2/N3.
 */
void PgofApp::callGarageCapacityService() {
    const garage::garage_capacity garageCapacity = garage::calculate_garage_capacity(capacity);
    N1 = garageCapacity.n1;
    N2 = garageCapacity.n2;
    N3 = garageCapacity.n3;
}

}  // namespace pgof
