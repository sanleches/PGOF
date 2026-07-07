#include "pgof/pgofApp.hpp"

#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr int defaultTicks = 12;

struct ScheduledArrival {
    int time{};
    int size{};
    int requestedTime{};
};

void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <total-spaces> [ticks]\n";
}

int parseTicks(int argc, char* argv[]) {
    if (argc == 3) {
        const int ticks = std::stoi(argv[2]);
        if (ticks <= 0) {
            throw std::invalid_argument("ticks must be greater than zero");
        }

        return ticks;
    }

    return defaultTicks;
}

void submitArrivals(pgof::PgofApp& garage, const std::vector<ScheduledArrival>& arrivals, int currentStep) {
    for (const ScheduledArrival& arrival : arrivals) {
        if (arrival.time != currentStep) {
            continue;
        }

        garage.submitCar(arrival.size, arrival.requestedTime);
        std::cout << "arrival: size " << arrival.size << ", requested time " << arrival.requestedTime << '\n';
    }
}

void printUnparkedCars(const std::vector<pgof::Car>& cars) {
    for (const pgof::Car& car : cars) {
        std::cout << "unparked: size " << car.size << ", requested time " << car.reqtime
                  << ", fee " << car.fee << '\n';
    }
}

void printStepReport(const pgof::PgofApp& garage) {
    const pgof::PgofReport report = garage.getReport();
    std::cout << "time " << report.currentTime << ": parked total " << report.totalParkedVehicles
              << ", fees " << report.totalFees << ", waiting " << report.waitingCars
              << ", currently parked " << report.parkedCars << '\n';
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    try {
        const int totalSpaces = std::stoi(argv[1]);
        const int ticks = parseTicks(argc, argv);
        pgof::PgofApp garage = pgof::createParkingLot(totalSpaces);

        const std::vector<ScheduledArrival> arrivals{
            {1, 3, 10},
            {1, 1, 4},
            {2, 2, 5},
            {3, 1, 2},
            {4, 3, 3},
            {5, 2, 4},
            {7, 1, 3},
            {8, 3, 2},
        };

        std::cout << std::fixed << std::setprecision(2);
        std::cout << garage.getReportText() << "\n\n";

        for (int step = 1; step <= ticks; ++step) {
            std::cout << "step " << step << '\n';
            submitArrivals(garage, arrivals, step);

            const std::vector<pgof::Car> unparkedCars = garage.tick();
            printUnparkedCars(unparkedCars);
            printStepReport(garage);
            std::cout << '\n';
        }

        const pgof::PgofReport finalReport = garage.finish();
        std::cout << "finished run\n";
        std::cout << "final fees: " << finalReport.totalFees << '\n';
        std::cout << garage.getReportText() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Failed to run PGOF demo: " << error.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
