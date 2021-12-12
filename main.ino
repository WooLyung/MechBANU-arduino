#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial bluetooth(12, 13);
Adafruit_NeoPixel matrix(192, 11, NEO_RGB + NEO_KHZ800);

void setup() 
{
    Serial.begin(9600);
    bluetooth.begin(9600);

    matrix.begin();
    matrix.show();
    matrix.setBrightness(20);

    for (int i = 0; i < 192; i++)
    {
        matrix.setPixelColor(i, 100, 100, 0);
        matrix.show();
    }
}

void loop()
{
    if (bluetooth.available())
    {
        Serial.write(bluetooth.read());
    }
    if (Serial.available()) 
    {
        bluetooth.write(Serial.read());
    }
}