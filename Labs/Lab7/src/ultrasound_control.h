#ifndef Ultrasound_h
#define Ultrasound_h

int trigPin = 3;
int echoPin = 11;

float duration;

float distanceDetect() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2;

  return distance;
}

#endif