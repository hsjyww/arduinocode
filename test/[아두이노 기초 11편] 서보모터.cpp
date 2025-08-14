#include <Arduino.h>
#include <Servo.h>

const int servoPin = 9;  // 서보모터 신호선 → D9
const int buttonPin = 2; // 버튼 입력 → D2

Servo myServo;

int angle = 0;
bool lastButtonState = LOW;
bool currentButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup()
{
    myServo.attach(servoPin);
    pinMode(buttonPin, INPUT_PULLUP); // 버튼은 풀업 사용
    myServo.write(angle);
    Serial.begin(9600);
}

void loop()
{
    bool reading = digitalRead(buttonPin);

    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != currentButtonState)
        {
            currentButtonState = reading;

            if (currentButtonState == LOW)
            { // 버튼 눌렸을 때
                angle += 90;
                if (angle > 180)
                    angle = 0;

                myServo.write(angle);
                Serial.print("서보 각도: ");
                Serial.println(angle);
            }
        }
    }

    lastButtonState = reading;
}
// © 2025 hsjyww. All rights reserved.
// 본 코드는 hsjyww가 제작한 아두이노 실습 예제입니다.
// 무단 복제 및 배포를 금합니다.
// 출처: https://github.com/hsjyww/arduinocode
