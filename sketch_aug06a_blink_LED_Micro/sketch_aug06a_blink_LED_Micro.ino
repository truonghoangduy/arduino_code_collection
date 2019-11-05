
// pin 13 is the LED on-board
int RXLED = 17;

// put your setup code here, to run once:
void setup() {
  // init the digital pin 13th as OUTPUT
pinMode(RXLED, OUTPUT);  // Set RX LED as an output
 // TX LED is set as an output behind the scenes

 Serial.begin(9600); //This pipes to the serial monitor
 Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
}

// put your main code here, to run repeatedly:  
void loop() {
  // output to pin_13 a HIGH voltage level
  digitalWrite(RXLED, HIGH);
  delay(1000);
  
  // output to pin_13 a LOW voltage level
  digitalWrite(RXLED, LOW);
  delay(1000);
}
