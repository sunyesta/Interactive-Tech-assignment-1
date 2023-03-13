#include "Loopable.hpp"

#include "LoopManager.hpp"

Loopable::Loopable() { index = loopManager->connect(this); }

void Loopable::loop() { Serial.println("default loop function"); }