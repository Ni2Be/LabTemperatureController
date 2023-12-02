#ifndef TEMPERATURECONTROLLER_HPP
#define TEMPERATURECONTROLLER_HPP
#include "TemperatureDisplay.hpp"
#include "TemperatureSensor.hpp"
#include "TemperaturePotentiometer.hpp"

class TemperatureController
{
    public:
        TemperatureController();
        void setup();
        void controlTemperature();
        
        static constexpr int RELAY_PIN = 2;
        static constexpr int SENSOR_PIN = A6;
        static constexpr int POTENTIOMETER_PIN = A1;

    private:
        TemperatureDisplay display;
        TemperatureSensor sensor;
        TemperaturePotentiometer potentiometer;

        void heaterControl(int temp, int targetTemp);
};

#endif
