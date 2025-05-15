#include "motion_setting.h"
#include "motion_control.h"
#include "engine_control.h"
#include "ultrasound_control.h"

int baseSpeed = 150;

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

float frontDist = 0;
float leftDist = 0;
float rightDist = 0;

void loop() {
  bool reverse = false;

  int angle = servoRotate();
  int distance = distanceDetect();

  switch(angle) {
    case 0:
      leftDist = distance;
      Serial.print("Left: ");
      Serial.println(leftDist);
      break;
    case 90:
      frontDist = distance;
      Serial.print("Front: ");
      Serial.println(frontDist);
      break;
    case 180:
      rightDist = distance;
      Serial.print("Right: ");
      Serial.println(rightDist);
      break;
  }

  carDrive(leftDist, frontDist, rightDist);
}
