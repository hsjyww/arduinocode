#include <Arduino.h>
int led=9,x=A0,y=A1,b,s;
void setup(){pinMode(led,OUTPUT);}
void loop(){
  int xv=analogRead(x),yv=analogRead(y);
  
  // 가운데
  if(abs(xv-512)<50 && abs(yv-512)<50){analogWrite(led,0);return;}
  
  // 위아래 밝기 조절 (깜빡임 없음)
  if(abs(xv-512)<50){b=map(yv,0,1023,0,255);analogWrite(led,b);delay(50);return;}
  
  // 좌우 속도 조절 (깜빡임)
  s=map(xv,0,1023,700,30);
  b=map(yv,0,1023,0,255);
  analogWrite(led,b);delay(s);
  analogWrite(led,0);delay(s);
}
