/**
 * @file car_queue.hpp
 * @brief Declares the CarQueue runtime object outlined in design.md.
 *
 * CarQueue points to the waiting line structure shown in the base UML. It exposes
 * enqueue and dequeue functions, but leaves the mode behavior and queue logic
 * unimplemented until the design is expanded.
 */

#pragma once

#include <queue>

#include "pgof/car.hpp"

namespace pgof {

/**
 * @brief Runtime object that contains waiting Car objects.
 */
class CarQueue {
public:
    std::queue<Car>* queue{};
    Car* head{};
    Car* tail{};
    bool Mode{};

    /**
     * @brief Purpose: dequeue a car according to the provided queue mode.
     * @param Mode Boolean mode value from the design.md UML.
     * @return Car object selected from the queue.
     *
     * TODO: Define mode meanings and dequeue behavior before implementing.
     */
    Car dequeueCar(bool Mode);

    /**
     * @brief Dequeue the first car that can fit a space up to maxSize.
     */
    Car dequeueFirstEligible(int maxSize);

    /**
     * @brief Purpose: enqueue a car into the waiting line.
     * @param car Car object that should enter the queue.
     * @return Nothing.
     *
     * TODO: Define queue ownership and pointer lifetime before implementing.
     */
    void enqueue(Car car);
};

}  // namespace pgof
