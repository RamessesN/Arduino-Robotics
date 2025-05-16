#include "motion_setting.h"
#include "motion_control.h"
#include "servo_control.h"
#include "ultrasound_control.h"

#define ANGLE_INTERVAL 30

float leftDist = 0;
float frontDist = 0;
float rightDist = 0;

unsigned long lastAngleTime = 0;

bool isWaiting = false;

void setup() {
  Serial.begin(9600);
  // Wheel Driver
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  // Light Driver
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);
  // Engine Driver
  MyServo.attach(9);
  // Ultrasound Driver
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int angle = servoRotate();
  int distance = distanceDetect();

  unsigned long currentAngleTime = millis();

  if(!isWaiting) {
    switch(angle) {
      case 0:
        leftDist = distance;
        Serial.print("Left: ");
        Serial.println(leftDist);
        isWaiting = true;
        lastAngleTime = currentAngleTime;
        break;
      case 90:
        frontDist = distanceDetect();
        Serial.print("Front: ");
        Serial.println(frontDist);
        isWaiting = true;
        lastAngleTime = currentAngleTime;
        break;
      case 180:
        rightDist = distance;
        Serial.print("Right: ");
        Serial.println(rightDist);
        isWaiting = true;
        lastAngleTime = currentAngleTime;
        break;
    }
    carDrive(leftDist, frontDist, rightDist);
  } else if(currentAngleTime - lastAngleTime >= ANGLE_INTERVAL) {
    isWaiting = false;
  }
}