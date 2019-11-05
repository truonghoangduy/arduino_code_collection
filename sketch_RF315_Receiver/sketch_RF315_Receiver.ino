// RF315 Receiver
// using VirtualWire Library
//..................................
#include <VirtualWire.h>  // Radio Signal Library
#include <JeeLib.h>       // Low power functions library

#define HEART_BEAT 13  // A2 on Tiny85 as Heart LED
#define SOUND_BEAT 11  // A1 on Tiny85 as Speaker
#define DATA_PIN 12    // 1 as Data Pin on Tiny85

#define RF_CODE 6   // Currently using number
#define HEART_RATE 2000// Milli-seconds to drop
#define WARNING_RATE 30// Seconds to sleep after warning
#define VOLTAGE_MIN 3.0// will be ~3.0V for lithium
#define VOLTAGE_WARN 3.1// will be ~3.1V for lithium

ISR(WDT_vect) {
  Sleepy::watchdogEvent();  // Setup the watchdog
}

void blink_for(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(HEART_BEAT, HIGH);// INDICATE ALIVE
    delay(150 / times);
    digitalWrite(HEART_BEAT, LOW);// INDICATE ALIVE
    delay(250 / times);
  }
}

void setup()
{
  pinMode(HEART_BEAT, OUTPUT);// HEART LED BEAT
  pinMode(SOUND_BEAT, OUTPUT);// SPEAKER BEAT
  pinMode(DATA_PIN, INPUT);   // GET DATA 

//  digitalWrite(SOUND_BEAT, HIGH); // TEST SOUND
//  delay(100);
//  digitalWrite(SOUND_BEAT, LOW); 
  
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_set_rx_pin(DATA_PIN);    // DATA PIN as 12 on Uno
  vw_setup(4000);             // Config Speed : Bits per sec


  blink_for(4);         // Blinking...
//  Serial.begin(9600); // debug
//  Serial.println("Serial ready.");

  vw_rx_start(); // Start the receiver PLL running
}


void loop()
{
  //check_voltage();  // check current power.

//  digitalWrite(HEART_BEAT, LOW);// INDICATE END
  
  listen_signal();  // check on signal...
  
  delay(500);
  
  listen_signal();  // check on signal...
  
//  digitalWrite(HEART_BEAT, HIGH);// INDICATE START

  delay(1000);
  
      
//  listen_signal();  // check on signal...
//  delay(500);

  
//  deep_sleep(HEART_RATE); // fall asleep again.
}

void deep_sleep(int timing) {
  Sleepy::loseSomeTime(timing);
}

void pulse_sound() {
  digitalWrite(SOUND_BEAT, HIGH);
  delay(500);
  digitalWrite(SOUND_BEAT, LOW);
}
void pulse_sound(int times){
  for(int i = 0; i< times; i++){
    pulse_sound();
    delay(250);
  }
}

void listen_signal() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))   // Non-blocking
  {
    String message = (char*)buf;      // Convert buffer->string

    if (message.toInt() == RF_CODE) {          // Check data
      pulse_sound(2);
      blink_for(4);
//      Serial.println("Got your bike here !");
    }
//    else Serial.println("[" + message + "]");     // Debug
  }
  else blink_for(1);     // IT's ALIVE !
}

void check_voltage() {
  // Get voltage from A2 Pin
  float voltage = analogRead(1)/100.0;
  
  if(voltage < VOLTAGE_MIN){
//    Serial.println("Low power...deep sleep now.");
    blink_for(5);    
//    pulse_sound(2);
//    delay(500);
    deep_sleep(WARNING_RATE*60*1000);// SLEEP FOR WARNING Minutes
  }
  else if(voltage < VOLTAGE_WARN){
    
    blink_for(3);                 // To alert and to be found faster.
//    Serial.println("Almost Low power...");
  }
//  Serial.println (String(voltage) + " V");
}
