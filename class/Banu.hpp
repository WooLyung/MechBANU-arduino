#include "BluetoothSensor.hpp"
#include "Display.hpp"
#include "MoodLamp.hpp"

class Banu
{
private:
    BluetoothSensor* bluetoothSensor;
    Display* display;
    MoodLamp* moodLamp;

public:
    Banu();
    ~Banu();

    void setup();
    void loop();
};

Banu::Banu()
{
    display = new Display();
    moodLamp = new MoodLamp();
    bluetoothSensor = new BluetoothSensor(display);
}

Banu::~Banu()
{
    delete bluetoothSensor;
    delete display;
    delete moodLamp;
}

void Banu::setup()
{
    Serial.begin(9600);
    display->setup();
    moodLamp->setup();
    bluetoothSensor->setup();
}

void Banu::loop()
{
    bluetoothSensor->read();
}