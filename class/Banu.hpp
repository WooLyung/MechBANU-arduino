#include "Bluetooth.hpp"
#include "Display.hpp"
#include "MoodLamp.hpp"
#include "Sensor.hpp"

class Banu
{
private:
    Bluetooth bluetooth;
    Display display;
    MoodLamp moodLmap;
    Sensor sensor;

public:
    void setup();
    void loop();
};

void Banu::setup()
{
    Serial.begin(9600);
    bluetooth.setup();
}

void Banu::loop()
{
    bluetooth.read();
}