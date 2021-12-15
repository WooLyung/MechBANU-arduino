#ifndef MOODLAMP_HPP
#define MOODLAMP_HPP

#include <Adafruit_NeoPixel.h>
#include "../util/Pins.hpp"

static Adafruit_NeoPixel lamp = Adafruit_NeoPixel(30, PIN_MOODLAMP, NEO_RGB + NEO_KHZ800);

class MoodLamp
{
public:
    void setup();
    void setBrightness(int);
    void setColor(int, int, int, int);
    void refresh();
};

void MoodLamp::setup()
{
    lamp.begin();
    lamp.show();
}

void MoodLamp::setBrightness(int brightness)
{
    lamp.setBrightness(brightness);
}

void MoodLamp::setColor(int pixel, int r, int g, int b)
{
    lamp.setPixelColor(pixel, g, r, b);
}

void MoodLamp::refresh()
{
    lamp.show();
}

#endif