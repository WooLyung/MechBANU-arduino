#include "Bluetooth.hpp"
#include "Display.hpp"
#include "MoodLamp.hpp"
#include "Sensor.hpp"

class Banu
{
private:
    Bluetooth* bluetooth;
    Display* display;
    MoodLamp* moodLmap;
    Sensor* sensor;

public:
    Banu();
    ~Banu();

    void setup();
    void loop();
};

Banu::Banu()
{
    bluetooth = new Bluetooth(this);
    display = new Display(this);
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
}

void Banu::loop()
{
    bluetooth->read();
}