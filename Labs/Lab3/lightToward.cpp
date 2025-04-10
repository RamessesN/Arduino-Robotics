/* 四引脚 mode */
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;

boolean reverse = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue_LEFT = analogRead(A5);
  int sensorValue_RIGHT = analogRead(A0);
  int GAP = abs(sensorValue_LEFT - sensorValue_RIGHT);

  Serial.print("LEFT: ");
  Serial.print(sensorValue_LEFT);
  Serial.print("\t RIGHT: ");
  Serial.print(sensorValue_RIGHT);
  Serial.print("\t GAP: ");
  Serial.println(GAP);

  Turn(reverse, sensorValue_LEFT, sensorValue_RIGHT, GAP);

  delay(100);
}

// Left Wheel CONTROL
void setLeft(boolean reverse, int speed) {
  analogWrite(in1Pin, !reverse ? speed : 0);
  analogWrite(in2Pin, reverse ? speed : 0);
}

// Right Wheel CONTROL
void setRight(boolean reverse, int speed) {
  analogWrite(in3Pin, !reverse ? speed : 0);
  analogWrite(in4Pin, reverse ? speed : 0);
}

// Whole car CONTROL - LIGHT Driving
void Turn(boolean reverse, int Left, int Right, int Gap) {
  if(Gap >= 70) {
    // Turn LEFT
    if(Left < Right) {
      setLeft(!reverse, 155);
      setRight(reverse, 255);
    }
    // Turn RIGHT
    if(Right < Left) {
      setLeft(reverse, 255);
      setRight(reverse, 155);
    }
  } else {
    // Go FORWARD
    setLeft(reverse, 155);
    setRight(reverse, 155);
  }
}