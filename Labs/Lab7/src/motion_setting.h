#ifndef MotionSetting_h
#define MotionSetting_h

/* 4pin - mode */
int in1Pin = 4;
int in2Pin = 5;
int in3Pin = 7;
int in4Pin = 6;

// tail lights
int leftLightPin = 2;
int rightLightPin = 8;

float leftComp = 1.00;
float rightComp = 1.00;

// Left Wheel CONTROl
void setLeft(bool reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in1Pin, reverse);
  analogWrite(in2Pin, speed);
  digitalWrite(leftLightPin, reverse ? LOW: HIGH);
}

// Right Wheel CONTROL
void setRight(bool reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in3Pin, reverse);
  analogWrite(in4Pin, speed);
  digitalWrite(rightLightPin, reverse ? LOW: HIGH);
}

// STOP
void fullStop() {
  digitalWrite(in1Pin, LOW);
  analogWrite(in2Pin, 0);
  digitalWrite(in3Pin, LOW);
  analogWrite(in4Pin, 0);
  digitalWrite(leftLightPin, LOW);
  digitalWrite(rightLightPin, LOW);
}

// Go STRAIGHT
void goStraight(bool reverse, int leftSpeed, int rightSpeed) {
  setLeft(reverse, leftSpeed);
  setRight(reverse, rightSpeed);
}

// Go BACK
void goBack(bool reverse, int speed) {
  setLeft(!reverse, 255 - speed * leftComp);
  setRight(!reverse, 255 - speed * rightComp);
}

// Turn LEFT
void turnLeft(bool reverse, int speed) {
  setLeft(!reverse, 255 - speed * leftComp);
  setRight(reverse, speed * rightComp);
}

// Turn RIGHT
void turnRight(bool reverse, int speed) {
  setLeft(reverse, speed * leftComp);
  setRight(!reverse, 255 - speed * rightComp);
}

#endif