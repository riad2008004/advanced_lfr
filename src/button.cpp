#include <Arduino.h>
#include "button.h"
// test
#define BTN_UP 12
#define BTN_DOWN 16
#define BTN_LEFT 8
#define BTN_RIGHT 14
#define BTN_SELECT 10

// extern bool portRead(char port_type, byte pin_number); 
// Above line was for directly access button pin (C_B_RIAD)

void buttonSetup()
{
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_SELECT, INPUT);
}

// void buttonTest()
// {
//     Serial.print("UP ");
//     Serial.print(portRead('C', 7));
//     Serial.print("---");
//     Serial.print("DOWN  ");
//     Serial.print(portRead('A', 0));
//     Serial.print("---");
//     Serial.print("LEFT ");
//     Serial.print(portRead('A', 4));
//     Serial.print("---");
//     Serial.print("RIGHT ");
//     Serial.print(portRead('A', 2));
//     Serial.print("---");
//     Serial.print("SELECT ");
//     Serial.println(portRead('A', 6));
// }
//    (C_B_RIAD)

String buttonPressed()
{
    // if (portRead('C', 7) == HIGH)
    if(digitalRead(BTN_UP))
    {
        return "BTN_UP";
    }
    // else if (portRead('A', 0) == HIGH)
    else if(digitalRead(BTN_DOWN))
    {
        return "BTN_DOWN";
    }
    else if (digitalRead(BTN_SELECT))
    {
        return "BTN_SELECT";
    }
    else if (digitalRead(BTN_LEFT))
    {
        return "BTN_LEFT";
    }
    else if (digitalRead(BTN_RIGHT))
    {
        return "BTN_RIGHT";
    }
    else
    {
        return "NO";
    }
}