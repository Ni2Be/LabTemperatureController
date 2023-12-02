#include "TemperatureSensor.hpp"

#include <math.h>
#include <Arduino.h>

TemperatureSensor::TemperatureSensor(int pin)
    : pin(pin)
{
}

double TemperatureSensor::convertRawToTemperature(int raw, bool celsius)
{
    double temperatureInF;

    temperatureInF = log(10000.0 * ((1024.0 / raw - 1)));
    temperatureInF = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperatureInF * temperatureInF)) * temperatureInF);
    temperatureInF = temperatureInF - 273.15;

    if (celsius == false)
        temperatureInF = (temperatureInF * 9.0) / 5.0 + 32.0;

    return temperatureInF;
}

double TemperatureSensor::readTempC()
{
    int rawTemperature = analogRead(this->pin);
    double temperatureInC = convertRawToTemperature(rawTemperature, true);

    Serial.print("Temperature: ");
    Serial.print(temperatureInC);
    Serial.println("° C");

    return temperatureInC;
}
