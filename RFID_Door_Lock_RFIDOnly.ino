#include "SupportLib.h"

/*
   Connections used :
   All analog I/P, used as LCD O/P
   9,10,11,12,13 for RFID
   7 as Gate
   3 as RESET Pin
*/

DisplayClass Display;
DBDriver DB;
RFIDClass RFIDCardReader;
GateClass Gate;

//const byte SYSTEM_RESET_PIN = 2;  now software reset is used
void(* resetFunc) (void) = 0; //declare reset function at address 0

void SystemReset() {
  //digitalWrite(SYSTEM_RESET_PIN, HIGH);
  resetFunc();
}

const byte RESET_PIN = 3;

void setup() {
  Gate.begin();
  RFIDCardReader.begin();
  Display.begin();
  Display.showInititationMessage();
  delay(500);

  if (DB.getInitializationFlag() == false) {
    Display.displayMessage("Entering", "1st Time Setup");
    delay(800);

    Display.displayMessage("Enter Card", "");

    RFIDCardReader.waitForCard();
    
    Display.showModeStatus(DisplayClass::STATUS_MODE::SUCC);
    DB.setAccessCode(RFIDCardReader.getPICCUID(), RFIDCardReader.getPICCUIDSize());
    DB.setInitializationFlag(true);
    
    SystemReset();
  }
}

void loop() {
  if (digitalRead(RESET_PIN) == HIGH) {
    Display.displayMessage("Verify id", "Enter old Card");

    if (!RFIDCardReader.waitForCard(10000)) {
      Display.displayMessage("Error", "Timeout");
      delay(1000);
      return;
    }

    if (DB.validateAccessCode(RFIDCardReader.getPICCUID(), RFIDCardReader.getPICCUIDSize())) {
      DB.setInitializationFlag(false);
      SystemReset();
    } else {
      Display.displayMessage("Error", "Auth failed");
      delay(1000);
    }
  }


  Display.showModeStatus(DisplayClass::STATUS_MODE::RDY);
  if (RFIDCardReader.cardReady()) {
    if (DB.validateAccessCode(RFIDCardReader.getPICCUID(), RFIDCardReader.getPICCUIDSize())) {
      // toggle gate
      Gate.toggle();
    }
  }
}

