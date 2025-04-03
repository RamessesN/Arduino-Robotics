int enablePin1 = 9;
int enablePin2 = 10;
int in1Pin = 2;
int in2Pin = 3;
int in3Pin = 4;
int in4Pin = 5;

int leftSpeed = 155;
int rightSpeed = 155;

int potPin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(int4Pin, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean reverse = 0;
  setMotor(leftSpeed, rightSpeed, reverse);

  if(reverse == 1) {
    Serial.println("STOP!");
  } else {
    Serial.println("GO!");
  }
  
}

void setMotor(int leftSpeed, int rightSpeed, boolean reverse) {
  // Right Wheel CONTROL
  analogWrite(enablePin1, rightSpeed);
  digitalWrite(in1Pin, !reverse);
  digitalWrite(in2Pin, reverse);
  // Left Wheel CONTROL
  analogWrite(enablePin1, leftSpeed);
  digitalWrite(in3Pin, !reverse);
  digitalWrite(in4Pin, reverse);
}
