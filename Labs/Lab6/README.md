<div align="center">
    <h1>Lab6 - Ultrasonic Distance Detection</h1>
</div>

## HC-SR04 超声波测距搭配 SG90 舵机使用测量的雷达图
### 1. 原理 
1. HC-SR04 超声波测距原理:  
详见 [# HC-SR04 超声波测距](https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1)
2. SG90 舵机原理:  
详见 [# SG90 舵机](https://blog.csdn.net/weixin_42645653/article/details/112210095)

### 2. 实验过程
### 3. 实物图
<p align="center">
  <img src="./Photos/actual/front.jpg" alt="front.jpg" height="250">
  <img src="./Photos/actual/above.jpg" alt="above.jpg" height="250">
</p>

### 4. 电路图
<p align="center">
  <img src="./Photos/jlc/jlc.png" alt="jlc.png" height="300">
</p>

### 5. 测量数据
- 0cm: [
Angle: 90°; Distance: 2.44 cm
Angle: 91°; Distance: 2.44 cm
Angle: 92°; Distance: 3.74 cm
Angle: 93°; Distance: 0.00 cm
Angle: 94°; Distance: 0.00 cm
Angle: 95°; Distance: 0.00 cm
Angle: 96°; Distance: 0.00 cm
Angle: 97°; Distance: 0.00 cm
Angle: 98°; Distance: 0.00 cm
Angle: 99°; Distance: 0.00 cm
Angle: 100°; Distance: 0.00 cm
Angle: 101°; Distance: 0.00 cm
Angle: 102°; Distance: 0.00 cm
Angle: 103°; Distance: 0.00 cm
Angle: 104°; Distance: 0.00 cm
Angle: 105°; Distance: 0.00 cm
Angle: 106°; Distance: 0.00 cm
Angle: 107°; Distance: 0.00 cm
Angle: 108°; Distance: 0.00 cm
Angle: 109°; Distance: 0.00 cm
Angle: 110°; Distance: 0.00 cm
Angle: 111°; Distance: 0.00 cm
Angle: 112°; Distance: 0.00 cm
Angle: 113°; Distance: 0.00 cm
Angle: 114°; Distance: 0.00 cm
Angle: 115°; Distance: 0.00 cm
Angle: 116°; Distance: 0.00 cm
Angle: 117°; Distance: 0.00 cm
Angle: 118°; Distance: 0.00 cm
Angle: 119°; Distance: 0.00 cm
Angle: 120°; Distance: 0.00 cm
Angle: 121°; Distance: 0.00 cm
Angle: 122°; Distance: 0.00 cm
Angle: 123°; Distance: 0.00 cm
Angle: 124°; Distance: 0.00 cm
Angle: 125°; Distance: 0.00 cm
Angle: 126°; Distance: 0.00 cm
Angle: 127°; Distance: 0.00 cm
Angle: 128°; Distance: 0.00 cm
Angle: 129°; Distance: 0.00 cm
Angle: 130°; Distance: 0.00 cm
Angle: 131°; Distance: 0.00 cm
Angle: 132°; Distance: 0.00 cm
Angle: 133°; Distance: 0.00 cm
Angle: 134°; Distance: 0.00 cm
Angle: 135°; Distance: 4.39 cm
Angle: 134°; Distance: 16.43 cm
Angle: 133°; Distance: 16.43 cm
Angle: 132°; Distance: 16.43 cm
Angle: 131°; Distance: 16.43 cm
Angle: 130°; Distance: 4.39 cm
Angle: 129°; Distance: 5.92 cm
Angle: 128°; Distance: 4.72 cm
Angle: 127°; Distance: 4.61 cm
Angle: 126°; Distance: 8.95 cm
Angle: 125°; Distance: 3.31 cm
Angle: 124°; Distance: 27.20 cm
Angle: 123°; Distance: 23.02 cm
Angle: 122°; Distance: 6.35 cm
Angle: 121°; Distance: 3.64 cm
Angle: 120°; Distance: 3.74 cm
Angle: 119°; Distance: 3.74 cm
Angle: 118°; Distance: 60.87 cm
Angle: 117°; Distance: 3.74 cm
Angle: 116°; Distance: 3.74 cm
Angle: 115°; Distance: 3.74 cm
Angle: 114°; Distance: 49.60 cm
Angle: 113°; Distance: 49.60 cm
Angle: 112°; Distance: 2.76 cm
Angle: 111°; Distance: 2.76 cm
Angle: 110°; Distance: 2.76 cm
Angle: 109°; Distance: 2.76 cm
Angle: 108°; Distance: 9.57 cm
Angle: 107°; Distance: 0.00 cm
Angle: 106°; Distance: 0.00 cm
Angle: 105°; Distance: 0.00 cm
Angle: 104°; Distance: 0.00 cm
Angle: 103°; Distance: 0.00 cm
Angle: 102°; Distance: 0.00 cm
Angle: 101°; Distance: 0.00 cm
Angle: 100°; Distance: 0.00 cm
Angle: 99°; Distance: 0.00 cm
Angle: 98°; Distance: 0.00 cm
Angle: 97°; Distance: 0.00 cm
Angle: 96°; Distance: 0.00 cm
Angle: 95°; Distance: 0.00 cm
Angle: 94°; Distance: 0.00 cm
Angle: 93°; Distance: 0.00 cm
Angle: 92°; Distance: 0.00 cm
Angle: 91°; Distance: 0.00 cm
Angle: 90°; Distance: 0.00 cm
  ]
- 40cm:
- 80cm:
- 120cm:
- 160cm:
- 200cm:
- 240cm:
- 280cm:
- 320cm:
- 360cm:
- 400cm:

### 6. “距离 - 角度” 扇形雷达图
### 7. 附录: 代码
```cpp {.line-numbers}
#include <Servo.h>
Servo engine;

// steering gear
int enginePin = 3;

// ultrasonic sensor
int ultrasound_TrigPin = 10;
int ultrasound_EchoPin = 11;

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Engine Driver
  engine.attach(enginePin);
  // Ultrasound Driver
  pinMode(ultrasound_TrigPin, OUTPUT);
  pinMode(ultrasound_EchoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(counter < 6) {
    engineTurn();
  } else if(engine.attached()) {
    engine.detach();
    Serial.println("STOP!!!");
  }
}

int angle = 90;
int step = 1;
unsigned long previousMillis = 0;

void engineTurn() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= 20) {
    previousMillis = currentMillis;

    engine.write(angle);

    ultrasoundControl();

    angle += step;

    // Change the direction when arrive the boundary
    if(angle >= 135) {
      angle = 135;
      step = -step;
      counter++;
    } else if(angle <= 45) {
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

  duration = pulseIn(ultrasound_EchoPin, HIGH, 25000);
  distance = (duration * 0.0343) / 2;

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("°; Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
```