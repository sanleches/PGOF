/**
 * @file car.hpp
 * @brief Declares the Car structure outlined in design.md.
 *
 * This file represents the vehicle data object from the base UML. A Car stores
 * the requested parking time, remaining parking time, size, and fee fields.
 * No behavior is implemented here yet because design.md only outlines data for
 * this class.
 */

#pragma once

namespace pgof {

/**
 * @brief Vehicle data object tracked by the garage system.
 *
 * Fields come directly from design.md:
 * - reqtime: requested parking duration.
 * - remainingtime: time left before the car should be unparked.
 * - size: car size bucket, expected to be 1, 2, or 3.
 * - fee: fee assigned to this car.
 */
class Car {
public:
    int reqtime{};
    int remainingtime{};
    int size{};
    float fee{};

    Car(int reqtime, int size){
        this->reqtime = reqtime;
        this->remainingtime = reqtime;
        this->size = size;

        this->fee = calculateIndividualFee();
    }
};

}  // namespace pgof
