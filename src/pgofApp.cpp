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
#include <string>

namespace pgof {

namespace {

std::string describeCar(const Car& car) {
    std::ostringstream output;
    output << "size=" << car.size << " requested_time=" << car.reqtime
           << " remaining_time=" << car.remainingtime << " fee=" << car.fee;
    return output.str();
}

}  // namespace

PgofApp::PgofApp() {
    carQueue.queue = &waitingCars;
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
    feeHandler.totalfees = 0.0F;
    timeHandler.time = 0;
    feeHandler.logOperation("initialize capacity=" + std::to_string(capacity)
        + " n1=" + std::to_string(N1) + " n2=" + std::to_string(N2)
        + " n3=" + std::to_string(N3));
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
    feeHandler.logOperation("enqueue " + describeCar(car));
}

void PgofApp::submitCar(int size, int requestedTime) {
    Car car{};
    car.size = size;
    car.reqtime = requestedTime;
    car.remainingtime = requestedTime;
    enqueueCar(car);
}

Car PgofApp::park() {
    carQueue.queue = &waitingCars;
    if (waitingCars.empty()) {
        feeHandler.logOperation("park skipped reason=no_waiting_cars");
        return {};
    }

    const int largestAvailableSpace = parkingLot.getLargestAvailableSpaceCapacity();
    if (largestAvailableSpace <= 0) {
        feeHandler.logOperation("park skipped reason=no_empty_spaces");
        return {};
    }

    Car selectedCar{};
    if (parkingLot.canPark(waitingCars.front())) {
        selectedCar = carQueue.dequeueCar(false);
    } else {
        selectedCar = carQueue.dequeueFirstEligible(largestAvailableSpace);
    }

    if (selectedCar.size <= 0) {
        feeHandler.logOperation("park skipped reason=no_eligible_car");
        return {};
    }

    Car parkedCar = parkingLot.park(selectedCar);
    if (parkedCar.size <= 0) {
        feeHandler.logOperation("park skipped reason=selected_car_not_parked " + describeCar(selectedCar));
        return parkedCar;
    }

    feeHandler.addFee(parkedCar.fee);
    totalFees = feeHandler.getTotalFees();
    ++totalParkedVehicles;
    feeHandler.logOperation("parked " + describeCar(parkedCar));
    feeHandler.logFeeCollected(parkedCar.fee);
    return parkedCar;
}

std::vector<Car> PgofApp::tick() {
    timeHandler.tick();
    feeHandler.logOperation("tick time=" + std::to_string(timeHandler.time));
    std::vector<Car> unparked = parkingLot.tickParkedCars();
    for (const Car& car : unparked) {
        feeHandler.logOperation("expired_unpark " + describeCar(car));
    }
    park();
    return unparked;
}

void PgofApp::unpark(Car car) {
    parkingLot.unpark(car);
    feeHandler.logOperation("manual_unpark " + describeCar(car));
}

PgofReport PgofApp::finish() {
    feeHandler.logOperation("finish started time=" + std::to_string(timeHandler.time));

    const std::vector<Car> unparkedCars = parkingLot.unparkAll();
    for (const Car& car : unparkedCars) {
        feeHandler.logOperation("finish_unpark " + describeCar(car));
    }

    const int waitingCarCount = static_cast<int>(waitingCars.size());
    while (!waitingCars.empty()) {
        waitingCars.pop();
    }

    if (waitingCarCount > 0) {
        feeHandler.logOperation("finish_cleared_waiting_cars count=" + std::to_string(waitingCarCount));
    }

    totalFees = feeHandler.getTotalFees();
    feeHandler.logFeesToFile();
    feeHandler.logOperation("finish complete total_fees=" + std::to_string(totalFees)
        + " total_parked_vehicles=" + std::to_string(totalParkedVehicles));

    return getReport();
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
    report.parkedCars = parkingLot.getParkedCarCount();
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
           << "waiting cars: " << report.waitingCars << '\n'
           << "parked cars: " << report.parkedCars;
    return output.str();
}

PgofApp createParkingLot(int totalSpaces) {
    return PgofApp{totalSpaces};
}

}  // namespace pgof
