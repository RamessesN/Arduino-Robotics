#ifndef MotionDetect_H
#define MotionDetect_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

extern Adafruit_MPU6050 mpu;

struct variables {
  float x;
  float y;
  float z;
};

extern variables accData;
extern variables gyroData;

void getVariables() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  accData = { a.acceleration.x - 0.40, a.acceleration.y + 0.16, a.acceleration.z + 0.560 };
  gyroData = { g.gyro.x + 0.02, g.gyro.y - 0.06, g.gyro.z + 0.02 };
}

void mpuPrint() {
  getVariables();

  Serial.println("------------- MPU6050  -------------");

  Serial.println("| ----- Accelerations (m/s^2) ---- |");
  Serial.print("|    x: "); Serial.print(accData.x);
  Serial.print(", y: "); Serial.print(accData.y);
  Serial.print(", z: "); Serial.print(accData.z);
  Serial.println("    |");

  Serial.println("| --------- Gyro (rad/s) --------- |");
  Serial.print("|    x: "); Serial.print(gyroData.x);
  Serial.print(", y: "); Serial.print(gyroData.y);
  Serial.print(", z: "); Serial.print(gyroData.z);
  Serial.println("   |");

  Serial.println("------------------------------------");
}

#endif
