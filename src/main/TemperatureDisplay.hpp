#ifndef TEMPERATUREDISPLAY_HPP
#define TEMPERATUREDISPLAY_HPP

#include <Adafruit_SSD1306.h>

class TemperatureDisplay
{
    public:
        static constexpr int SCREEN_WIDTH = 128; // OLED display width, in pixels
        static constexpr int SCREEN_HEIGHT = 32; // OLED display height, in pixels

        Adafruit_SSD1306 display;

        TemperatureDisplay();
        void setup();
        void displayTemperature(double temperature, double targetTemp, bool isHeating);
};

#endif
