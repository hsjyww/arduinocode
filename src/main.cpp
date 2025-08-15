#include <Arduino.h>
int leds[]={2,3,4}; // LED 핀 번호
int cnt=3;

void setup(){
  for(int i=0;i<cnt;i++) pinMode(leds[i],OUTPUT);
}

void loop(){
  for(int i=0;i<cnt;i++){
    digitalWrite(leds[i],HIGH);
    delay(200);
    digitalWrite(leds[i],LOW);
  }
  for(int i=cnt-1;i>=0;i--){
    digitalWrite(leds[i],HIGH);
    delay(200);
    digitalWrite(leds[i],LOW);
  }
}
