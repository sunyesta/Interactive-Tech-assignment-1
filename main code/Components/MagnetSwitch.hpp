
// #pragma once
// #ifndef MAGNET_SWITCH_HPP
// #define MAGNET_SWITCH_HPP

// #include "../AppEnv.hpp"
// #include "../Modules/Loopable.hpp"

// class MagnetSwitch : public Loopable {
//    private:
//     Pin inputPin;
//     DebounceTime time = 1000;
//     Debounce *deb = new Debounce(&time);

//    public:
//     MagnetSwitch(Pin inputPin);

//     void loop();
// };

// MagnetSwitch::MagnetSwitch(Pin inputPin) : Loopable() {
//     // Serial.println("created magnet switch!");
//     this->inputPin = inputPin;
//     // pinMode(inputPin, INPUT_PULLUP);
//     deb->start();
// }

// void MagnetSwitch::loop() {
//     if (deb->isValidOnce()) {
//         Serial.println("created magnet switch!");
//         deb->start();
//     }
//     // Serial.println("created magnet switch!");
//     // int buttonState = digitalRead(inputPin);
//     // if (buttonState == HIGH) {
//     // } else if (buttonState == LOW) {
//     //     // Serial.println("funnn!");
//     // }
// }

// #endif /* MAGNET_SWITCH_HPP */