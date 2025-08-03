#include <Arduino.h>  

int pirPin = 2;     // PIR 센서 OUT 핀 → D2
int ledPin = 3;     // LED → D3

void setup() {
  pinMode(pirPin, INPUT);     // PIR은 입력으로 설정
  pinMode(ledPin, OUTPUT);    // LED는 출력으로 설정
  Serial.begin(9600);         // 시리얼 모니터 속도 설정
}

void loop() {
  int motion = digitalRead(pirPin);  // PIR 신호 읽기

  if (motion == HIGH) {
    digitalWrite(ledPin, HIGH);      // 감지되면 LED 켜기
    Serial.println("사람 감지됨!");
  } else {
    digitalWrite(ledPin, LOW);       // 감지 없으면 LED 끄기
    Serial.println("감지 없음");
  }

  delay(500);  // 0.5초 대기
}
