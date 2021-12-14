#include "class/Banu.hpp"

Banu banu;

void setup()
{
    banu.setup();
}

void loop()
{
    banu.display->setColor(0, 255, 255, 0);
    banu.display->refresh();

    // banu.loop();
}