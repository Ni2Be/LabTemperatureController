#ifndef TEMPERATUREPOTENTIOMETER_HPP
#define TEMPERATUREPOTENTIOMETER_HPP

class TemperaturePotentiometer
{
    public:
        TemperaturePotentiometer(int pin);
        void setup();
        int getTargetTempC();
        int pin;
    private:
        int lastStableValue = 0; // Stores the last stable value
        int deadzone = 2;
};

#endif
