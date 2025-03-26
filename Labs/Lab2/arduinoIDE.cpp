const int enablePin = 11;
const int in1Pin = 10;
const int in2Pin = 9;
const int switchPin = 7;
const int potPin = 0;
const float fixedR = 1000.0
const float VCC = 5.0

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int speed = analogRead(potPin) / 4;
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(";\t");

  boolean reverse = digitalRead(switchPin);
  Serial.print("Sequence: ");

  if(reverse == 1) {
    Serial.print("Clockwise");
  } else {
    Serial.print("Counter-Clockwise");
  }  
  Serial.print(";\t");

  setMotor(speed, reverse);

  int sensorValue_A1 = analogRead(A1);
  float Vref = (sensorValue_A1 / 1023.0) * VCC;
  float R = fixedR * (VCC - Vref) / Vref;
  Serial.print("POT-LIN: ");
  Serial.println(R);

  delay(1);
  delay(500);
}

void setMotor(int speed, boolean reverse) {
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, !reverse);
  digitalWrite(in2Pin, reverse);
}
