#ifndef Motion_h
#define Motion_h

/* 4pin - mode */
int in1Pin = 4;
int in2Pin = 5;
int in3Pin = 7;
int in4Pin = 6;

// tail lights
int leftLightPin = 2;
int rightLightPin = 8;

float leftComp = 1.00;
float rightComp = 0.94;

// Left Wheel CONTROl
void setLeft(bool reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in1Pin, reverse);
  analogWrite(in2Pin, speed);
  digitalWrite(leftLightPin, HIGH);
}

// Right Wheel CONTROL
void setRight(bool reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in3Pin, reverse);
  analogWrite(in4Pin, speed);
  digitalWrite(rightLightPin, HIGH);
}

// STOP
void fullStop(bool reverse) {
  setLeft(reverse, 0);
  setRight(reverse, 0);
}

// Go STRAIGHT
void goStraight(bool reverse, int speed) {
  setLeft(reverse, speed * leftComp);
  setRight(reverse, speed * rightComp);
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