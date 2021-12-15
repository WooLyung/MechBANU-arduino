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
    if (flag != connected)
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
    matrix.setBrightness(10);

    if (connected)
    {
        for (int i = 0; i < 192; i++)
            setColor(i, 0, 255, 0);
        refresh();
    }
    else
    {
        for (int i = 0; i < 192; i++)
            setColor(i, 0, 0, 0);

        setColor(81, 100, 40, 255);
        setColor(85, 20, 200, 255);
        setColor(90, 80, 80, 255);
        setColor(92, 40, 160, 255);
        setColor(96, 120, 0, 255);
        setColor(97, 100, 40, 255);
        setColor(98, 80, 80, 255);
        setColor(99, 60, 120, 255);
        setColor(100, 40, 160, 255);
        setColor(101, 20, 200, 255);
        setColor(102, 0, 240, 255);
        setColor(105, 100, 40, 255);
        setColor(107, 60, 120, 255);
        setColor(109, 20, 200, 255);
        setColor(114, 60, 80, 255);
        setColor(116, 20, 160, 255);

        refresh();
    }
}

#endif