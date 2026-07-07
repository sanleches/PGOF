/**
 * @file parking_lot_handler.cpp
 * @brief Source skeleton for ParkingLotHandler from design.md.
 *
 * This file outlines the handler functions used by main in the sequence
 * diagram. No parking-space creation, parking, or unparking logic is implemented.
 */

#include "pgof/parking_lot_handler.hpp"

namespace pgof {

namespace {

bool hasParkedCar(const ParkingSpace& space, const Car& car) {
    if (space.cars == nullptr) {
        return false;
    }

    for (const Car& parkedCar : *space.cars) {
        if (parkedCar.size == car.size && parkedCar.reqtime == car.reqtime) {
            return true;
        }
    }

    return false;
}

bool isEmptyCompatibleSpace(const ParkingSpace& space, const Car& car) {
    return space.cars != nullptr && space.cars->empty() && car.size > 0 && car.size <= space.capacity;
}

}  // namespace

/**
 * @brief Purpose: construct the lot from the N1, N2, and N3 capacity values.
 * @param N1 Number of size-1 parking spaces.
 * @param N2 Number of size-2 parking spaces.
 * @param N3 Number of size-3 parking spaces.
 */
ParkingLotHandler::ParkingLotHandler(int N1, int N2, int N3) {
    n1 = N1;
    n2 = N2;
    n3 = N3;

    const int totalSpaces = (N1 > 0 ? N1 : 0) + (N2 > 0 ? N2 : 0) + (N3 > 0 ? N3 : 0);
    spaces.reserve(totalSpaces);

    auto addSpaces = [this](int count, int capacity) {
        for (int i = 0; i < count; ++i) {
            ParkingSpace space{};
            space.capacity = capacity;
            space.isfull = false;
            space.occupancy = 0;
            spaces.push_back(space);
        }
    };

    addSpaces(N1, 1);
    addSpaces(N2, 2);
    addSpaces(N3, 3);
}

int ParkingLotHandler::getLargestAvailableSpaceCapacity() const {
    int largestCapacity = 0;

    for (const ParkingSpace& space : spaces) {
        if (space.cars != nullptr && space.cars->empty() && space.capacity > largestCapacity) {
            largestCapacity = space.capacity;
        }
    }

    return largestCapacity;
}

bool ParkingLotHandler::canPark(const Car& car) const {
    for (const ParkingSpace& space : spaces) {
        if (isEmptyCompatibleSpace(space, car)) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Purpose: park a car by triggering dequeueCar behavior.
 * @param None.
 * @return Car selected for parking.
 *
 * TODO: Dequeue a car, check spaces, point a space to the car, and log fees.
 */
Car ParkingLotHandler::park() {
    return {};
}

Car ParkingLotHandler::park(Car car) {
    for (ParkingSpace& space : spaces) {
        if (!isEmptyCompatibleSpace(space, car)) {
            continue;
        }

        space.insert(car);
        if (space.cars != nullptr && !space.cars->empty()) {
            return space.cars->front();
        }

        return {};
    }

    return {};
}

std::vector<Car> ParkingLotHandler::tickParkedCars() {
    std::vector<Car> expiredCars;

    for (ParkingSpace& space : spaces) {
        if (space.cars == nullptr) {
            space.updateOccupancy();
            continue;
        }

        for (auto parkedCar = space.cars->begin(); parkedCar != space.cars->end();) {
            --parkedCar->remainingtime;

            if (parkedCar->remainingtime <= 0) {
                expiredCars.push_back(*parkedCar);
                parkedCar = space.cars->erase(parkedCar);
            } else {
                ++parkedCar;
            }
        }

        space.updateOccupancy();
    }

    return expiredCars;
}

/**
 * @brief Purpose: unpark a car from the managed parking spaces.
 * @param car Car object that should be unparked.
 * @return Nothing.
 *
 * TODO: Release the car from the appropriate ParkingSpace.
 */
void ParkingLotHandler::unpark(Car car) {
    for (ParkingSpace& space : spaces) {
        if (hasParkedCar(space, car)) {
            space.remove(car);
            return;
        }
    }
}

}  // namespace pgof
