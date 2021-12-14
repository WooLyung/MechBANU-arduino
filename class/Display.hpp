#include <Adafruit_NeoPixel.h>
#include "../utils/Pins.hpp"

class Banu;

class Display
{
private:
    Adafruit_NeoPixel matrix = Adafruit_NeoPixel(192, PIN_DISPLAY, NEO_RGB + NEO_KHZ800);
    Banu* banu;

public:
    Display(Banu*);

    void setup();
};

Display::Display(Banu* banu)
{
    this->banu = banu;
}

void Display::setup()
{
    matrix.begin();
    matrix.show();
    matrix.setBrightness(20);
}