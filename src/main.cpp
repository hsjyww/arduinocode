#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>


constexpr uint8_t PIN_SS   = 10;   // MFRC522 SDA(SS)
constexpr uint8_t PIN_RST  = 9;    // MFRC522 RST
constexpr uint8_t PIN_RELAY = 7;   // 릴레이 IN

// 릴레이 모듈 특성: LOW에서 동작하는 경우 많음
constexpr uint8_t RELAY_ACTIVE_LEVEL   = LOW;
constexpr uint8_t RELAY_INACTIVE_LEVEL = HIGH;

MFRC522 mfrc522(PIN_SS, PIN_RST);

// 허용 카드 UID (시리얼 모니터로 확인 후 교체)
byte ALLOWED_UID[][4] = {
  { 0xA1, 0xFF, 0xAC, 0x7B }
};
const size_t NUM_UID = sizeof(ALLOWED_UID) / sizeof(ALLOWED_UID[0]);

bool relayOn = false;
unsigned long lastToggleMs = 0;
const unsigned long toggleGuardMs = 600; // 중복 방지

bool uidEquals(const byte *a, const byte *b, byte len) {
  for (byte i = 0; i < len; i++) if (a[i] != b[i]) return false;
  return true;
}

bool isAllowedUID(MFRC522::Uid uid) {
  if (uid.size != 4) return false;
  for (size_t i = 0; i < NUM_UID; i++) {
    if (uidEquals(uid.uidByte, ALLOWED_UID[i], 4)) return true;
  }
  return false;
}

void setRelay(bool on) {
  relayOn = on;
  digitalWrite(PIN_RELAY, on ? RELAY_ACTIVE_LEVEL : RELAY_INACTIVE_LEVEL);
}

void printUID(const MFRC522::Uid &uid) {
  Serial.print("UID: ");
  for (byte i = 0; i < uid.size; i++) {
    if (uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(uid.uidByte[i], HEX);
    if (i < uid.size - 1) Serial.print(":");
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(PIN_RELAY, OUTPUT);
  setRelay(false);

  Serial.println("RFID + Relay → LED Control");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  unsigned long now = millis();
  printUID(mfrc522.uid);

  if (now - lastToggleMs < toggleGuardMs) {
    Serial.println("중복 방지 대기 중...");
  } else {
    if (isAllowedUID(mfrc522.uid)) {
      setRelay(!relayOn);
      Serial.print("인증 성공 → 릴레이 ");
      Serial.println(relayOn ? "ON (LED 켜짐)" : "OFF (LED 꺼짐)");
      lastToggleMs = now;
    } else {
      Serial.println("인증 실패 → LED 변화 없음");
    }
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
