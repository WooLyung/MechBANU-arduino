#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Adafruit_NeoPixel.h>
#include "../util/Pins.hpp"

class Display
{
private:
    Adafruit_NeoPixel matrix = Adafruit_NeoPixel(192, PIN_DISPLAY, NEO_RGB + NEO_KHZ800);
    unsigned long pre = 0;
    bool connected = false;
    int duration = 0;

    void setDefault();

public:
    void setup();
    void update();

    void setConnected(bool);
    void setDuration(int);
    void setBrightness(int);
    void setColor(int, int, int, int);
    void refresh();
};

void Display::setup()
{
    pre = millis();
    matrix.begin();
    matrix.show();
    setDefault();
}

void Display::setConnected(bool flag)
{
    if (!duration && flag != connected)
    {
        connected = flag;
        setDefault();
    }
    else
    {
        connected = flag;
    }
}

void Display::setDuration(int duration)
{
    this->duration = duration * 1000;
}

void Display::setBrightness(int brightness)
{
    matrix.setBrightness(brightness);
}

void Display::setColor(int pixel, int r, int g, int b)
{
    matrix.setPixelColor(pixel, g, r, b);
}

void Display::refresh()
{
    matrix.show();
}

void Display::update()
{
    if (duration)
    {
        duration -= millis() - pre;

        if (duration <= 0)
        {
            duration = 0;
            setDefault();
        }
    }
    pre = millis();
}

void Display::setDefault()
{
    matrix.setBrightness(20);

    if (connected)
    {
        for (int i = 0; i < 192; i++)
            matrix.setPixelColor(i, 255, 0, 0);
        matrix.show();
    }
    else
    {
        for (int i = 0; i < 192; i++)
            matrix.setPixelColor(i, 0, 0, 255);
        matrix.show();
    }
}

#endif