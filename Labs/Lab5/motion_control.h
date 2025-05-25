#ifndef MotionControl_H
#define MotionControl_H

#include <Arduino.h>

#define BORDER_VALUE 0.2
#define TREND_THRESHOLD 3           // 连续多少帧趋势才有效
#define LOST_INTERVAL 100           // ms，断线后动作尝试间隔

int baseSpeed = 90;
int sharp_turnSpeed = 200;
int subtle_turnSpeed = 75;
int maxStraightSpeed = 150;

bool reverse = false;

enum Direction {
  DIR_STRAIGHT,
  DIR_LEFT,
  DIR_RIGHT
};

Direction lastDirection = DIR_STRAIGHT;
int leftTrendCount = 0;
int rightTrendCount = 0;
unsigned long lastLostTime = 0;  // 断线状态上一次处理时间戳

// 编码状态：左中右三位 -> 3bit 编码
uint8_t encodeSensorStatus(bool left, bool middle, bool right) {
  return (left << 2) | (middle << 1) | right;
}

// 趋势统计更新（缓慢衰减版）
void updateTrend(uint8_t status) {
  if (status == 0b100 || status == 0b110) {          // 偏左
    leftTrendCount++;
    rightTrendCount = max(0, rightTrendCount - 1);
  } else if (status == 0b001 || status == 0b011) {   // 偏右
    rightTrendCount++;
    leftTrendCount = max(0, leftTrendCount - 1);
  } else {
    // 无明显趋势时缓慢衰减
    leftTrendCount = max(0, leftTrendCount - 1);
    rightTrendCount = max(0, rightTrendCount - 1);
  }
}

void carDrive(float leftStatus, float middleStatus, float rightStatus) {
  bool leftOn = (leftStatus >= BORDER_VALUE);
  bool middleOn = (middleStatus >= BORDER_VALUE);
  bool rightOn = (rightStatus >= BORDER_VALUE);

  uint8_t status = encodeSensorStatus(leftOn, middleOn, rightOn);

  // === 优先判断：直角转弯 ===
  if (status == 0b011) {
    turnRight(reverse, sharp_turnSpeed);
    lastDirection = DIR_RIGHT;
    leftTrendCount = 0;
    rightTrendCount = 0;
    return;
  }
  if (status == 0b110) {
    turnLeft(reverse, sharp_turnSpeed);
    lastDirection = DIR_LEFT;
    leftTrendCount = 0;
    rightTrendCount = 0;
    return;
  }

  // === 更新偏移趋势 ===
  updateTrend(status);

  // === 判断是否居中且稳定，可提速 ===
  bool centeredAndStable =
    (status == 0b010 || status == 0b111) &&
    leftTrendCount < TREND_THRESHOLD &&
    rightTrendCount < TREND_THRESHOLD;

  int currentSpeed = centeredAndStable ? min(baseSpeed + 30, maxStraightSpeed) : baseSpeed;

  // === 主控制逻辑 ===
  switch (status) {
    case 0b001: // 微右
      turnRight(reverse, subtle_turnSpeed);
      lastDirection = DIR_RIGHT;
      break;

    case 0b100: // 微左
      turnLeft(reverse, subtle_turnSpeed);
      lastDirection = DIR_LEFT;
      break;

    case 0b010: // 正中
    case 0b111: // 全中，冗余稳态
      goStraight(reverse, currentSpeed);
      lastDirection = DIR_STRAIGHT;
      break;

    case 0b101: // 左右都有线，中间丢失（十字或分叉）
      if (lastDirection == DIR_LEFT) {
        turnLeft(reverse, subtle_turnSpeed);
      } else if (lastDirection == DIR_RIGHT) {
        turnRight(reverse, subtle_turnSpeed);
      } else {
        goStraight(reverse, baseSpeed / 2); // 慢速探测
      }
      break;

    case 0b000: { // 全部丢失，参考趋势 + 限制频率
      unsigned long now = millis();
      if (now - lastLostTime >= LOST_INTERVAL) {
        lastLostTime = now;

        if (leftTrendCount >= TREND_THRESHOLD) {
          turnLeft(reverse, subtle_turnSpeed);
          lastDirection = DIR_LEFT;
        } else if (rightTrendCount >= TREND_THRESHOLD) {
          turnRight(reverse, subtle_turnSpeed);
          lastDirection = DIR_RIGHT;
        } else {
          // 不确定方向，使用历史方向作为参考
          if (lastDirection == DIR_LEFT) {
            turnLeft(reverse, subtle_turnSpeed);
          } else if (lastDirection == DIR_RIGHT) {
            turnRight(reverse, subtle_turnSpeed);
          } else {
            goStraight(reverse, baseSpeed);
          }
        }
      }
      break;
    }

    default:
      goStraight(reverse, baseSpeed);
      lastDirection = DIR_STRAIGHT;
      break;
  }
}

#endif