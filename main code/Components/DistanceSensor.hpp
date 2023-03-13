
#pragma once
#ifndef DISTANCE_SENSOR_HPP
#define DISTANCE_SENSOR_HPP

#include "../AppEnv.hpp"
#include "../Apps/InfoApp.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

class DistanceSensor : Loopable {
   private:
    int distance_cm = -1;
    Pin echoPin, trigPin;
    unsigned long secs2 = 2, secs10 = 10, debounceTime = 1000;
    Debounce *wait2 = new Debounce(&secs2), *wait10 = new Debounce(&secs10),
             *debounce = new Debounce(&debounceTime);
    bool looped = true;

   public:
    DistanceSensor(Pin echoPin, Pin trigPin) {
        this->echoPin = echoPin;
        this->trigPin = trigPin;
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);

        debounce->start();
    }

    void loop() {
        // TODO make a replacment for loopable that updates all sensors every 2
        // secs
        if (appEnv->funcs->isSensorsOn()) {  // TODO make sure to handle
                                             // currently running debounces

            // TODO add debounce with isValid not isValidOnce
            if (debounce->isValidOnce()) {
                digitalWrite(trigPin, LOW);
                wait2->start();
            }

            if (wait2->isValidOnce()) {
                digitalWrite(trigPin, HIGH);
                wait10->start();
            }
            if (wait10->isValidOnce()) {
                digitalWrite(trigPin, LOW);
                long duration = pulseIn(echoPin, HIGH);
                distance_cm = duration * 0.034 / 2;
                appEnv->data->distance = distance_cm;
                appEnv->apps->infoApp->updateDistance(true);
                debounce->start();
            }
        }

        // SLOW WAY
        //  digitalWrite(trigPin, LOW);
        //  delayMicroseconds(2);
        //  digitalWrite(trigPin, HIGH);
        //  delayMicroseconds(10);
        //  digitalWrite(trigPin, LOW);

        // long duration = pulseIn(echoPin, HIGH);
        // distance_cm = duration * 0.034 / 2;
        // appEnv->data->distance = distance_cm;
        // Serial.println(distance_cm);
        // appEnv->apps->infoApp->updateDistance(true);
        // END SLOW WAY
    }
};

#endif /* DISTANCE_SENSOR_HPP */