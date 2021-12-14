#include <SoftwareSerial.h>
#include "Display.hpp"
#include "../util/Pins.hpp"

class Bluetooth
{
private:
    SoftwareSerial bluetooth = SoftwareSerial(PIN_BLUETOOTH_TXD, PIN_BLUETOOTH_RXD);
    Display* display;

public:
    Bluetooth(Display*);

    void setup();
    void read();

private:
    void op_1();
};

Bluetooth::Bluetooth(Display* display)
{
    this->display = display;
}

void Bluetooth::setup()
{
    bluetooth.begin(9600);
}

void Bluetooth::read()
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

void Bluetooth::op_1()
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