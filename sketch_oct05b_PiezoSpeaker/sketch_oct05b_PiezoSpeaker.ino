#define SOUND_PIN 13

void setup() {
  // put your setup code here, to run once:
  pinMode(SOUND_PIN,OUTPUT);
  digitalWrite(SOUND_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SOUND_PIN,HIGH);
  delay(100);
  digitalWrite(SOUND_PIN,LOW);
  delay(2000);
}
