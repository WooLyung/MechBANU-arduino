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
}

void loop()
{
    if (bluetooth.available())
    {
        char str[100];
        bluetooth.readString().toCharArray(str, 100);
        Serial.print(str);

        if (!strcmp(str, "불 켜\n"))
        {
            for (int i = 0; i < 192; i++)
            {
                matrix.setPixelColor(i, 100, 100, 0);
                matrix.show();
            }
        }
        else if (!strcmp(str, "불 꺼\n"))
        {
            for (int i = 0; i < 192; i++)
            {
                matrix.setPixelColor(i, 0, 0, 0);
                matrix.show();
            }
        }
    }
    if (Serial.available()) 
    {
        bluetooth.write(Serial.read());
    }
}