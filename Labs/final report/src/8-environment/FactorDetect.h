#ifndef FactorDetect_H
#define FactorDetect_H

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

extern Adafruit_BME280 bme;

float getTemperature() {
  return bme.readTemperature();
}

float getHumidity() {
  return bme.readHumidity();
}

float getPressure() {
  return bme.readPressure() / 100.0F;
}

void getBMEData(float &temp, float &hum, float &pres) {
  temp = getTemperature();
  hum = getHumidity();
  pres = getPressure();
}

void bmePrint() {
  float temp, hum, pres;
  getBMEData(temp, hum, pres);

  Serial.println("----------------------------- BME280 ------------------------------");

  Serial.print("| Temprature: "); Serial.print(temp); Serial.print("℃");
  Serial.print(", Humidity: "); Serial.print(hum); Serial.print("%");
  Serial.print(", Air pressure: "); Serial.print(pres); Serial.println("hPa |");
  
  Serial.println("-------------------------------------------------------------------");
}

#endif