#ifndef EngineControl_h
#define EngineControl_h

#include <Servo.h>

#define SERVO_INTERVAL 150

Servo MyServo;

int angles[] = {0, 90, 180, 90};
int curr = 0;
int lastAngle = angles[0];

unsigned long lastServoTime = 0;

int servoRotate() {
  unsigned long currentServoTime = millis();

  if(currentServoTime - lastServoTime >= SERVO_INTERVAL) {
    curr = (curr + 1) % 4;
    int angle = angles[curr];
    MyServo.write(angle);

    lastServoTime = currentServoTime;
    lastAngle = angle;
  }

  return lastAngle;
}

#endif