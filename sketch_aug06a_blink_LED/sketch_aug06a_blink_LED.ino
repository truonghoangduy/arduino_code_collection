
// pin 13 is the LED on-board
int RXLED = 13; // For Uno
//int RXLED = 17; // For Micro/Atmega32U4
//int RXLED = 0; // For ATTiny85
//int RXLED = 4; // For ATmega328


// put your setup code here, to run once:
void setup() {
  // init the digital pin 13th as OUTPUT
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes
  // Serial.begin(9600); //This pipes to the serial monitor
  // Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
}

// put your main code here, to run repeatedly:
void loop() {
  // output to pin_13 a HIGH voltage level
  digitalWrite(RXLED, HIGH);
  //  Serial.print("Hello from chip !");
  delay(1000);

  // output to pin_13 a LOW voltage level
  digitalWrite(RXLED, LOW);
  delay(1000);
}
