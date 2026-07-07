/**
 * @file parking_space.cpp
 * @brief Source skeleton for ParkingSpace from design.md.
 *
 * This file intentionally contains only documented function outlines. The
 * actual parking-space logic is left for later implementation.
 */

#include "pgof/parking_space.hpp"

namespace pgof {

namespace {

bool sameCarRequest(const Car& left, const Car& right) {
    return left.reqtime == right.reqtime && left.size == right.size;
}

}  // namespace

/**
 * @brief Purpose: update this space's occupancy value.
 * @param None.
 * @return Nothing.
 */
void ParkingSpace::updateOccupancy() {
    occupancy = 0;

    if (cars == nullptr) {
        isfull = false;
        return;
    }

    for (const Car& car : *cars) {
        occupancy += car.size;
    }

    isfull = occupancy > 0;
}

/**
 * @brief Purpose: check whether this parking space is full.
 * @param None.
 * @return bool indicating whether the space is full.
 */
bool ParkingSpace::checkSpace() const {
    return isfull;
}

/**
 * @brief Purpose: insert a car into this parking space.
 * @param car Car object that should be inserted.
 * @return Nothing.
 */
void ParkingSpace::insert(Car car) {
    const bool canAcceptCar = cars != nullptr && cars->empty() && car.size > 0 && car.size <= capacity;
    if (!canAcceptCar) {
        updateOccupancy();
        return;
    }

    car.fee = static_cast<float>(car.size * car.reqtime);
    cars->push_back(car);
    updateOccupancy();
}

/**
 * @brief Purpose: remove a car from this parking space.
 * @param car Car object that should be removed.
 * @return Nothing.
 */
void ParkingSpace::remove(Car car) {
    if (cars == nullptr) {
        updateOccupancy();
        return;
    }

    for (auto parkedCar = cars->begin(); parkedCar != cars->end(); ++parkedCar) {
        if (sameCarRequest(*parkedCar, car)) {
            cars->erase(parkedCar);
            break;
        }
    }

    updateOccupancy();
}

}  // namespace pgof
