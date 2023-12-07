#include <Arduino.h>

#define pinF 29
#define trigL 44
#define echoL 45
#define trigR 47
#define echoR 46

long duration;
float distance;
char dir;
long waitTime = 2200;

void sonarSetup()
{
    pinMode(pinF, INPUT);
    pinMode(trigL, OUTPUT);
    pinMode(trigR, OUTPUT);
    pinMode(echoL, INPUT);
    pinMode(echoR, INPUT);
}

float sonarSearchF()
{
    return digitalRead(29);
}

float sonarSearchL()
{
    digitalWrite(trigL, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigL, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoL, HIGH, waitTime);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    // Serial.print(distance);
    if (distance == 0)
        distance = 50;
    return distance;
}

float sonarSearchR()
{
    digitalWrite(trigR, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigR, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoR, HIGH, waitTime);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    // Serial.print(distance);
    if (distance == 0)
        distance = 30;
    return distance;
}

void sonarTest(bool newline)
{
    Serial.print("F = ");
    Serial.print(sonarSearchF());
    Serial.print("  ");
    Serial.print("R = ");
    Serial.print(sonarSearchR());
    Serial.print("  ");
    Serial.print("L = ");
    Serial.print(sonarSearchL());
    Serial.print("  ");
    if (newline)
        Serial.println("");
}
