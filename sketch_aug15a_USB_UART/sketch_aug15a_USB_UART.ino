#include <SoftwareSerial.h>

#define BUFF_MAX 300
void setup()
{
  Serial.begin(9600, SERIAL_6E2);
  Serial1.begin(9600, SERIAL_6E2);
}
void loop()
{
  char inBuffer[BUFF_MAX];
  memset(inBuffer, 0, sizeof(inBuffer));
  Serial.print(inBuffer);
  while (Serial1.available() > 0)
  {

    //    Serial.write(Serial1.read());

    byte sizeBuffer = Serial1.readBytesUntil('\n', inBuffer, BUFF_MAX);
    Serial.print("Received:");
    Serial.write(inBuffer, 100);
    Serial.println();
  }

}
