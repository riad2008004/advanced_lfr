#ifndef _IR_SENSOR
#define _IR_SENSOR

#include <Arduino.h>

void sensorSetup();
void readSensors();
void generateBinary();
void generateThreshold();
void showRawSensorData();
void showBinarySensorData(bool newline);
void sensorRetrieveThreshold();

#endif //_IR_SENSOR