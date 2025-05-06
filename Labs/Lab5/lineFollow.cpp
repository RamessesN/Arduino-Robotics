/* 4pin - mode */
int in1Pin = 4;
int in2Pin = 5;
int in3Pin = 8;
int in4Pin = 9;

// Tail Lights
int leftLight = 2;
int rightLight = 7;

// Speed Setting
int base_Speed = 180;
int decelerated_Speed_small = 145;
int decelerated_Speed_big = 110;
int accelerated_Speed_small = 215;
int accelerated_Speed_big = 250;

// Fluctuating Rate
float leftComp = 1.00;
float rightComp = 0.94;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Wheel Driver
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  // Light Driver
  pinMode(leftLight, OUTPUT);
  pinMode(rightLight, OUTPUT);

  // Wheel Initialization
  analogWrite(in1Pin, 0);
  analogWrite(in4Pin, 0);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  // Light Initialization
  digitalWrite(leftLight, LOW);
  digitalWrite(rightLight, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool reverse = false;

  int sensorValue_LEFT = getSmoothedValue(A4);
  delay(2);
  int sensorValue_MIDDLE = getSmoothedValue(A2);
  delay(2);
  int sensorValue_RIGHT = getSmoothedValue(A0);
  delay(2);

  Serial.print("LEFT: ");
  Serial.print(sensorValue_LEFT);
  Serial.print("; MIDDLE: ");
  Serial.print(sensorValue_MIDDLE);
  Serial.print("; LIGHT: ");
  Serial.println(sensorValue_RIGHT);

  if(sensorValue_LEFT <= 100 && sensorValue_MIDDLE <= 100 && sensorValue_RIGHT <= 100) {
    breakLingHandle();
  } else {
    Turn(reverse, sensorValue_LEFT, sensorValue_MIDDLE, sensorValue_RIGHT);
  }

  delay(10); // read arguments every 10ms
}

int getSmoothedValue(int pin) {
  int total = 0;
  for (int i = 0; i < 5; i++) {
    total += analogRead(pin);
    delay(2);
  }
  return total / 5;
}

// Left Wheel CONTROL
void setLeft(bool reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in1Pin, reverse);
  analogWrite(in2Pin, speed);
  digitalWrite(leftLight, HIGH);
}

// Right Wheel CONTROL
void setRight(bool reverse, int speed) {
  speed = constrain(speed, 0, 255);
  digitalWrite(in3Pin, reverse);
  analogWrite(in4Pin, speed);
  digitalWrite(rightLight, HIGH);
}

/**
  Break Line Handling -
  If the line is detected, perform the corresponding steering operation. If not, reverse back.
  After returning to the origin, it turned left by a certain Angle. If the line was detected in the process, it performed the corresponding steering operation, if not, it turned back to the origin.
  After returning to the origin, turn right by a certain Angle. If the line is detected in the process, the corresponding steering operation is performed, if not, the original direction is turned back.
  Otherwise, it remains stationary at the origin and starts flashing the tail light to indicate that the user needs manual correction.
*/
void breakLineHandle() {
  bool reverse = false;

  // Step 1: Try Going Forward a Short Distance and Check if can Find the Line again
  setLeft(reverse, base_Speed);
  setRight(reverse, base_Speed);
  unsigned long startTime = millis();
  while(millis() - startTime < 300) {
    int left = getSmoothedValue(A4);
    int middle = getSmoothedValue(A2);
    int right = getSmoothedValue(A0);
    if (!(left <= 100 && middle <= 100 && right <= 100)) {
      Turn(reverse, left, middle, right);
      return;
    }
    delay(10);
  }

  // Step 2: Stop and Go Back to Origin
  stopMotors();
  delay(100);
  reverse = true;
  setLeft(reverse, base_Speed);
  setRight(reverse, base_Speed);
  delay(300);
  stopMotors();

  // Step 3: Turn Left to Scan Line
  reverse = false;
  setLeft(reverse, decelerated_Speed_big);
  setRight(reverse, accelerated_Speed_big);
  startTime = millis();
  while (millis() - startTime < 500) {
    int left = getSmoothedValue(A4);
    int middle = getSmoothedValue(A2);
    int right = getSmoothedValue(A0);
    if (!(left <= 100 && middle <= 100 && right <= 100)) {
      Turn(reverse, left, middle, right);
      return;
    }
    delay(10);
  }

  // Step 4: Turn Back
  reverse = false;
  setLeft(reverse, accelerated_Speed_big);
  setRight(reverse, decelerated_Speed_big);
  delay(500);
  stopMotors();

  // Step 5: Turn Right to Scan Line
  setLeft(reverse, accelerated_Speed_big);
  setRight(reverse, decelerated_Speed_big);
  startTime = millis();
  while (millis() - startTime < 500) {
    int left = getSmoothedValue(A4);
    int middle = getSmoothedValue(A2);
    int right = getSmoothedValue(A0);
    if (!(left <= 100 && middle <= 100 && right <= 100)) {
      Turn(reverse, left, middle, right);
      return;
    }
    delay(10);
  }

  // Step 6: All Try Failed, Requiring Human intervention
  stopMotors();
  alertManualFair();
}

void stopMotors() {
  setLeft(false, 0);
  setRight(false, 0);
}

void alertManualFair() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(leftLight, HIGH);
    digitalWrite(rightLight, LOW);
    delay(300);
    digitalWrite(leftLight, LOW);
    digitalWrite(rightLight, HIGH);
    delay(300);
  }
  digitalWrite(leftLight, LOW);
  digitalWrite(rightLight, LOW);
}

// Turn CONTROL - LINE Follow
void Turn(bool reverse, int Left, int Middle, int Right) {
  if(Left <= 100 && Middle <= 100 && Right >= 600) { // 001
    // Right Turn
    setLeft(reverse, accelerated_Speed_small);
    setRight(reverse, decelerated_Speed_small);
  } else if(Left <= 100 && Middle >= 600 && Right <= 100) { // 010
    // Go Straight
    setLeft(reverse, base_Speed);
    setRight(reverse, base_Speed);
  } else if(Left <= 100 && Middle >= 600 && Right >= 600) { // 011
    // Right Sharp Turn
    setLeft(reverse, accelerated_Speed_big);
    setRight(reverse, decelerated_Speed_big);
  } else if(Left >= 600 && Middle <= 100 && Right <= 100) { // 100
    // Left Turn
    setLeft(reverse, decelerated_Speed_small);
    setRight(reverse, accelerated_Speed_small);
  } else if(Left >= 600 && Middle >= 600 && Right <= 100) { // 110
    // Left Sharp Turn
    setLeft(reverse, decelerated_Speed_big);
    setRight(reverse, accelerated_Speed_big);
  } else if(Left >= 600 && Middle >= 600 && Right >= 600) { // 111
    // Stop
    setLeft(reverse, 0);
    setRight(reverse, 0);
  } else {
    setLeft(reverse, 0);
    setRight(reverse, 0);
  }
}
