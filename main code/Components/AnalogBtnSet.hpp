
#pragma once
#ifndef ANALOG_BTN_SET_HPP
#define ANALOG_BTN_SET_HPP

#include "../AppEnv.hpp"
#include "../Modules/Assert.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"
#include "../NoErrors.hpp"
#include "./AnalogButton.hpp"

// note: all analog buttons connected to the same pin must also have the same
// resistorOhms
class AnalogBtnSet : public Loopable {
   private:
    Pin pin;
    static const int btnCount = 3;
    int startingVolts;
    int resistorKOhms;
    bool ready = true;
    DebounceTime debounceTime = 300;
    Debounce* debounce = new Debounce(&debounceTime);
    AnalogButton* btns[btnCount];  // WARNING: button count has been hardcoded

    int getMaxVoltage(const int btnNum);
    int getMinVoltage(const int btnNum);

    void triggerButton(AnalogButton* btn);

   public:
    AnalogBtnSet(AnalogButton* btns[], int btnCount, Pin analogPin,
                 const int startingVolts, const int resistorKOhms);

    void loop();
};

// private:
int AnalogBtnSet::getMaxVoltage(const int btnNum) {
    int resistorsBfrBtn = btnNum + 1;
    return (startingVolts * 100) - (resistorsBfrBtn * resistorKOhms * 100) +
           resistorKOhms * 100;
}

int AnalogBtnSet::getMinVoltage(const int btnNum) {
    return getMaxVoltage(btnNum) - 100;
}

void AnalogBtnSet::triggerButton(AnalogButton* btn) {
    if (ready) {
        btn->onButtonPressed();
        ready = false;
    }
}

// public:
AnalogBtnSet::AnalogBtnSet(AnalogButton* btns[], int btnCount, Pin analogPin,
                           const int startingVolts, const int resistorKOhms)
    : Loopable() {
    assert_int(this->btnCount == btnCount,
               "button count must be same as hard code", btnCount);
    this->pin = analogPin;
    this->startingVolts = startingVolts;
    this->resistorKOhms = resistorKOhms;
    for (int i = 0; i < btnCount; i++) {
        this->btns[i] = btns[i];
    }
}

void AnalogBtnSet::loop() {
    int voltageInput = analogRead(this->pin);

    // no button pressed
    if (voltageInput < getMaxVoltage(btnCount)) {
        ready = true;
        return;
    }
    // btn that isn't 1st btn is pressed
    for (int i = this->btnCount - 1; i >= 1; i--) {
        if (voltageInput < getMaxVoltage(i)) {
            triggerButton(this->btns[i]);
            return;
        }
    }

    triggerButton(this->btns[0]);
}

#endif /* ANALOG_BTN_SET_HPP */
