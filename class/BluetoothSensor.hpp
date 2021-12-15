#include <SoftwareSerial.h>
#include <DHT.h>
#include "Display.hpp"
#include "../util/Pins.hpp"

class BluetoothSensor
{
private:
    SoftwareSerial bluetooth = SoftwareSerial(PIN_BLUETOOTH_TXD, PIN_BLUETOOTH_RXD);
    DHT temp = DHT(PIN_TEMP, DHT22);
    Display* display;

public:
    BluetoothSensor(Display*);

    void setup();
    void read();

private:
    float pulse2ugm3(unsigned long);
    void op_1();
};

BluetoothSensor::BluetoothSensor(Display* display)
{
    this->display = display;
}

void BluetoothSensor::setup()
{
    pinMode(PIN_TOUCH1, INPUT);
    pinMode(PIN_TOUCH2, INPUT);
    pinMode(PIN_TOUCH3, INPUT);
    pinMode(PIN_TOUCH4, INPUT);
    pinMode(PIN_TEMP, INPUT);
    pinMode(PIN_DUST, INPUT);

    bluetooth.begin(9600);
}

float BluetoothSensor::pulse2ugm3(unsigned long pulse)
{
    float value = (pulse - 540) / 14.0f;
    if (value > 300.0f)
        value = 0.0f;
    return value;
}

void BluetoothSensor::read()
{
    if (bluetooth.available())
    {
        byte buffer[4];
        bluetooth.readBytes(buffer, 4);

        char H = buffer[0];
        int op = buffer[1];
        size_t len = buffer[2] * 16 + buffer[3];

        if (op == 0x01)
            op_1();
    }
}

void BluetoothSensor::op_1()
{
    byte buffer[578];
    bluetooth.readBytes(buffer, 578);

    int duration = buffer[0];
    int brightness = buffer[1];

    display->setBrightness(brightness);
    for (int i = 0; i < 192; i++)
    {
        display->setColor(i, buffer[i * 3 + 2], buffer[i * 3 + 3], buffer[i * 3 + 4]);
    }
    display->refresh();
}