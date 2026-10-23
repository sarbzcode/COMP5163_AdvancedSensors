// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College
// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  DS18B20.begin();
}
void loop()
{
  float fTemp;
  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();
  // fetch the temperature. We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);
  // print the temp to the USB serial monitor
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius");
  // wait 2s (2000ms) before doing this again
  delay(2000);
}
