#include "./AnalogButton.hpp"

#include "../AppEnv.hpp"
#include "../Apps/App.hpp"

void AnalogButton::onButtonPressed() {
    // Serial.println("button pressed (from button)");
    if (appEnv->data->activeApp) {
        appEnv->data->activeApp->onButtonPressed(this);
    }
}