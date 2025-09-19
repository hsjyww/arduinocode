#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int pirPin = 2;
int motionCount = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(pirPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("PIR Motion Log");
  delay(1000);
  lcd.clear();
}

void loop() {
  int pirState = digitalRead(pirPin);

  if (pirState == HIGH) {
    motionCount++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Motion Detected!");
    lcd.setCursor(0,1);
    lcd.print("Count: ");
    lcd.print(motionCount);
    delay(2000);
  }
}
