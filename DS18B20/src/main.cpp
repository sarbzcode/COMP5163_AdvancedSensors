// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Application
// COMP 5163
// Acadia University
// ******************************************************************

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication library
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

// Unique 8-byte address of the sensor
DeviceAddress sensorAddress;

// Convert a temperature in Celsius to a judgement string
String judgeTemperature(float fTemp) {
  if (fTemp < 10.0)
    return "Cold!";
  else if (fTemp < 15.0)
    return "Cool";
  else if (fTemp < 25.0)
    return "Perfect";
  else if (fTemp < 30.0)
    return "Warm";
  else if (fTemp < 35.0)
    return "Hot";
  else
    return "Too Hot!";
}

void setup() {
  // configure the USB serial monitor
  Serial.begin(115200);
  Serial.println();
  Serial.println("Temperature Application");

  // Start the DS18B20 sensor
  DS18B20.begin();

  // Check that at least one sensor is on the bus and that we can read its address
  if (DS18B20.getDeviceCount() == 0 || !DS18B20.getAddress(sensorAddress, 0)) {
    Serial.println("No DS18B20 temperature sensors are installed!");
    // terminate gracefully: nothing more to do, so halt here
    while (true) {
      delay(1000);
    }
  }

  // Print the sensor's unique address
  Serial.print("Found DS18B20 sensor with address: ");
  for (uint8_t i = 0; i < 8; i++) {
    if (sensorAddress[i] < 16)
      Serial.print("0");
    Serial.print(sensorAddress[i], HEX);
  }
  Serial.println();
}

void loop() {
  float fTemp;

  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  // fetch the temperature. We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);

  // handle a sensor that was unplugged after startup
  if (fTemp == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: DS18B20 sensor disconnected!");
  } else {
    // print the temp and judgement to the USB serial monitor
    Serial.println("Current temperature is: " + String(fTemp) + "\xC2\xB0 C or " + judgeTemperature(fTemp));
  }

  // wait 5s (5000ms) before doing this again
  delay(5000);
}