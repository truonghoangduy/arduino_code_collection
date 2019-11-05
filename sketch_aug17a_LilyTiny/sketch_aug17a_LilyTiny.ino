// INSTALL 
//
// For LilyTiny, add to Board Manager :
// http://digistump.com/package_digistump_index.json
// 
// Then choose "Digipark Default 16.5Mhz.
//
// 1. Click on "Upload" >> Then Plug-in the board.

// P4 
int LED = 4;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(1000);

  digitalWrite(LED, LOW);
  delay(1000);
}
