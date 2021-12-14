#include <Adafruit_NeoPixel.h>
#include "../utils/Pins.hpp"

class Display
{
private:
    Adafruit_NeoPixel matrix = Adafruit_NeoPixel(192, PIN_DISPLAY, NEO_RGB + NEO_KHZ800);

public:
    void setup();
};

void Display::setup()
{
    matrix.begin();
    matrix.show();
    matrix.setBrightness(20);
}