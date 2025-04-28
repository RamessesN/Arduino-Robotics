void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int sensorValue_LEFT = analogRead(A4);
  delay(2);
  int sensorValue_MIDDLE = analogRead(A2);
  delay(2);
  int sensorValue_RIGHT = analogRead(A0);
  delay(2);

  Serial.print("LEFT: ");
  Serial.print(printStatus(sensorValue_LEFT));
  Serial.print("; MIDDLE: ");
  Serial.print(printStatus(sensorValue_MIDDLE));
  Serial.print("; LIGHT: ");
  Serial.println(printStatus(sensorValue_RIGHT));

  delay(1000);
}

int printStatus(int value) {
  int ans = 0;
  if(value > 800) {
    ans = 1;
  }
  return ans;
}