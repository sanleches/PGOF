/**
 * @file pgofApp.cpp
 * @brief Source skeleton for PgofApp from design.md.
 *
 * This file outlines the setup action where PgofApp requests capacity from
 * GarageCapacityService, stores N1/N2/N3, and later passes those values to
 * ParkingLotHandler. No system loop or setup logic is implemented yet.
 */

#include "pgof/pgofApp.hpp"

#include <sstream>

namespace pgof {

PgofApp::PgofApp() {
    carQueue.queue = &waitingCars; // Initialize the car queue with the waiting cars vector
}

PgofApp::PgofApp(int totalSpaces) : PgofApp() {
    initialize(totalSpaces);
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
    parkingLot = ParkingLotHandler(N1, N2, N3);
    carQueue.queue = &waitingCars; // Re-initialize the car queue with the waiting cars vector
    totalFees = 0.0F;
    totalParkedVehicles = 0;
    feeHandler.fees.clear();
    timeHandler.time = 0;
}

void PgofApp::initialize(int totalSpaces) {
    capacity = totalSpaces;
    initialize();
}

int PgofApp::getCapacity() const {
    return capacity;
}

int PgofApp::getN1() const {
    return N1;
}

int PgofApp::getN2() const {
    return N2;
}

int PgofApp::getN3() const {
    return N3;
}

void PgofApp::enqueueCar(Car car) {
    if (car.remainingtime <= 0) {
        car.remainingtime = car.reqtime;
    }

    carQueue.enqueue(car);
}

void PgofApp::submitCar(int size, int requestedTime) {
    Car car{};
    car.size = size;
    car.reqtime = requestedTime;
    car.remainingtime = requestedTime;
    enqueueCar(car);
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

PgofReport PgofApp::getReport() const {
    PgofReport report{};
    report.capacity = capacity;
    report.n1 = N1;
    report.n2 = N2;
    report.n3 = N3;
    report.totalParkedVehicles = totalParkedVehicles;
    report.totalFees = totalFees;
    report.currentTime = timeHandler.time;
    report.waitingCars = static_cast<int>(waitingCars.size());
    return report;
}

std::string PgofApp::getReportText() const {
    const PgofReport report = getReport();
    std::ostringstream output;
    output << "PGOF report\n"
           << "capacity: " << report.capacity << '\n'
           << "N1: " << report.n1 << '\n'
           << "N2: " << report.n2 << '\n'
           << "N3: " << report.n3 << '\n'
           << "total parked vehicles: " << report.totalParkedVehicles << '\n'
           << "total fees: " << report.totalFees << '\n'
           << "current time: " << report.currentTime << '\n'
           << "waiting cars: " << report.waitingCars;
    return output.str();
}

}  // namespace pgof
