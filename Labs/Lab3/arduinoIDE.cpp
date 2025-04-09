/* 四引脚 mode */
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;

int leftSpeed = 75;
int rightSpeed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean reverse = 0;
  setLeft(reverse, leftSpeed);
  setRight(reverse, rightSpeed);
}

// Left Wheel CONTROL
void setLeft(boolean reverse, int speed) {
  analogWrite(in3Pin, reverse ? speed : 0);
  analogWrite(in4Pin, reverse ? 0 : speed);
}

// Right Wheel CONTROL
void setRight(boolean reverse, int speed) {
  analogWrite(in3Pin, reverse ? 0 : speed);
  analogWrite(in3Pin, reverse ? speed : 0);
}