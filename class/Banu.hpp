#include "BluetoothSensor.hpp"
#include "Display.hpp"
#include "MoodLamp.hpp"

class Banu
{
private:
    BluetoothSensor* bluetoothSensor;
    Display* display;
    MoodLamp* moodLmap;

public:
    Banu();
    ~Banu();

    void setup();
    void loop();
};

Banu::Banu()
{
    display = new Display();
    bluetoothSensor = new BluetoothSensor(display);
}

Banu::~Banu()
{
    delete bluetoothSensor;
    delete display;
}

void Banu::setup()
{
    Serial.begin(9600);
    bluetoothSensor->setup();
    display->setup();
}

void Banu::loop()
{
    bluetoothSensor->read();
}