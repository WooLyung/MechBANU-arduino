#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "class/Banu.hpp"

SoftwareSerial bluetooth(12, 13);
Adafruit_NeoPixel matrix(192, 11, NEO_RGB + NEO_KHZ800);

void setup() 
{
    Serial.begin(9600);
    bluetooth.begin(9600);

    matrix.begin();
    matrix.show();
    matrix.setBrightness(20);
}

void loop()
{
    if (bluetooth.available())
    {
        char buffer[100];
        bluetooth.readBytes(buffer, 4);

        Serial.println(Banu().yeah());
        Serial.print(buffer[0]);
        Serial.print(buffer[1] == 0);
        Serial.print(buffer[2] == 0);
        Serial.println(buffer[3] == 9);
    }
}