
#pragma once
#ifndef MOTION_SENSOR_HPP
#define MOTION_SENSOR_HPP

#include "../AppEnv.hpp"
#include "../Apps/InfoApp.hpp"
#include "../Modules/Loopable.hpp"

class MotionSensor : public Loopable {
   private:
   public:
    Pin pin;
    MotionSensor(Pin pin);

    void loop() {
        // if (appEnv->funcs->isSensorsOn()) {
        //     updateMotion();
        // }
    }

    void updateMotion();
};

#endif /* MOTION_SENSOR_HPP */