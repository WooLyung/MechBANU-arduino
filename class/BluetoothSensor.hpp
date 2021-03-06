#ifndef BLUETOOTHSENSOR_HPP
#define BLUETOOTHSENSOR_HPP

#include <SoftwareSerial.h>
#include <DHT.h>
#include "Display.hpp"
#include "MoodLamp.hpp"
#include "../util/Pins.hpp"

class BluetoothSensor
{
private:
    SoftwareSerial bluetooth = SoftwareSerial(PIN_BLUETOOTH_TXD, PIN_BLUETOOTH_RXD);
    DHT temp = DHT(PIN_TEMP, DHT22);
    Display* display;
    MoodLamp* moodLamp;

    unsigned long pre = millis();
    int connectTime = 0;
    int touchPattern[4] = { -1, -1, -1, -1 };
    bool touchFlag[4] = { false, false, false, false };

public:
    BluetoothSensor(Display*, MoodLamp*);

    void touch();
    void setup();
    void read();

private:
    float pulse2ugm3(unsigned long);
    void op_0();
    void op_1();
    void op_2();
    void op_3();
};

BluetoothSensor::BluetoothSensor(Display* display, MoodLamp* MoodLamp)
{
    this->display = display;
    this->moodLamp = moodLamp;
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

void BluetoothSensor::touch()
{
    int code = -1;

    // enter
    if (digitalRead(PIN_TOUCH1) && !touchFlag[0])
    {
        touchFlag[0] = true;
        code = 1;
    }
    if (digitalRead(PIN_TOUCH2) && !touchFlag[1])
    {
        touchFlag[1] = true;
        code = 2;
    }
    if (digitalRead(PIN_TOUCH3) && !touchFlag[2])
    {
        touchFlag[2] = true;
        code = 3;
    }
    if (digitalRead(PIN_TOUCH4) && !touchFlag[3])
    {
        touchFlag[3] = true;
        code = 4;
    }

    // pattern
    if (code != -1)
    {
        touchPattern[3] = touchPattern[2];
        touchPattern[2] = touchPattern[1];
        touchPattern[1] = touchPattern[0];
        touchPattern[0] = code;

        if (touchPattern[0] == 4 && touchPattern[1] == 3 && touchPattern[2] == 2 && touchPattern[3] == 1)
        {
            byte a[4] = { 0x48, 0x05, 0x00, 0x00 };
            bluetooth.write(a, 4);
        }
    }

    // exit
    if (!digitalRead(PIN_TOUCH1))
        touchFlag[0] = false;
    if (!digitalRead(PIN_TOUCH2))
        touchFlag[1] = false;
    if (!digitalRead(PIN_TOUCH3))
        touchFlag[2] = false;
    if (!digitalRead(PIN_TOUCH4))
        touchFlag[3] = false;
}

void BluetoothSensor::read()
{
    connectTime += millis() - pre;
    pre = millis();

    if (bluetooth.available())
    {
        byte buffer[4];
        bluetooth.readBytes(buffer, 4);

        char H = buffer[0];
        int op = buffer[1];
        size_t len = buffer[2] * 16 + buffer[3];

        connectTime = 0;
        display->setConnected(true);
        if (H == 'H')
        {
            if (op == 0x00) // ping
                op_0();
            else if (op == 0x01) // display
                op_1();
            else if (op == 0x02) // mood
                op_2();
            else if (op == 0x03) // request
                op_3();
        }
    }
    else if (connectTime >= 30000 || connectTime < 0)
    {
        connectTime = 0;
        display->setConnected(false);
    }
}

void BluetoothSensor::op_0()
{
}

void BluetoothSensor::op_1()
{
    byte buffer[578];
    bluetooth.readBytes(buffer, 578);

    int duration = buffer[0];
    int brightness = buffer[1];

    display->setDuration(duration);
    display->setBrightness(brightness);
    for (int i = 0; i < 192; i++)
        display->setColor(i, buffer[i * 3 + 2], buffer[i * 3 + 3], buffer[i * 3 + 4]);
    display->refresh();
}

void BluetoothSensor::op_2()
{
    byte buffer[91];
    bluetooth.readBytes(buffer, 91);

    int brightness = buffer[0];

    moodLamp->setBrightness(brightness);
    for (int i = 0; i < 30; i++)
        moodLamp->setColor(i, buffer[i * 3 + 1], buffer[i * 3 + 2], buffer[i * 3 + 3]);
    moodLamp->refresh();
}

void BluetoothSensor::op_3()
{
    byte buffer[1];
    bluetooth.readBytes(buffer, 1);

    int code = buffer[0];
    
    if (code == 0)
    {
        float t = temp.readTemperature();
        byte* p = (byte*) &t;
        byte buffer[9] = { 0x48, 0x04, 0x00, 0x04, 0x00, p[0], p[1], p[2], p[3] };
        bluetooth.write(buffer, 9);
    }
    else if (code == 1)
    {
        float h = temp.readHumidity();
        byte* p = (byte*) &h;
        byte buffer[9] = { 0x48, 0x04, 0x00, 0x04, 0x01, p[0], p[1], p[2], p[3] };
        bluetooth.write(buffer, 9);     
    }
    else if (code == 2)
    {
        unsigned long pulse = 0;
        while (pulse)
            unsigned long pulse = pulseIn(PIN_DUST, LOW, 100000);
        float d = pulse2ugm3(pulse);
        byte* p = (byte*) &d;
        byte buffer[9] = { 0x48, 0x04, 0x00, 0x04, 0x02, p[0], p[1], p[2], p[3] };
        bluetooth.write(buffer, 9);
    }
}

#endif