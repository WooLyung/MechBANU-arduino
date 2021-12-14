#include <SoftwareSerial.h>
#include "../utils/Pins.hpp"

class Bluetooth
{
private:
    SoftwareSerial bluetooth = SoftwareSerial(PIN_BLUETOOTH_TXD, PIN_BLUETOOTH_RXD);

public:
    void setup();
    void read();
};

void Bluetooth::setup()
{
    bluetooth.begin(9600);
}

void Bluetooth::read()
{
    if (bluetooth.available())
    {
        byte buffer[1024];
        bluetooth.readBytes(buffer, 4);
        Serial.print(buffer[0]);
        Serial.print(buffer[1]);
        Serial.print(buffer[2]);
        Serial.println(buffer[3]);
    }
}