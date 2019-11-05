
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // Really important, ours is FC16
#define MAX_DEVICES 4
#define DATA_PIN  12
#define CS_PIN    11
#define CLK_PIN   10

// Turn on debug statements to the serial output
#define DEBUG 1

#if DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

// SOFTWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


uint8_t scrollSpeed = 25;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
bool newMessageAvailable = true;


void readSerial(void)
{
  static char *cp = newMessage;

  while (Serial.available())
  {
    *cp = (char)Serial.read();
    if ((*cp == '\n') || (cp - newMessage >= BUF_SIZE - 2)) // end of message character or full buffer
    {
      *cp = '\0'; // end the string
      // restart the index for next filling spree and flag we have a message waiting
      cp = newMessage;
      newMessageAvailable = true;
    }
    else  // move char pointer to next position
      cp++;
  }
}

void setup()
{
  #if DEBUG
  Serial.begin(57600);
  Serial.print("\n[Parola Scrolling Display]\nType a message for the scrolling display\nEnd message line with a newline");
  #endif
  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void loop()
{
#if USE_UI_CONTROL
  doUI();
#endif // USE_UI_CONTROL

  if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
      #if DEBUG
      Serial.print("\n\n=> ");
      Serial.print(newMessage);
      #endif
    }
    P.displayReset();
  }
  readSerial();
}
