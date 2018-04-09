#include "SupportLib.h"
// Designed for LCD Charecter display

#include <LiquidCrystal.h>

/*
  The circuit:
   LCD RS pin to digital pin A5
   LCD Enable pin to digital pin A4
   LCD D4 pin to digital pin A3
   LCD D5 pin to digital pin A2
   LCD D6 pin to digital pin A1
   LCD D7 pin to digital pin A0
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
*/


/*
   Occupies pins:
   A0,A1,A2,A3,A4,A5
*/


LiquidCrystal LCD(A5, A4, A3, A2, A1, A0);  // set as above description

#define DISPLAY_WIDTH 16
#define DISPLAY_HIGHT 2

void DisplayClass :: begin() {
  LCD.begin(DISPLAY_WIDTH, DISPLAY_HIGHT); // set proper display init
}

void DisplayClass :: showInititationMessage() {
  LCD.clear();
  String data = "Inititaing";
  String displayString = "";

  // adding extra space in front for padding
  for (byte i = 0; i <= (DISPLAY_WIDTH - data.length()) / 2; i++) {
    displayString += " ";
  }
  displayString += data;

  LCD.print(displayString);
}

void DisplayClass :: displayMessage(String heading, String msg) {
  LCD.clear();
  LCD.print(heading);
  LCD.setCursor(0, 1);
  LCD.print(msg);
}

void DisplayClass :: displayDataOnly(String msg) {
  LCD.setCursor(0, 1);
  LCD.print(msg);
}

void DisplayClass :: displayUnitDataOnly(char msg) {
  LCD.setCursor(0, 1);
  LCD.print(msg);
}

void DisplayClass :: showModeStatus(STATUS_MODE mode) {
  LCD.clear();
  LCD.setCursor(0, 1);

  switch (mode) {
    case SCAN:
      LCD.print("Scanning...");
      break;
    case UPDATE:
      LCD.print("Updating...");
      break;
    case SUCC:
      LCD.print("Success");
      break;
    case FAIL:
      LCD.print("Failed");
      break;
    case RDY:
      LCD.print("Ready");
      break;
  }
}

