//Logitech Driving Force Shifter USB Adapter
//By Armandoiglesias 2018
//Based on Jason Duncan functionreturnfunction Project
//Video tutorial https://www.youtube.com/watch?v=dLpWEu8kCec
//Use Arduino Leonardo
//Install Joystick Library
//Attribution-NonCommercial-NoDerivatives 4.0 International


#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

// H-shifter mode analog axis thresholds
#define HS_XAXIS_12        400
#define HS_XAXIS_56        500
#define HS_YAXIS_135       800
#define HS_YAXIS_246       300

// Sequential shifter mode analog axis thresholds
#define SS_UPSHIFT_BEGIN   670
#define SS_UPSHIFT_END     600
#define SS_DOWNSHIFT_BEGIN 430
#define SS_DOWNSHIFT_END   500

// Handbrake mode analog axis limits
#define HB_MAXIMUM         530
#define HB_MINIMUM         400
#define HB_RANGE           (HB_MAXIMUM-HB_MINIMUM)

// Digital inputs definitions
#define DI_REVERSE         1
#define DI_MODE            3
#define DI_RED_CENTERRIGHT 4
#define DI_RED_CENTERLEFT  5
#define DI_RED_RIGHT       6
#define DI_RED_LEFT        7
#define DI_BLACK_TOP       8
#define DI_BLACK_RIGHT     9
#define DI_BLACK_LEFT      10
#define DI_BLACK_BOTTOM    11
#define DI_DPAD_RIGHT      12
#define DI_DPAD_LEFT       13
#define DI_DPAD_BOTTOM     14
#define DI_DPAD_TOP        15

// Shifter state
#define DOWN_SHIFT         -1
#define NO_SHIFT           0
#define UP_SHIFT           1

// Shifter mode
#define SHIFTER_MODE       0
#define HANDBRAKE_MODE     1

// Led Indication
#define RXLED 17

// LED blink counter
int led = 0;

// Shifter state
int shift = NO_SHIFT;

// Handbrake mode
int mode = SHIFTER_MODE;

int b[16];

int gear = 0;                        // Default value is neutral

// Constant that maps the phyical pin to the joystick button.
//const int pinToButtonMap = 9;

//int Pin_X = A0; // 0 for ATTiny85
//int Pin_Y = A2; // 1 for ATTiny85
//int Pin_Rev = 2; //D2 for Leo, 2 for ATTiny85

// 5V + GND are there on ATTiny85


void setup() {
  // G29 shifter analog inputs configuration
  // It use A0, A2, D2
  
  pinMode(A0, INPUT_PULLUP);   // X axis
  pinMode(A2, INPUT_PULLUP);   // Y axis

  pinMode(2, INPUT); // Reverse

  pinMode(RXLED, OUTPUT);       // RED LED pin 17
  digitalWrite(RXLED, HIGH);  // Indicate Living

  for (int i = 0; i < 16; i++) b[i] = 0;
  b[DI_MODE] = 0;
  // Initialize Joystick Library
  Joystick.begin();

  // Logger
  Serial.begin(9600);
  Serial.println("Boot completed. Proceed to Loop..");
}

// Last state of the button
int lastButtonState = 0;

void loop() {

  digitalWrite(RXLED, LOW);
    
  int x = analogRead(0);               // X axis
  int y = analogRead(2);               // Y axis

  Serial.println("X: " + String(x) + "| Y:" + String(y));

  int _isreverse = digitalRead(2);   // Rev
  int _gear_ = 0;

  if ( _isreverse == 1 && _gear_==6 ) { //Trung: only When Gear is 6th, allow Reverse )

    _gear_ = 8;
    b[DI_REVERSE] = 1;
    Serial.println("REV :" + String(_gear_));
    
  } else {

    if (b[DI_MODE] == 0)                 // H-shifter mode?
    {
      if (x < HS_XAXIS_12-50) //400-50               // Shifter on the left?
      {
        if (y > HS_YAXIS_135) _gear_ = 1;  // 1st gear
        if (y < HS_YAXIS_246) _gear_ = 2;  // 2nd gear
      }
      else if (x > HS_XAXIS_56 + 100) // 500+100     // Shifter on the right?
      {
        if (y > HS_YAXIS_135) _gear_ = 5;  // 5th gear
        if (y < HS_YAXIS_246) _gear_ = 6;  // 6th gear
      }
      else                               // Shifter is in the middle
      {
        if (y > HS_YAXIS_135) _gear_ = 3;  // 3rd gear
        if (y < HS_YAXIS_246) _gear_ = 4;  // 4th gear
      }

       //Log
        Serial.println("Gear:" + String(_gear_));
    }
  }


  if (gear != 6) b[DI_REVERSE] = 0;    // Reverse gear is allowed only on 6th gear position

  if (_gear_ != gear ) {
    gear = _gear_;
    desactivar();
    Joystick.setButton(gear - 1, HIGH);
  }


  if(_isreverse==1) digitalWrite(RXLED, HIGH);
  else              digitalWrite(RXLED, LOW);
  delay(50);

  // Keep blinking to indicate INPUT....
  digitalWrite(RXLED, HIGH);
}

void desactivar() {
  // Depress virtual button for current gear
  for (int i = 0; i <= 10 ; i++ )  Joystick.setButton(i, LOW);
}
