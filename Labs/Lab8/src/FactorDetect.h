#ifndef FactorDetect_H
#define FactorDetect_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

extern Adafruit_BME280 bme;

void tempGet() {
  Serial.print("Temprature: ");
  Serial.print(bme.readTemperature());
  Serial.print(" *C");
}

void presGet() {
  Serial.print("Air Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print(" hPa");
}

float altGet() {
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.print(" m");

  return altitude;
}

void humGet() {
  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.print(" %");
}

#endif