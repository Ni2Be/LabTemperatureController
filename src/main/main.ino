#include "TemperatureController.hpp"

TemperatureController controller;

void setup() {
  Serial.begin(115200);

  controller.setup();

  delay(1000);
}

void loop() {
  controller.controlTemperature();

  delay(50);
}
