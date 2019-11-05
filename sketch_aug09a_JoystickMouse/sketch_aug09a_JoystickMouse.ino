#include<Mouse.h>

// Pins
const int PIN_HOZ = A2;
const int PIN_VER = A3;
const int PIN_SEL = 9;

// pin 13 is the LED on-board
const int RXLED = 17;

// Values
const int MIN_HOLD = 750;
const int MAX_LOOP = 500;
const int SENSITIVITY = 150;

// vars
bool mouse_click = false;
int v0, h0, s0, v, h, s;
int counter, click_counter, holding_counter = 0;

void setup() {

  Serial.begin(57600);
  pinMode(PIN_HOZ, INPUT);
  pinMode(PIN_VER, INPUT);
  pinMode(PIN_SEL, INPUT);
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output

  digitalWrite(PIN_SEL, HIGH);
  delay(1000);
  v0 = analogRead(PIN_VER);
  h0 = analogRead(PIN_HOZ);
}

void loop() {

  v = analogRead(PIN_VER) - v0;
  h = analogRead(PIN_HOZ) - h0;

  if (v != 0)  Mouse.move(0, v / SENSITIVITY, 0);
  if (h != 0)  Mouse.move((h / SENSITIVITY) * -1, 0, 0);

  // HOLDING ...
  if (mouse_click) holding_counter++;

  if (counter < MAX_LOOP) counter ++;
  else counter = click_counter = 0;

  if (digitalRead(PIN_SEL) == 0 && !mouse_click) {
    press_mouse();
  }
  else if (digitalRead(PIN_SEL) && mouse_click) {
    release_mouse();
  }

  debug_log();
}

void press_mouse() {
  // CLICKED !
  mouse_click = true;

  if (click_counter == 0 && holding_counter < MIN_HOLD) 
  {
    digitalWrite(RXLED, HIGH);
    click_counter ++;
    Mouse.press(MOUSE_LEFT);
    Serial.println("SINGLE CLICKED");
  }
  else 
  {
    counter = MAX_LOOP;
    Mouse.press(MOUSE_RIGHT);
    Serial.println("RIGHT CLICKED");
  }
  
  holding_counter = 0;
}

void release_mouse() {
  mouse_click = false;
  Mouse.release(MOUSE_LEFT);
  Mouse.release(MOUSE_RIGHT);
  Serial.println("RELEASED");
  digitalWrite(RXLED, LOW);
}

void debug_log() {
  Serial.print("Vertical :" + String(v));
  Serial.print(" | Horizontal :" + String(h));
  Serial.print(" | Click :" + String(click_counter)  +  " => " + String(mouse_click));
  Serial.print(" | Holding : " + String(holding_counter));
  Serial.println("");
}
