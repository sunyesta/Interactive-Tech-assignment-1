
#pragma once
#ifndef RGB_LED_HPP
#define RGB_LED_HPP

#include "../Modules/Debounce.hpp"
#include "../Packages/ColorUtils.hpp"

class RGBLed : public Loopable {
   private:
    Pin rPin;
    Pin gPin;
    Pin bPin;
    int r, g, b;
    DebounceTime time = 1;
    Debounce *debounce1 = new Debounce(&time);

   public:
    RGBLed(Pin PinPWM_red, Pin PinPWM_green, Pin PinPWM_blue) {
        this->rPin = PinPWM_red;
        this->gPin = PinPWM_green;
        this->bPin = PinPWM_blue;

        pinMode(rPin, OUTPUT);
        pinMode(gPin, OUTPUT);
        pinMode(bPin, OUTPUT);

        debounce1->start();
    }

    void setColor(RGB color);
    void setColor(int r, int g, int b);
    // need to be put in loop

    void rainbow() {
        static int hue;
        if (debounce1->isValidOnce()) {
            if (hue < 255) {
                // Serial.println("updating color");
                hue++;
                setColor(HSLToRGB(HSL(hue, 1, .5)));

            } else if (hue >= 255) {
                hue = 0;
            }
            debounce1->start();
        }
    }

    void setColorToState() {
        switch (appEnv->data->machineState()) {
            case MachineState::menuInUse:
                setColor(0, 0, 255);  // dark blue
                break;
            case MachineState::notInUse:
                setColor(255, 255, 255);  // white
                break;
            case MachineState::triggeredSprayImminent:
                setColor(255, 0, 0);  // red
                break;
            case MachineState::useCleaning:
                setColor(255, 255, 0);  // yellow
                break;
            case MachineState::useNum1:
                setColor(0, 255, 0);  // green
                break;
            case MachineState::useNum2:
                setColor(255, 0, 255);  // purple
                break;
            case MachineState::useUnknown:
                setColor(255, 115, 0);  // cyan
                break;

            default:
                setColor(0, 0, 0);  // off
                break;
        }
    }
    void loop() {
        // rainbow();
        // char buff[50];
        // sprintf(buff, "rgb = %d, %d, %d", r, g, b);
        // Serial.println(buff);
    }
};

void RGBLed::setColor(RGB color) {
    analogWrite(rPin, color.R);
    analogWrite(gPin, color.G);
    analogWrite(bPin, color.B);
}

void RGBLed::setColor(int r, int g, int b) {
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);

    this->r = r;
    this->g = g;
    this->b = b;
}

#endif /* RGB_LED_HPP */