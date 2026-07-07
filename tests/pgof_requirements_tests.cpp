#include "pgof/car.hpp"
#include "pgof/car_queue.hpp"
#include "pgof/fee_handler.hpp"
#include "pgof/parking_lot_handler.hpp"
#include "pgof/parking_space.hpp"
#include "pgof/pgofApp.hpp"
#include "pgof/time_handler.hpp"

#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

namespace {

int failures = 0;

void expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "Requirement failed: " << message << '\n';
        ++failures;
    }
}

pgof::Car makeCar(int size, int requestedTime) {
    pgof::Car car{};
    car.size = size;
    car.reqtime = requestedTime;
    car.remainingtime = requestedTime;
    return car;
}

void test_startup_discovers_and_splits_capacity() {
    pgof::PgofApp app{};
    app.initialize(10);

    expect(app.getN1() == 4, "startup should discover size-1 capacity for N=10");
    expect(app.getN2() == 3, "startup should discover size-2 capacity for N=10");
    expect(app.getN3() == 3, "startup should discover size-3 capacity for N=10");
}

void test_parking_lot_initializes_spaces_from_capacity_split() {
    pgof::ParkingLotHandler lot{2, 3, 4};

    int size1Spaces = 0;
    int size2Spaces = 0;
    int size3Spaces = 0;

    for (const pgof::ParkingSpace& space : lot.spaces) {
        if (space.capacity == 1) {
            ++size1Spaces;
        } else if (space.capacity == 2) {
            ++size2Spaces;
        } else if (space.capacity == 3) {
            ++size3Spaces;
        }
    }

    expect(lot.spaces.size() == 9, "lot should create N1+N2+N3 parking spaces");
    expect(size1Spaces == 2, "lot should create requested size-1 spaces");
    expect(size2Spaces == 3, "lot should create requested size-2 spaces");
    expect(size3Spaces == 4, "lot should create requested size-3 spaces");
}

void test_car_queue_tracks_arrival_order() {
    std::queue<pgof::Car> storage;
    pgof::CarQueue queue{};
    queue.queue = &storage;

    queue.enqueue(makeCar(1, 4));
    queue.enqueue(makeCar(2, 5));

    const pgof::Car first = queue.dequeueCar(false);
    const pgof::Car second = queue.dequeueCar(false);

    expect(first.size == 1, "queue should dequeue the first arriving car first");
    expect(first.reqtime == 4, "queue should preserve requested time for first car");
    expect(second.size == 2, "queue should dequeue the second arriving car second");
    expect(second.reqtime == 5, "queue should preserve requested time for second car");
}

void test_car_tracks_size_and_requested_duration() {
    const pgof::Car car = makeCar(3, 8);

    expect(car.size == 3, "car should track its size");
    expect(car.reqtime == 8, "car should track requested parking duration");
    expect(car.remainingtime == 8, "car should initialize remaining time from requested duration");
}

void test_car_queue_can_select_first_eligible_car_when_head_cannot_park() {
    std::queue<pgof::Car> storage;
    pgof::CarQueue queue{};
    queue.queue = &storage;

    queue.enqueue(makeCar(3, 2));
    queue.enqueue(makeCar(1, 7));

    const pgof::Car selected = queue.dequeueCar(true);

    expect(selected.size == 1, "eligible mode should select the first car that can park");
    expect(selected.reqtime == 7, "eligible mode should preserve the selected car duration");
}

void test_queue_returns_to_arrival_order_after_compatible_space_is_available() {
    std::queue<pgof::Car> storage;
    pgof::CarQueue queue{};
    queue.queue = &storage;

    queue.enqueue(makeCar(3, 2));
    queue.enqueue(makeCar(1, 7));

    (void)queue.dequeueCar(true);
    const pgof::Car selected = queue.dequeueCar(false);

    expect(selected.size == 3, "queue should return to arrival-order parking when compatible space is available");
    expect(selected.reqtime == 2, "arrival-order mode should preserve the original head car duration");
}

void test_parking_space_accepts_only_compatible_cars_and_tracks_occupancy() {
    std::vector<pgof::Car> parkedCars;
    pgof::ParkingSpace space{};
    space.capacity = 2;
    space.cars = &parkedCars;

    space.insert(makeCar(2, 6));

    expect(parkedCars.size() == 1, "compatible car should be inserted into an empty space");
    expect(space.occupancy == 2, "space occupancy should equal parked car size");
    expect(space.checkSpace(), "space should be full after accepting a size-2 car in size-2 space");

    space.insert(makeCar(3, 4));

    expect(parkedCars.size() == 1, "incompatible larger car should not be inserted");
}

void test_unpark_removes_car_from_space() {
    std::vector<pgof::Car> parkedCars;
    pgof::ParkingSpace space{};
    space.capacity = 3;
    space.cars = &parkedCars;

    const pgof::Car car = makeCar(1, 1);
    parkedCars.push_back(car);
    space.occupancy = 1;
    space.isfull = false;

    space.remove(car);

    expect(parkedCars.empty(), "unpark should remove the expired car from its space");
    expect(space.occupancy == 0, "unpark should update space occupancy");
}

