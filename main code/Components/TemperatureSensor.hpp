
#pragma once
#ifndef TEMPERATURE_SENSO_HPP
#define TEMPERATURE_SENSO_HPP

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

class TemperatureSensor : public Loopable {
   private:
    Pin pin;
    unsigned long milisec = 2000;
    Debounce* debounce = new Debounce(&milisec);

   public:
    TemperatureSensor(Pin analogPin) : Loopable() {
        //
        this->pin = analogPin;
        debounce->start();
    }
    void loop() {
        if (appEnv->funcs->isSensorsOn() && debounce->isValidOnce()) {
            int temperature = analogRead(pin);
            float celcius = (float)temperature / 1023;
            celcius = celcius * 5;
            celcius = celcius - 0.5;
            celcius = celcius * 100;

            appEnv->data->temperature = celcius;
            appEnv->apps->infoApp->updateTemperature(true);
            // Serial.println(celcius);
            debounce->start();
        }
    }
};

#endif /* TEMPERATURE_SENSO_HPP */