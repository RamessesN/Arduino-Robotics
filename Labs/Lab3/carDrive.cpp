/* 4PIN-MODE */
int in1Pin = 4;
int in2Pin = 5;
int in3Pin = 8;
int in4Pin = 9;

int light_LEFT = 2;
int light_RIGHT = 7;

int baseSpeed = 150;

float leftComp = 1.00;
float rightComp = 0.94;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(light_LEFT, OUTPUT);
  pinMode(light_RIGHT, OUTPUT);

  digitalWrite(light_LEFT, LOW);
  digitalWrite(light_RIGHT, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean reverse = 0;
  setLeft(reverse, baseSpeed * leftComp);
  setRight(reverse, baseSpeed * rightComp);
  delay(5);
}

// Left Wheel CONTROL
void setLeft(boolean reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in1Pin, reverse);
  analogWrite(in2Pin, speed);
  digitalWrite(light_LEFT, HIGH);
}

// Right Wheel CONTR OL
void setRight(boolean reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in3Pin, reverse);
  analogWrite(in4Pin, speed);
  digitalWrite(light_RIGHT, HIGH);
}