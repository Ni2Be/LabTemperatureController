#ifndef TEMPERATURESENSOR_HPP
#define TEMPERATURESENSOR_HPP

class TemperatureSensor
{
    public:
        TemperatureSensor(int pin);
        double readTempC();
        int pin;
    private:
        double convertRawToTemperature(int raw, bool celsius);
};

#endif
