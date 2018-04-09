#ifndef SupportLib_h
#define SupportLib_h

#include "Arduino.h"

/*
   File storing all support library available functions
*/

// DisplayDriver provides diplay capability
class DisplayClass {
  public:
    enum STATUS_MODE {
      SCAN,
      UPDATE,
      SUCC,
      FAIL,
      RDY
    };
    void begin();
    void showInititationMessage();
    void displayMessage(String, String);
    void displayDataOnly(String msg);
    void displayUnitDataOnly(char msg);
    void showModeStatus(STATUS_MODE mode);
};

class DBDriver {
  public:
    boolean getInitializationFlag();
    void setInitializationFlag(boolean flag);
    void setAccessCode(byte* code, byte len);
    boolean validateAccessCode(byte* code, byte len);
};

class GateClass {
  private:
    boolean status = false;
  public:
    void begin();
    void open();
    void close();
    boolean isOpen();
    void toggle();
};

// RFIDDriver provides RFID tag/ID card capability


class RFIDClass {
  public:
    void begin();
    boolean cardReady();
    void waitForNewCard();
    void waitForCard();
    boolean waitForCard(long max);
    // read UID of card
    byte* getPICCUID();
    byte getPICCUIDSize();
    void endCommunication();
};

#endif
