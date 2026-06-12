/**
 * @file time_handler.hpp
 * @brief Declares the TimeHandler class outlined in design.md.
 *
 * TimeHandler is the handler responsible for ticking time and updating parked
 * cars' remaining time values. The update behavior is not implemented yet.
 */

#pragma once

namespace pgof {

/**
 * @brief Handler class for time progression.
 */
class TimeHandler {
public:
    int time{};

    /**
     * @brief Purpose: advance time and update parked cars' remaining time.
     * @param None.
     * @return Nothing.
     *
     * TODO: Define how parked cars are located and updated on each tick.
     */
    void tick();
};

}  // namespace pgof
