# PGOF Definition Of Done

PGOF is complete when the system supports these top-level use cases:

1. Start the garage and discover the current number of parking spaces.
2. Split the garage capacity across size-1, size-2, and size-3 parking spaces.
3. Accept autonomous vehicles into a waiting line in order of arrival.
4. Track each vehicle's size and requested parking duration.
5. Park vehicles into compatible empty spaces according to the PGOF parking rules.
6. When the next vehicle in line cannot be parked, select the first eligible waiting vehicle that can be parked.
7. Return to arrival-order parking once compatible spaces are available again.
8. Unpark vehicles when their requested parking duration expires.
9. Charge each parked vehicle using `fee = car_size * parking_time`.
10. Maintain the total fees collected over the run.
11. Maintain the total number of vehicles successfully parked.
12. Prefer parking decisions that maximize collected fees over a long-running operating period.

## Base UML

```mermaid
classDiagram
    class pgofApp {
        <<pgofApp>>
        float totalFees
        int capacity (N)
        int N1, N2, N3
        function callGarageCapacityService() -> N1 N2 N3
    }

    class ParkingLotHandler {
        <<handler>>
        List<ParkingSpace> spaces
        function initialize(N1, N2, N3)
        function park() -> dequeueCar()
        function unpark(car)
    }

    class ParkingSpace {
        <<class>>
        int capacity (1,2,3)
        boolean isfull
        int occupancy
        
        pointer List<Car>
        
        function updateOccupancy()
        function checkSpace() -> isfull
        function insert(car)
        function remove(car)
    }

    class TimeHandler {
        <<handler>>
        int time

        function tick() -> updates P-cars timeleft
    }

    class Car {
        <<class>>
        int reqtime
        int remainingtime
        int size (1,2,3)
        int fee
    }

    class CarQueue {
        <<runtimeObject>>
        pointer Queue<Car>
        pointer head
        pointer tail
        boolean Mode

        function dequeueCar(Mode)
        function enqueue(car)
    }

    class FeeHandler {
        <<runtimeLogger>>
        function logFeesToFile()
        function CalculateTotalFeesOnExit()
    }

    class GarageCapacityService {
        <<service>>
        returns capacity value
    }

    pgofApp --> ParkingLotHandler : triggers
    pgofApp --> CarQueue : triggers
    pgofApp --> FeeHandler : triggers
    pgofApp --> TimeHandler : triggers
    pgofApp --> GarageCapacityService : uses
    ParkingLotHandler o-- ParkingSpace : contains
    CarQueue o-- Car : contains
    ParkingSpace --> Car : points to
    TimeHandler o-- Car : updates
```

## Base Sequence

```mermaid
sequenceDiagram
    participant pgofApp as pgofApp
    participant GarageCapacityService as GarageCapacityService service
    participant CarQueue as CarQueue object
    participant ParkingLotHandler as ParkingLotHandler handler class
    participant ParkingSpace as ParkingSpace object
    participant Car as Car object
    participant TimeHandler as TimeHandler handler class
    participant FeeHandler as FeeHandler runtime logger

    Note over pgofApp,CarQueue: setup
    pgofApp->>GarageCapacityService: request capacity
    GarageCapacityService-->>pgofApp: capacity value
    Note over pgofApp: store N1, N2, N3 in pgofApp variables
    pgofApp->>ParkingLotHandler: initialize(N1, N2, N3)
    ParkingLotHandler->>ParkingSpace: create spaces
    
    loop while PGOF is running
        pgofApp->>CarQueue: enqueue(car)
        CarQueue->>Car: contains

        pgofApp->>ParkingLotHandler: park()
        ParkingLotHandler->>CarQueue: dequeueCar(Mode)
        CarQueue-->>ParkingLotHandler: car
        ParkingLotHandler->>ParkingSpace: check space
        ParkingSpace->>Car: points to
        ParkingLotHandler->>FeeHandler: logs fees to local file

        pgofApp->>TimeHandler: tick()
        TimeHandler->>Car: updates P-cars timeleft

        pgofApp->>ParkingLotHandler: unpark(car)
        ParkingLotHandler->>ParkingSpace: release car
    end
```
# Sequence of events of PGOF System
