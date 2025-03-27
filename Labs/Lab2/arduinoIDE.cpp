int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPin = 7;
int potPin = 0;
int fixedR = 10000;
int VCC = 5;

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

  int sensorValue_A0 = analogRead(A0);
  float Vout = (sensorValue_A0 / 1023.0) * VCC;
  float Rpot = fixedR * ((VCC - Vout) / Vout);
  Serial.print("POT-LIN: ");
  Serial.println(sensorValue_A0);

  delay(1);
  delay(500);
}

void setMotor(int speed, boolean reverse) {
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, !reverse);
  digitalWrite(in2Pin, reverse);
}