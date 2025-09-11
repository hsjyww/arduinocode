// 아두이노 기초 29편: 조이스틱 + 8채널 릴레이(4채널 사용) 방향별 제어
// 릴레이 보드 Active-LOW(LOW=ON) 기준. HIGH=ON 보드면 RELAY_ON/RELAY_OFF를 바꾸세요.
#include <Arduino.h>
const int JOY_X = A1;      // 좌우
const int JOY_Y = A0;      // 상하

const int RELAY_UP    = 2; // IN1
const int RELAY_DOWN  = 3; // IN2
const int RELAY_LEFT  = 4; // IN3
const int RELAY_RIGHT = 5; // IN4

const int RELAY_ON  = LOW;   // Active-LOW
const int RELAY_OFF = HIGH;

// 방향 임계값(데드존 포함)
const int TH_LOW  = 300;
const int TH_HIGH = 700;

inline void allRelays(int state) {
  digitalWrite(RELAY_UP, state);
  digitalWrite(RELAY_DOWN, state);
  digitalWrite(RELAY_LEFT, state);
  digitalWrite(RELAY_RIGHT, state);
}

void setup() {
  pinMode(RELAY_UP, OUTPUT);
  pinMode(RELAY_DOWN, OUTPUT);
  pinMode(RELAY_LEFT, OUTPUT);
  pinMode(RELAY_RIGHT, OUTPUT);
  allRelays(RELAY_OFF);
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  allRelays(RELAY_OFF);

  // 상/하 우선 → 좌/우 (동시 입력 흔들림 억제)
  if (y < TH_LOW) {
    digitalWrite(RELAY_UP, RELAY_ON);
    Serial.println("UP");
  } else if (y > TH_HIGH) {
    digitalWrite(RELAY_DOWN, RELAY_ON);
    Serial.println("DOWN");
  } else if (x < TH_LOW) {
    digitalWrite(RELAY_LEFT, RELAY_ON);
    Serial.println("LEFT");
  } else if (x > TH_HIGH) {
    digitalWrite(RELAY_RIGHT, RELAY_ON);
    Serial.println("RIGHT");
  } else {
    Serial.println("CENTER");
  }

  delay(60);
}
