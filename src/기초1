#include <Arduino.h>
// 핀 설정
int latchPin = 8;  // ST_CP
int clockPin = 12; // SH_CP
int dataPin = 11;  // DS

void setup()
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void loop()
{
    // LED가 하나씩 오른쪽으로 이동하며 켜지는 애니메이션
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);                   // 래치 클럭 LOW
        shiftOut(dataPin, clockPin, MSBFIRST, 1 << i); // i번째 비트만 1
        digitalWrite(latchPin, HIGH);                  // 래치 클럭 HIGH (출력 갱신)
        delay(200);
    }
}
