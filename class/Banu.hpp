#ifndef BANU_HPP
#define BANU_HPP

#include "Bluetooth.hpp"
#include "Display.hpp"
#include "MoodLamp.hpp"
#include "Sensor.hpp"

class Banu
{
public:
    Bluetooth* bluetooth;
    Display* display;
    MoodLamp* moodLmap;
    Sensor* sensor;

    Banu();
    ~Banu();

    void setup();
    void loop();
};

Banu::Banu()
{
    display = new Display();
    bluetooth = new Bluetooth(display);
}

Banu::~Banu()
{
    delete bluetooth;
    delete display;
}

void Banu::setup()
{
    Serial.begin(9600);
    bluetooth->setup();
    display->setup();
}

void Banu::loop()
{
    bluetooth->read();
}

#endif