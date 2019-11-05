#include <Servo.h>

Servo servo1;
int led = 13;
  
void setup() {
  // put your setup code here, to run once:
  servo1.attach(9);
  pinMode(led, OUTPUT);
}

void blink(int times) {
  
  int i = 0;
  
  while( i < times){
    
    digitalWrite(led, HIGH);
    delay(100);

    digitalWrite(led, LOW);
    delay(100);

    i++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  servo1.write(180);
  delay(600);
  blink(2);
  
  servo1.write(-180);
  delay(1000);

  delay(3000);
}
