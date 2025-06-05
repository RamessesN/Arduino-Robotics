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

void bmePrint() {
  Serial.println("----------------------------- BME280 ------------------------------");

  float temp = getTemperature();
  float hum = getHumidity();
  float pres = getPressure();

  Serial.print("| Temprature: "); Serial.print(temp); Serial.print("℃");
  Serial.print(", Humidity: "); Serial.print(hum); Serial.print("%");
  Serial.print(", Air pressure: "); Serial.print(pres); Serial.println("hPa |");
  
  Serial.println("-------------------------------------------------------------------");
}

#endif