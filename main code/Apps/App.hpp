
#pragma once
#ifndef APP_HPP
#define APP_HPP

#include "../AppEnv.hpp"
#include "../Components/AnalogButton.hpp"
#include "../Components/Lcd.hpp"
#include "../NoErrors.hpp"

class App {
   protected:
    char texts[2][17];
    void fireUpdate();

   public:
    App();

    virtual void activate();
    virtual void deactivate();
    virtual char* toString();
    virtual void onButtonPressed(AnalogButton* btn);
};
// protected
void App::fireUpdate() { appEnv->lcd->update(this, texts); }

// public
App::App() {
    sprintf(texts[0], "sixteen chars==1");
    sprintf(texts[1], "sixteen chars==2");
}

void App::onButtonPressed(AnalogButton* btn) {
    Serial.println("button pressed (from App parent class)");
}

void App::activate() {
    Serial.println("WARNING: parent");
    fireUpdate();
}

void App::deactivate() {}

char* App::toString() { return "Default app"; }

#endif /* APP_HPP */