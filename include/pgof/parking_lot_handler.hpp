/**
 * @file parking_lot_handler.hpp
 * @brief Declares the ParkingLotHandler class outlined in design.md.
 *
 * ParkingLotHandler is the handler responsible for owning the list of parking
 * spaces, initializing spaces from N1/N2/N3, parking cars, and unparking cars.
 * This file only captures the structure from design.md.
 */

#pragma once

#include <vector>

#include "pgof/car.hpp"
#include "pgof/parking_space.hpp"

namespace pgof {

/**
 * @brief Handler class that manages ParkingSpace objects.
 */
class ParkingLotHandler {
public:
    int n1{};
    int n2{};
    int n3{};
    std::vector<ParkingSpace> spaces;

    /**
     * @brief Default constructor for an empty parking-lot handler.
     */
    ParkingLotHandler() = default;

    /**
     * @brief Purpose: construct the lot from the N1, N2, and N3 capacity values.
     * @param N1 Number of size-1 parking spaces.
     * @param N2 Number of size-2 parking spaces.
     * @param N3 Number of size-3 parking spaces.
     * TODO: Define exactly how spaces are created from each capacity value.
     */
    ParkingLotHandler(int N1, int N2, int N3);

    /**
     * @brief Return the largest currently empty space capacity.
     */
    int getLargestAvailableSpaceCapacity() const;

    /**
     * @brief Check whether a car can fit in any currently empty space.
     */
    bool canPark(const Car& car) const;

    /**
     * @brief Count currently parked cars.
     */
    int getParkedCarCount() const;

    /**
     * @brief Purpose: park a car by triggering dequeueCar behavior.
     * @param None.
     * @return Car selected for parking.
     *
     * TODO: Connect this outline to CarQueue, ParkingSpace, and FeeHandler.
     */
    Car park();

    /**
     * @brief Park the supplied car into a compatible empty space.
     */
    Car park(Car car);

    /**
     * @brief Reduce remaining time for parked cars and unpark expired vehicles.
     */
    std::vector<Car> tickParkedCars();

    /**
     * @brief Unpark every currently parked car.
     */
    std::vector<Car> unparkAll();

    /**
     * @brief Purpose: unpark a car from the managed parking spaces.
     * @param car Car object that should be unparked.
     * @return Nothing.
     *
     * TODO: Define how the handler locates and releases a parked car.
     */
    void unpark(Car car);
};

}  // namespace pgof
