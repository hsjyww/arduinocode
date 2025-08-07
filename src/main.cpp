#include <Arduino.h>
#include <IRremote.h> // IR 리모컨용 라이브러리

const int RECV_PIN = 11; // 적외선 수신기 신호핀
const int LED_PIN = 7;   // LED 연결 핀

IRrecv irrecv(RECV_PIN); // 수신기 객체 생성
decode_results results;  // 수신된 결과 저장

void setup()
{
  Serial.begin(9600);       // 시리얼 모니터 시작
  irrecv.enableIRIn();      // 리모컨 수신기 작동 시작
  pinMode(LED_PIN, OUTPUT); // LED 출력 핀 설정
}

void loop()
{
  if (irrecv.decode(&results))
  {                                     // 신호가 들어오면
    Serial.println(results.value, HEX); // 어떤 버튼인지 코드 출력

    if (results.value == 0xFFA25D)
    {                                               // 예: 전원 버튼
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // 현재 상태 반전
    }

    irrecv.resume(); // 다음 신호 받을 준비
  }
  == == == =

               const int joyX = A0;
  const int joyY = A1;
  const int swPin = 2;
  const int ledPin = 9;

  bool blinkMode = false;  // 깜빡이기 모드 on/off
  bool lastSwState = HIGH; // 이전 SW 상태 저장용
  unsigned long lastBlinkTime = 0;

  void setup()
  {
    Serial.begin(9600);
    pinMode(joyX, INPUT);
    pinMode(joyY, INPUT);
    pinMode(swPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
  }

  void loop()
  {
    int xVal = analogRead(joyX);
    int yVal = analogRead(joyY);
    int swState = digitalRead(swPin);

    // 밝기 설정 (X축 → 0~255)
    int pwmValue = map(xVal, 0, 1023, 0, 255);
    int blinkDelay = map(yVal, 0, 1023, 50, 1000); // Y축으로 깜빡이기 속도 조절

    // SW 눌림 체크 → 토글
    if (swState == LOW && lastSwState == HIGH)
    {
      blinkMode = !blinkMode;
      Serial.println(blinkMode ? "깜빡이기 모드 ON" : "깜빡이기 모드 OFF");
      delay(200); // 채터링 방지
    }
    lastSwState = swState;

    if (blinkMode)
    {
      unsigned long now = millis();
      if (now - lastBlinkTime >= blinkDelay)
      {
        static bool ledState = false;
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);
        lastBlinkTime = now;
      }
    }
    else
    {
      analogWrite(ledPin, pwmValue); // 깜빡이기 모드 아닐 땐 밝기 고정
    }

    // 시리얼 출력
    Serial.print("X: ");
    Serial.print(xVal);
    Serial.print(" | Y: ");
    Serial.print(yVal);
    Serial.print(" | SW: ");
    Serial.print(swState == LOW ? "눌림" : "안눌림");
    Serial.print(" | BlinkMode: ");
    Serial.println(blinkMode ? "ON" : "OFF");

    delay(10);
>>>>>>> a09d25872bea3ea072ac82a601c8f6d6a412ea15
  }
