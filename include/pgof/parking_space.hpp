/**
 * @file parking_space.hpp
 * @brief Declares the ParkingSpace class outlined in design.md.
 *
 * ParkingSpace represents one garage space with a capacity bucket, occupancy
 * value, fullness state, and a pointer to the list of cars assigned to it.
 * Function bodies are intentionally left as TODO skeletons in the source file.
 */

#pragma once

#include <vector>

#include "pgof/car.hpp"

namespace pgof {

/**
 * @brief Parking space object that points to parked Car objects.
 */
class ParkingSpace {
public:
    int capacity{};
    bool isfull{};
    int occupancy{};
    std::vector<Car>* cars{};

    /**
     * @brief Purpose: update this space's occupancy value.
     * @param None.
     * @return Nothing.
     *
     * TODO: Define how occupancy is calculated from the current car list.
     */
    void updateOccupancy();

    /**
     * @brief Purpose: check whether this parking space is full.
     * @param None.
     * @return bool indicating the isfull state.
     *
     * TODO: Define the exact fullness rule from the design before implementing.
     */
    bool checkSpace() const;

    /**
     * @brief Purpose: insert a car into this parking space.
     * @param car Car object that should be inserted.
     * @return Nothing.
     *
     * TODO: Define validation and insertion rules before implementing.
     */
    void insert(Car car);

    /**
     * @brief Purpose: remove a car from this parking space.
     * @param car Car object that should be removed.
     * @return Nothing.
     *
     * TODO: Define lookup and removal rules before implementing.
     */
    void remove(Car car);
};

}  // namespace pgof
