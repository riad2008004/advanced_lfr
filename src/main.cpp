#include <Arduino.h>
#include "display.h"
#include "button.h"
#include "motor.h"
#include "pidcalc.h"
#include "irsensor.h"
#include "memory.h"
#include "sonar.h"

//------------ Global variables ----------------------
extern struct Memory sensorMemory;
const int numOfSensors = 8;
extern unsigned int sensorThreshold[numOfSensors];
void setup()
{
  // Serial.begin(9600);
  displaySetup();
  buttonSetup();
  memorySetup(&sensorMemory);
  memoryRetriveConfigVariables();

  // Only Once needed
  // memorySaveMotorVariables();
  // memorySaveSensorVariables();
  // memorySaveConfigVariables();

  sensorSetup();
  motorSetup();
  PIDsetup();
  sonarSetup();
  displayBootScreen();
}
String arr[100];
void loop()
{
  // memorySaveMotorVariables();

  displayMenu("MAIN_MENU");

  // sonarTest(1);
  // readSensors();
  // showRawSensorData();
  // sonarDrive();
  // motorCalibrate();
  // memoryGetArray(&sensorMemory, arr);
  // Serial.println("---------");
  // Serial.println("---------");
  // for (int i = 0; i < 100; i++)
  // {
  //   Serial.println(arr[i]);
  // }
  // readSensors();
}