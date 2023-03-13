#include "MotionSensor.hpp"

#include "../AppEnv.hpp"

// TODO: fix data leak!
// static void MotionSensor_toggleMotion() {
//     appEnv->data->hasMotion = (appEnv->data->hasMotion) ? false : true;
//     if (appEnv->data->activeApp == appEnv->apps->infoApp) {
//         appEnv->apps->infoApp->updateHasMotion(true);
//     }
// }

MotionSensor::MotionSensor(Pin pin) {
    // this->pin = pin;
    // pinMode(pin, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(pin), MotionSensor_toggleMotion,
    //                 CHANGE);
}

void MotionSensor::updateMotion() {
    int motionData = digitalRead(pin);
    if (motionData == 1) {
        appEnv->data->hasMotion = true;
    } else {
        appEnv->data->hasMotion = false;
    }
    if (appEnv->data->activeApp == appEnv->apps->infoApp) {
        appEnv->apps->infoApp->updateHasMotion(true);
    }
}