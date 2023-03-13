
#pragma once
#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "../AppEnv.hpp"
#include "../Components/AirFreshener.hpp"
#include "./Debounce.hpp"
#include "./Loopable.hpp"

class StateManager : public Loopable {
   public:
    DebounceTime time = 1;
    Debounce *motionTimer = new Debounce(&time),
             *distanceTimer = new Debounce(&time);
    StateManager() : Loopable() {}

    void loop() {
        if (appEnv->data->distance < 10) {
            motionTimer->start();
        }
        if (motionTimer->isValidOnce() &&
            appEnv->data->machineState() !=
                MachineState::triggeredSprayImminent) {
            appEnv->miscComponents->airFreshener->activate();
        }
    }
};

#endif /* STATE_MANAGER_HPP */