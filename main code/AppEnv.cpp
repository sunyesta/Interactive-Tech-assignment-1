#include "AppEnv.hpp"

#include <EEPROM.h>

#include "./Apps/App.hpp"
#include "./Apps/ForceSprayApp.hpp"
#include "./Apps/InfoApp.hpp"
#include "./Apps/MainMenuApp.hpp"
#include "./Apps/ResetSpraysApp.hpp"
#include "./Apps/SprayConfigApp.hpp"
#include "./Components/AirFreshener.hpp"
#include "./Components/AnalogButton.hpp"
#include "./Components/DistanceSensor.hpp"
#include "./Components/Lcd.hpp"
#include "./Components/MagnetSwitch.hpp"
#include "./Components/MotionSensor.hpp"
#include "./Components/RGBLed.hpp"
#include "./Components/TemperatureSensor.hpp"

#define EEPROM_DEFAULT 0

// We use 5000 because it is impossible for spraysRemaining to = 5000
#define EEPROM_OFFSET 5000

// LCD display
// const Pin LCD_RS = 11, LCD_E = 12, LCD_DB4 = 4, LCD_DB5 = A5, LCD_DB6 = 13,
//   LCD_DB7 = 7;

// NEW LCD
const Pin LCD_RS = 2, LCD_E = 4, LCD_DB4 = 7, LCD_DB5 = 8, LCD_DB6 = 12,
          LCD_DB7 = 13;

const int lcdPins[]{LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7};

const int spraysRemainingEEPROM = 0;

AppEnv::Data::Data() {
    activeApp = NULL;
    defaultApp = NULL;
    setMachineState(MachineState::notInUse);
    hasMotion = false;
    distance = -1;

    // spraysRemaining from EEPROM
    spraysRemaining = EEPROM.get(spraysRemainingEEPROM, spraysRemaining);
    if (spraysRemaining == EEPROM_DEFAULT) {
        spraysRemaining = appEnv->config->defaultSprayCount;
        EEPROM.put(spraysRemainingEEPROM, spraysRemaining + EEPROM_OFFSET);
    } else {
        spraysRemaining -= EEPROM_OFFSET;
    }

    temperature = -1;
    sprayDelay = 1000;
}
MachineState AppEnv::Data::machineState() { return _machineState; }

void AppEnv::Data::setMachineState(MachineState machineState) {
    this->_machineState = machineState;
    appEnv->miscComponents->rgbLed->setColorToState();
}

AppEnv ::Apps::Apps() {
    this->infoApp = new InfoApp();
    this->mainMenuApp = new MainMenuApp();
    this->sprayConfigApp = new SprayConfigApp();
    this->forceSprayApp = new ForceSprayApp();
    this->resetSpraysApp = new ResetSpraysApp();
}

AppEnv ::Btns::Btns() {
    this->selectButton = new AnalogButton();
    this->nextButton = new AnalogButton();
}

AppEnv ::MiscComponents::MiscComponents() {
    this->airFreshener = new AirFreshener(11);
    this->temperatureSensor = new TemperatureSensor(A2);
    this->distanceSensor = new DistanceSensor(9, 10);
    this->motionSensor = new MotionSensor(A1);
    this->rgbLed = new RGBLed(3, 6, 5);
    // this->magnetSwitch = new MagnetSwitch(A2);  // put the pin back in
    // place
}

AppEnv ::Funcs::Funcs() {}

void AppEnv ::Funcs::openSelectionMenu() {
    appEnv->lcd->activateApp(appEnv->apps->mainMenuApp);
}

void AppEnv ::Funcs::openDefaultApp() {
    appEnv->lcd->activateApp(appEnv->data->defaultApp);
}

bool AppEnv ::Funcs::isSensorsOn() {
    return appEnv->data->machineState() == MachineState::notInUse ||
           appEnv->data->machineState() == MachineState::useUnknown;
    // return true;
}

void AppEnv::Funcs::setMotion(bool hasMotion) {
    appEnv->data->hasMotion = hasMotion;
}

void AppEnv::Funcs::setSpraysRemaining(int spraysRemaining) {
    appEnv->data->spraysRemaining = spraysRemaining;
    EEPROM.put(spraysRemainingEEPROM, spraysRemaining + EEPROM_OFFSET);
}

AppEnv::AppEnv() {}

void AppEnv ::setup() {
    this->lcd = new Lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
    this->config = new Config();
    this->data = new Data();
    this->apps = new Apps();
    this->btns = new Btns();
    this->miscComponents = new MiscComponents();
    this->funcs = new Funcs();

    this->data->defaultApp = this->apps->infoApp;
}
