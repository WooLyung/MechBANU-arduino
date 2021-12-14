#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include <SoftwareSerial.h>
#include "Display.hpp"
#include "../utils/Pins.hpp"

class Bluetooth
{
private:
    SoftwareSerial bluetooth = SoftwareSerial(PIN_BLUETOOTH_TXD, PIN_BLUETOOTH_RXD);
    Display* display;

    byte buffer[1024];

public:
    Bluetooth(Display*);

    void setup();
    void read();

private:
    void op_0();
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
        bluetooth.readBytes(buffer, 4);

        char H = buffer[0];
        int op = buffer[1];
        size_t len = buffer[2] * 16 + buffer[3];


        if (op == 0x01) // Display Update Packet
            op_0();
    }
}

void Bluetooth::op_0()
{
    bluetooth.readBytes(buffer, 2);

    int duration = buffer[0];
    int brightness = buffer[1];

    display->setBrightness(brightness);
    for (int i = 0; i < 192; i++)
    {
        bluetooth.readBytes(buffer, 3);

        Serial.write(buffer[0]);
        Serial.write(buffer[1]);
        Serial.write(buffer[2]);

        display->setColor(i, buffer[0], buffer[1], buffer[2]);
    }
    display->refresh();
}

#endif