/**
 * @file parking_space.cpp
 * @brief Source skeleton for ParkingSpace from design.md.
 *
 * This file intentionally contains only documented function outlines. The
 * actual parking-space logic is left for later implementation.
 */

#include "pgof/parking_space.hpp"

namespace pgof {

/**
 * @brief Purpose: update this space's occupancy value.
 * @param None.
 * @return Nothing.
 *
 * TODO: Fill in the occupancy update behavior outlined by the final design.
 */
void ParkingSpace::updateOccupancy() {
    // TODO: Implement occupancy recalculation.
}

/**
 * @brief Purpose: check whether this parking space is full.
 * @param None.
 * @return bool indicating whether the space is full.
 *
 * TODO: Fill in the fullness check behavior outlined by the final design.
 */
bool ParkingSpace::checkSpace() const {
    // TODO: Implement space fullness check.
    return isfull;
}

/**
 * @brief Purpose: insert a car into this parking space.
 * @param car Car object that should be inserted.
 * @return Nothing.
 *
 * TODO: Fill in the car insertion behavior outlined by the final design.
 */
void ParkingSpace::insert(Car car) {
    // TODO: Implement car insertion into this parking space.
}

/**
 * @brief Purpose: remove a car from this parking space.
 * @param car Car object that should be removed.
 * @return Nothing.
 *
 * TODO: Fill in the car removal behavior outlined by the final design.
 */
void ParkingSpace::remove(Car car) {
    // TODO: Implement car removal from this parking space.
}

}  // namespace pgof
