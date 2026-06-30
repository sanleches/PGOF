/**
 * @file pgofApp.hpp
 * @brief Declares the PGOF application controller outlined in design.md.
 *
 * PgofApp represents the primary PGOF controller from the UML and sequence
 * diagram. main.cpp is only an executable entry point that uses this library.
 */

#pragma once

#include <queue>
#include <string>
#include <vector>

#include "pgof/car.hpp"
#include "pgof/car_queue.hpp"
#include "pgof/fee_handler.hpp"
#include "pgof/garage_capacity.hpp"
#include "pgof/parking_lot_handler.hpp"
#include "pgof/time_handler.hpp"

namespace pgof {

/**
 * @brief Snapshot of application metrics for end-of-run reporting.
 */
struct PgofReport {
    int capacity{};
    int n1{};
    int n2{};
    int n3{};
    int totalParkedVehicles{};
    float totalFees{};
    int currentTime{};
    int waitingCars{};
};

/**
 * @brief Application controller for the PGOF system.
 */
class PgofApp {
public:
    PgofApp();
    explicit PgofApp(int totalSpaces);

    float totalFees{};
    int totalParkedVehicles{};
    int capacity{};
    int N1{};
    int N2{};
    int N3{};

    ParkingLotHandler parkingLot;
    std::queue<Car> waitingCars;
    CarQueue carQueue;
    FeeHandler feeHandler;
    TimeHandler timeHandler;

    /**
     * @brief Purpose: call GarageCapacityService and receive N1, N2, and N3.
     * @return void
     *
     * Stores returned capacity values in N1, N2, and N3.
     */
    void callGarageCapacityService();

    /**
     * @brief Discover capacity and initialize all runtime services.
     */
    void initialize();

    /**
     * @brief Set total capacity and initialize all runtime services.
     */
    void initialize(int totalSpaces);

    /**
     * @brief Read-only accessors for startup capacity values.
     */
    int getCapacity() const;
    int getN1() const;
    int getN2() const;
    int getN3() const;

    /**
     * @brief Accept a car into the waiting line.
     */
    void enqueueCar(Car car);

    /**
     * @brief Convenience method to submit a car without manually building a Car object.
     */
    void submitCar(int size, int requestedTime);

    /**
     * @brief Park the next car selected by the PGOF parking policy.
     */
    Car park();

    /**
     * @brief Advance time and unpark expired vehicles.
     */
    std::vector<Car> tick();

    /**
     * @brief Explicitly release a car from the parking lot.
     */
    void unpark(Car car);

    /**
     * @brief Produce a metrics snapshot for final reporting.
     */
    PgofReport getReport() const;

    /**
     * @brief Produce a user-facing text report.
     */
    std::string getReportText() const;
};

}  // namespace pgof
