#include "TemperatureController.hpp"

#include <Arduino.h>

TemperatureController::TemperatureController()
    : 
    display(),
    sensor(TemperatureController::SENSOR_PIN),
    potentiometer(TemperatureController::POTENTIOMETER_PIN)
{
}

void TemperatureController::setup()
{
    this->display.setup();
    this->potentiometer.setup();
}

void TemperatureController::controlTemperature()
{
    double temp = this->sensor.readTempC();
    int roundedTemp = round(temp);
    int targetTemp = this->potentiometer.getTargetTempC();
    
    bool isHeating = this->heaterControl(roundedTemp, targetTemp);
    this->display.displayTemperature(roundedTemp, targetTemp, isHeating);
}

bool TemperatureController::heaterControl(int temp, int targetTemp)
{
    if (temp < targetTemp)
    {
        // Temperature is below target, turn on the heater
        digitalWrite(TemperatureController::RELAY_PIN, HIGH);
        return true;
    }
    else
    {
        // Temperature has reached or exceeded target, turn off the heater
        digitalWrite(TemperatureController::RELAY_PIN, LOW);
        return false;
    }
}
