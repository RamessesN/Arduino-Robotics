#ifndef LCDDemonstrate_H
#define LCDDemonstrate_H

#include <LiquidCrystal_I2C.h>
#include "FactorDetect.h"
#include "MotionDetect.h"

extern LiquidCrystal_I2C lcd;

void basicDemonstrate() {
  lcd.setCursor(2, 0);
  lcd.print("LORD LOBSTER");
  lcd.setCursor(4, 1);
  lcd.print("Group #15");
}

void bmeDemonstrate() {
  static unsigned long lastScrollTime = 0;
  static int scrollIndex = 0;

  float temp, hum, pres;
  getBMEData(temp, hum, pres);

  String fullText = "T:" + String(temp, 2) + "C "
                  + "H:" + String(hum, 2) + "% "
                  + "P:" + String(pres, 2) + "hPa ";

  const int windowWidth = 16;

  fullText += "   " + fullText;

  unsigned long currentTime = millis();
  if (currentTime - lastScrollTime > 250) {
    lcd.setCursor(0, 0);
    lcd.print(fullText.substring(scrollIndex, scrollIndex + windowWidth));
    scrollIndex++;
    if (scrollIndex > fullText.length() - windowWidth) {
      scrollIndex = 0;
    }
    lastScrollTime = currentTime;
  }
}

void mpuDemonstrate() {
  static unsigned long lastScrollTime = 0;
  static int scrollIndex = 0;

  getVariables();

  String fullText = String("acc: ") + "x:" + String(accData.x, 2) + " "
                  + "y:" + String(accData.y, 2) + " "
                  + "z:" + String(accData.z, 2) + " "
                  + String("gyro: ") + "x: " + String(gyroData.x, 2) + " "
                  + "y:" + String(gyroData.y, 2) + " "
                  + "z: " + String(gyroData.z, 2) + " ";

  const int windowWidth = 16;

  fullText += "   " + fullText;

  unsigned long currentTime = millis();
  if (currentTime - lastScrollTime > 250) {
    lcd.setCursor(0, 1);
    lcd.print(fullText.substring(scrollIndex, scrollIndex + windowWidth));
    scrollIndex++;
    if (scrollIndex > fullText.length() - windowWidth) {
      scrollIndex = 0;
    }
    lastScrollTime = currentTime;
  }
}

#endif