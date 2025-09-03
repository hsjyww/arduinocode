#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Serial Monitor Ready");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();      // 섭씨
  if (isnan(h) || isnan(t)) {
    Serial.println("센서 읽기 실패. 배선/전원/풀업 저항 확인");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h, 1);
    Serial.print(" %  |  Temp: ");
    Serial.print(t, 1);
    Serial.println(" C");
  }
  delay(2000);
}
