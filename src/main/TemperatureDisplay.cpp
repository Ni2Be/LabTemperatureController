#include "TemperatureDisplay.hpp"

#include <Wire.h>
#include <Adafruit_GFX.h>

TemperatureDisplay::TemperatureDisplay()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
}

void TemperatureDisplay::setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C Address (0x3D for 128x64)
    Serial.println(F("SSD1306 allocation failed"));
    while(true);
  }

  delay(2000);
  
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  
  display.println("Starting..");
  display.display(); 
}

void TemperatureDisplay::displayTemperature(double temperature, double targetTemp) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(String(temperature) + "C / " + String(targetTemp) + "C");
  display.display(); 
}