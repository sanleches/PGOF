/**
 * @file car_queue.cpp
 * @brief Source skeleton for CarQueue from design.md.
 *
 * This file reserves the queue behavior described by the UML and sequence
 * diagram. The actual enqueue and dequeue algorithms are intentionally not
 * implemented yet.
 */

#include "pgof/car_queue.hpp"

namespace pgof {

/**
 * @brief Purpose: dequeue a car according to the provided queue mode.
 * @param Mode Boolean mode value from the design.md UML.
 * @return Car object selected from the queue.
 *
 * TODO: Implement the queue selection behavior after Mode is fully defined.
 */
Car CarQueue::dequeueCar(bool mode) {
    if (queue == nullptr || queue->empty()) {
        return {};
    }

    if (mode == false) {
        // Mode 0: Arrival-order (FIFO) - return first car in queue
        Car car = queue->front();
        queue->pop();
        return car;
    } else {
        // Mode 1: Find first eligible car (for fee maximization strategy)
        // TODO: Implement logic to find compatible car when next can't park
        Car car = queue->front();
        queue->pop();
        return car;
    }
}

/**
 * @brief Purpose: enqueue a car into the waiting line.
 * @param car Car object that should enter the queue.
 * @return Nothing.
 *
 * TODO: Implement enqueue behavior and head/tail updates.
 */
void CarQueue::enqueue(Car car) {
    if (queue != nullptr) {
        queue->push(car);
    }
}

}  // namespace pgof
