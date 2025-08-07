#include <Arduino.h>
#include <IRremote.h>  // IR 리모컨용 라이브러리

const int RECV_PIN = 11;  // 적외선 수신기 신호핀
const int LED_PIN = 7;    // LED 연결 핀

IRrecv irrecv(RECV_PIN);  // 수신기 객체 생성
decode_results results;   // 수신된 결과 저장

void setup() {
  Serial.begin(9600);       // 시리얼 모니터 시작
  irrecv.enableIRIn();      // 리모컨 수신기 작동 시작
  pinMode(LED_PIN, OUTPUT); // LED 출력 핀 설정
}

void loop() {
  if (irrecv.decode(&results)) {                 // 신호가 들어오면
    Serial.println(results.value, HEX);          // 어떤 버튼인지 코드 출력

    if (results.value == 0xFFA25D) {             // 예: 전원 버튼
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // 현재 상태 반전
    }

    irrecv.resume(); // 다음 신호 받을 준비
  }
}
