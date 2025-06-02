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

void getVariables(variables &acc, variables &gyro) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  acc = { a.acceleration.x - 0.40, a.acceleration.y + 0.16, a.acceleration.z + 0.60 };
  gyro = { g.gyro.x + 0.02, g.gyro.y - 0.06, g.gyro.z + 0.02 };
}

void mpuPrint() {
  variables acc, gyro;
  getVariables(acc, gyro);

  Serial.println("------------- MPU6050  -------------");

  Serial.println("| ----- Accelerations (m/s^2) ---- |");
  Serial.print("|    x: "); Serial.print(acc.x);
  Serial.print(", y: "); Serial.print(acc.y);
  Serial.print(", z: "); Serial.print(acc.z);
  Serial.println("    |");

  Serial.println("| --------- Gyro (rad/s) --------- |");
  Serial.print("|    x: "); Serial.print(gyro.x);
  Serial.print(", y: "); Serial.print(gyro.y);
  Serial.print(", z: "); Serial.print(gyro.z);
  Serial.println("   |");

  Serial.println("------------------------------------");
}

#endif
