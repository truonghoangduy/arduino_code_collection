// Relay Order :
//
// GND
// 5V
// Signal D10
//
// With the Text reversed vertically.
#include <Arduino.h>

int relay = 6; // at D10
int led = 13;   // at D13

void setup() {
  // output like LED
  pinMode(relay, OUTPUT);
  // actual LED
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (relay, HIGH);
  digitalWrite (led, LOW);
  delay(2000);

  digitalWrite(led, HIGH);
  digitalWrite(relay, LOW);
  delay(2000);

}
