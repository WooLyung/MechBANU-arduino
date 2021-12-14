#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Adafruit_NeoPixel.h>
#include "../utils/Pins.hpp"

class Display
{
private:
    Adafruit_NeoPixel matrix = Adafruit_NeoPixel(192, PIN_DISPLAY, NEO_RGB + NEO_KHZ800);

public:
    void setup();
    void setBrightness(int);
    void setColor(int, int, int, int);
    void refresh();
};

void Display::setup()
{
    matrix.begin();
    matrix.show();
}

void Display::setBrightness(int brightness)
{
    matrix.setBrightness(brightness);
}

void Display::setColor(int pixel, int r, int g, int b)
{
    matrix.setPixelColor(pixel, r, g, b);
}

void Display::refresh()
{
    matrix.show();
}

#endif