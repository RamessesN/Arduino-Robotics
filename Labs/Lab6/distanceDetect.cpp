#include <Servo.h>
Servo engine;

// steering gear
int enginePin = 3;

// ultrasonic sensor
int ultrasound_TrigPin = 10;
int ultrasound_EchoPin = 11;

int counter = 0;
int angle = 45;
int step = 1;
unsigned long previousMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Engine Driver
  engine.attach(enginePin);
  engine.write(angle);
  // Ultrasound Driver
  pinMode(ultrasound_TrigPin, OUTPUT);
  pinMode(ultrasound_EchoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(counter < 2) {
    engineTurn();
  } else if(engine.attached()) {
    engine.detach();
    Serial.println("STOP!!!");
  }
}

void engineTurn() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= 20) {
    previousMillis = currentMillis;

    engine.write(angle);

    if(angle % 5 <= 1) {
      ultrasoundControl();
    }

    angle += step;

    // Change the direction when arrive the boundary
    if(angle > 135) {
      angle = 135;
      step = -step;
      counter++;
    } else if(angle < 45) {
      angle = 45;
      step = -step;
      counter++;
    }
  }
}

float duration, distance;

void ultrasoundControl() {
  digitalWrite(ultrasound_TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasound_TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasound_TrigPin, LOW);

  duration = pulseIn(ultrasound_EchoPin, HIGH);
  distance = (duration * 0.0343) / 2;

  if(distance < 2 || distance > 400) {
    distance = 0;
  }

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("°; Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}