void test_time_handler_advances_time() {
    pgof::TimeHandler time{};

    time.tick();

    expect(time.time == 1, "tick should advance system time by one unit");
}

void test_time_expiry_unparks_vehicle() {
    pgof::PgofApp app{};
    app.parkingLot = pgof::ParkingLotHandler(1, 0, 0);
    app.enqueueCar(makeCar(1, 1));

    app.park();
    const std::vector<pgof::Car> expiredCars = app.tick();

    expect(app.timeHandler.time == 1, "app tick should advance TimeHandler");
    expect(expiredCars.size() == 1, "time expiry should unpark vehicles once TimeHandler is connected to parked cars");
    expect(app.parkingLot.spaces.front().occupancy == 0, "expired vehicle should release its parking space");
}

void test_fee_is_car_size_times_requested_parking_time() {
    std::vector<pgof::Car> parkedCars;
    pgof::ParkingSpace space{};
    space.capacity = 3;
    space.cars = &parkedCars;

    space.insert(makeCar(3, 4));

    expect(!parkedCars.empty(), "parking should store the accepted car for fee tracking");
    if (!parkedCars.empty()) {
        expect(parkedCars.front().fee == 12.0F, "fee should be car_size * parking_time");
    }
}

void test_total_fees_start_at_zero() {
    pgof::PgofApp app{};

    expect(app.totalFees == 0.0F, "total fees should start at zero when PGOF starts");
}

void test_running_total_fees_are_maintained() {
    pgof::PgofApp app{};
    app.parkingLot = pgof::ParkingLotHandler(1, 1, 0);

    app.enqueueCar(makeCar(1, 4));
    app.enqueueCar(makeCar(2, 5));

    app.park();
    expect(app.totalFees == 4.0F, "system should expose/update running total fees after first successful park");

    app.park();
    expect(app.totalFees == 14.0F, "system should expose/update running total fees after each successful park");
}

void test_successfully_parked_vehicle_count_is_maintained() {
    pgof::PgofApp app{};
    app.parkingLot = pgof::ParkingLotHandler(2, 0, 0);

    app.enqueueCar(makeCar(1, 4));
    app.enqueueCar(makeCar(1, 5));

    app.park();
    app.park();

    expect(app.totalParkedVehicles == 2, "system should expose/update total number of successfully parked vehicles");
}

void test_long_running_policy_prefers_fee_maximizing_decisions() {
    pgof::PgofApp app{};
    app.parkingLot = pgof::ParkingLotHandler(1, 0, 0);

    app.enqueueCar(makeCar(3, 10));
    app.enqueueCar(makeCar(1, 10));

    const pgof::Car parked = app.park();

    expect(parked.size == 1, "parking policy should select first eligible car when head cannot fit");
    expect(app.totalFees == 10.0F, "parking policy should collect fees from eligible long-running decisions");
}

void test_finish_unparks_all_cars_and_preserves_final_totals() {
    pgof::PgofApp app{};
    app.parkingLot = pgof::ParkingLotHandler(2, 0, 0);

    app.enqueueCar(makeCar(1, 4));
    app.enqueueCar(makeCar(1, 5));
    app.enqueueCar(makeCar(1, 6));

    app.park();
    app.park();

    const pgof::PgofReport finalReport = app.finish();

    expect(finalReport.parkedCars == 0, "finish should unpark every currently parked car");
    expect(finalReport.waitingCars == 0, "finish should clear cars still waiting in line");
    expect(finalReport.totalFees == 9.0F, "finish should preserve collected fees without double charging");
    expect(finalReport.totalParkedVehicles == 2, "finish should preserve successful parked vehicle count");
    expect(app.parkingLot.spaces.front().occupancy == 0, "finish should release occupied spaces");
}

}  // namespace

int main() {
    test_startup_discovers_and_splits_capacity();
    test_parking_lot_initializes_spaces_from_capacity_split();
    test_car_queue_tracks_arrival_order();
    test_car_tracks_size_and_requested_duration();
    test_car_queue_can_select_first_eligible_car_when_head_cannot_park();
    test_queue_returns_to_arrival_order_after_compatible_space_is_available();
    test_parking_space_accepts_only_compatible_cars_and_tracks_occupancy();
    test_unpark_removes_car_from_space();
    test_time_handler_advances_time();
    test_time_expiry_unparks_vehicle();
    test_fee_is_car_size_times_requested_parking_time();
    test_total_fees_start_at_zero();
    test_running_total_fees_are_maintained();
    test_successfully_parked_vehicle_count_is_maintained();
    test_long_running_policy_prefers_fee_maximizing_decisions();
    test_finish_unparks_all_cars_and_preserves_final_totals();

    if (failures != 0) {
        std::cerr << failures << " requirement checks failed.\n";
        return EXIT_FAILURE;
    }

    std::cout << "All PGOF requirement tests passed.\n";
    return EXIT_SUCCESS;
}
