<div align="center">
  <h1>Lab3 - Car Drive</h1>
</div>

## 1. 实现小车**前进/后退**

### 实验过程：
1. 按照如下图示接线:
<p align="center">
  ***actual***
  <br>
  <img src="./Photos/actual/car_above.JPG" alt="car_above.JPG" height="300">
  <img src="./Photos/actual/car_bottom.JPG" alt="car_bottom.JPG" height="300">
  <br>
  ***JLC***
  <br>
  <img src="./Photos/JLC/carDrive.png" alt="carDrive.png" height="300">
</p>

2. Arduino IDE代码:
```cpp {.line-numbers}
/* 四引脚 mode */
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;

int leftSpeed = 255;
int rightSpeed = 255;

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
  boolean reverse = 0;
  setLeft(reverse, leftSpeed);
  setRight(reverse, rightSpeed);
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
```

## 2. 实现小车**寻光**行驶

### 实验过程：
1. 按照如下图示接线:
<p align="center">
  ***actual***
  <br>
  <img src="./Photos/actual/car_face_ldr.JPG" alt="car_face_ldr.JPG" height="300">
  <img src="./Photos/actual/car_above_ldr.JPG" alt="car_above_ldr.JPG" height="300">
  <br>
  ***JLC***
  <br>
  <img src="./Photos/JLC/lightToward.png" alt="" height="300">
</p>

2. Arduino IDE代码:
```c++ {.line-numbers}
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
```