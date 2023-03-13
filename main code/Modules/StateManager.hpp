
#pragma once
#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "./Debounce.hpp"
#include "./Loopable.hpp"

class StateManager {
   public:
    DebounceTime time = 1;
    Debounce *motionTimer = new Debounce(&time),
             *distanceTimer = new Debounce(&time);
    StateManager() {}

    void loop() {
        // if(hasMotion)
    }
};

#endif /* STATE_MANAGER_HPP */