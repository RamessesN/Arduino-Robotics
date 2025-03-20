void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue_A0 = analogRead(A0);

  Serial.print("Sensor Value of A0 = ");
  Serial.println(sensorValue_A0);
  Serial.println();

  delay(1);
  delay(1000);
}
