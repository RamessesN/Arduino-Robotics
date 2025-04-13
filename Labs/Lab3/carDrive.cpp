/* 四引脚 mode */
int in1Pin = 5;
int in2Pin = 6;
int in3Pin = 9;
int in4Pin = 10;

int baseSpeed = 150;

// fluctuating rate
float leftComp = 1.00;
float rightComp = 1.00;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // Initialize
  analogWrite(in1Pin, 0);
  analogWrite(in4Pin, 0);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int leftSpeed = baseSpeed * leftComp;
  int rightSpeed = baseSpeed * rightComp;

  boolean reverse = 0;
  setLeft(reverse, leftSpeed);
  setRight(reverse, rightSpeed);
}

// Left Wheel CONTROL
void setLeft(boolean reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in2Pin, reverse);
  analogWrite(in1Pin, speed);
}

// Right Wheel CONTR OL
void setRight(boolean reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in4Pin, !reverse);
  analogWrite(in3Pin, 255 - speed);
}