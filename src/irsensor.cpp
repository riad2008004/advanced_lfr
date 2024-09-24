#include <Arduino.h>
#include "irsensor.h"

static const byte numOfSensors = 8;
static byte i;
static unsigned int sensorMaxWaitTime = 1024;
int sensorRawReading[numOfSensors];
boolean sensorBinaryReading[numOfSensors];
byte sensorBinaryData;

int sensorThreshold[numOfSensors] = {700, 700, 700, 700, 700, 700, 700, 700};
static int sensorHighestReadings[numOfSensors];
static int sensorLowestReadings[numOfSensors];

byte numOfHighReadings;
//---------------------- Connection Related---------------------------------------
#define IR_LED 31
static byte sensorPin[numOfSensors] = {A11, A9, A8, A7, A6, A5, A4, A2}; // arduino analog pins
//------------------------- Invert Related Variable--------------------------------------------------
bool isInvert = 0;
// ------------------------------External Global Variables----------------------------
extern void Forward(double del, int vel);
extern void Stop(double del);
extern void memoryRetrieveSensorVariables();
extern void memorySaveSensorVariables();
extern struct Memory sensorMemory;
extern void memoryAddReading(struct Memory *m, int reading);
extern void Right(double del, int vel);

void sensorSetup()
{
    memoryRetrieveSensorVariables();
}

void readSensors()
{
    for (int i = 0; i < numOfSensors; i++)
    {
        sensorRawReading[i] = analogRead(sensorPin[i]);
    }
}

void showRawSensorData()
{
    readSensors();
    for (i = 0; i < numOfSensors; i++)
    {
        Serial.print(sensorRawReading[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void showBinarySensorData(bool newline)
{
    readSensors();
    generateBinary();
    for (i = 0; i < numOfSensors; i++)
    {
        Serial.print(sensorBinaryReading[i]);
        Serial.print(" ");
    }
    if (newline)
        Serial.println();
}
void generateBinary()
{
    /**
     * Generates a 8 bit binary value from the sensor reading
     */
    numOfHighReadings = 0;
    sensorBinaryData = 0;
    for (int i = 0; i < numOfSensors; i++)
    {
        if (sensorRawReading[i] < sensorThreshold[i])
        {
            sensorBinaryReading[i] = 1;
            sensorBinaryData = (sensorBinaryData << 1) | 1;
        }
        else
        {
            sensorBinaryReading[i] = 0;
            sensorBinaryData = (sensorBinaryData << 1);
        }
        numOfHighReadings += sensorBinaryReading[i];
    }
    //--------- Check for Invert situation ----------------------------------------------

    // Handling Invert situations
    // if (isInvert)
    // {
    //     for (i = 0; i < numOfSensors; i++)
    //     {
    //         sensorBinaryReading[i] ^= 1;
    //     }
    //     sensorBinaryData = ~sensorBinaryData;
    // }

    memoryAddReading(&sensorMemory, sensorBinaryData);
}

void generateThreshold()
{
    /*
     * For generating threshold value
     */
    Stop(500);
    Serial.println("Generate Threshold");
    for (int fill_i = 0; fill_i < numOfSensors; fill_i++)
    {
        sensorHighestReadings[fill_i] = 0;
        sensorLowestReadings[fill_i] = sensorMaxWaitTime;
    }
    for (int th_i = 0; th_i < 300; th_i++)
    {
        Right(4, 80); // set the speed while generating Threshold of IR
        readSensors();
        for (int sense = 0; sense < numOfSensors; sense++)
        {
            if (sensorRawReading[sense] > sensorHighestReadings[sense])
                sensorHighestReadings[sense] = sensorRawReading[sense];
            if (sensorRawReading[sense] < sensorLowestReadings[sense])
                sensorLowestReadings[sense] = sensorRawReading[sense];
        }
    }
    for (int thr = 0; thr < numOfSensors; thr++)
    {
        sensorThreshold[thr] = ((sensorHighestReadings[thr] + sensorLowestReadings[thr]) / 2);
    }
    Stop(10);
    memorySaveSensorVariables();
}
