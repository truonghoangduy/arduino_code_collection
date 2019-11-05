// RF315 Transmitter
// using VirtualWire Library
//..................................
#include <VirtualWire.h>  // Radio Signal Library
#include <JeeLib.h>       // Low power functions library

#define HEART_BEAT A2  // A2 on Tiny85 as Heart LED
#define DATA_PIN A1    // A1 or 1 as Data Pin on Tiny85

#define MESSAGE "6" // CODE 

#define VOLTAGE_MIN 3.0// will be ~3.0V for lithium
#define VOLTAGE_WARN 3.2// will be ~3.1V for lithium

ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup the watchdog

char *controller;

void setup() {
                              // PIN CONFIG :
  pinMode(HEART_BEAT, OUTPUT);        // A2: for signal indicator
//  pinMode(DATA_PIN,   OUTPUT);        // A1:  for signal output
  
  vw_set_ptt_inverted(true);  
  
  vw_set_tx_pin(DATA_PIN);    // for data transmission
  vw_setup(4000);             // speed of data transfer Kbps
}

void loop() {

  check_voltage();                      // JUST WARN ME ABOUT BATTERY
  
  digitalWrite(HEART_BEAT, HIGH);       // START TRANSMISSION...
  
  send_message();
  delay(500);   
  send_message();
  delay(500);                           // WAIT FOR 250ms
  
  digitalWrite(HEART_BEAT, LOW);        // END OF TRANSMISSION.
  
//  deep_sleep(1000);                     // SLEEP FOR 1 SECOND.

}

void send_message(){
  controller = MESSAGE ;                 // MESSAGE
  vw_send((uint8_t *)controller, 
            strlen(controller));        // SENDING....
  vw_wait_tx();                         // WAIT FOR IDLE..
}

void deep_sleep(int timing){
 Sleepy::loseSomeTime(timing);
}

void blink_for(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(HEART_BEAT, HIGH);// INDICATE ALIVE
    delay(150 / times);
    digitalWrite(HEART_BEAT, LOW);// INDICATE ALIVE
    delay(250 / times);
  }
}

void check_voltage() {
  float voltage = analogRead(A2)/100.0;
  if(voltage < VOLTAGE_MIN){
    blink_for(6);
  }
  else if(voltage < VOLTAGE_WARN){
    blink_for(3);
  }
}
