#include "TemperaturePotentiometer.hpp"

#include <Arduino.h>

TemperaturePotentiometer::TemperaturePotentiometer(int pin)
    : pin(pin)
{
}

void TemperaturePotentiometer::setup()
{
    pinMode(this->pin, INPUT);
}

int TemperaturePotentiometer::getTargetTempC()
{
    int sensorValue = analogRead(this->pin);
    int mappedValue = map(sensorValue, 0, 1023, 0, 400);

    // Update the last stable value if the change is outside the deadzone
    if (abs(mappedValue - this->lastStableValue) > this->deadzone) {
        this->lastStableValue = mappedValue;
    }

    return this->lastStableValue;
}