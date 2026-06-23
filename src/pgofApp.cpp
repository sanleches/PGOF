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

PgofApp::PgofApp() {
    carQueue.queue = &waitingCars;
}

/**
 * @brief Purpose: call GarageCapacityService and receive N1, N2, and N3.
 * @param None.
 * @return CapacityValue containing the N1, N2, and N3 capacity values.
 *
 * Requests capacity values from GarageCapacityService and stores N1/N2/N3.
 */
void PgofApp::callGarageCapacityService() {
    const garage::garage_capacity garageCapacity = garage::calculate_garage_capacity(capacity);
    N1 = garageCapacity.n1;
    N2 = garageCapacity.n2;
    N3 = garageCapacity.n3;
}

void PgofApp::initialize() {
    callGarageCapacityService();
    parkingLot.initialize(N1, N2, N3);
    carQueue.queue = &waitingCars;
    totalFees = 0.0F;
    totalParkedVehicles = 0;
    feeHandler.fees.clear();
    timeHandler.time = 0;
}

void PgofApp::enqueueCar(Car car) {
    if (car.remainingtime <= 0) {
        car.remainingtime = car.reqtime;
    }

    carQueue.enqueue(car);
}

Car PgofApp::park() {
    Car parkedCar = parkingLot.park(carQueue);
    if (parkedCar.size <= 0) {
        return parkedCar;
    }

    feeHandler.recordFee(parkedCar);
    totalFees = feeHandler.CalculateTotalFeesOnExit();
    ++totalParkedVehicles;
    return parkedCar;
}

std::vector<Car> PgofApp::tick() {
    timeHandler.tick();
    return parkingLot.tickAndUnparkExpired();
}

void PgofApp::unpark(Car car) {
    parkingLot.unpark(car);
}

}  // namespace pgof
