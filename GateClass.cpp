#include "SupportLib.h"

extern DisplayClass Display;

#define GATE_PIN  7

void GateClass :: begin() {
  pinMode(GATE_PIN, OUTPUT);
}

void GateClass :: open() {
  if (!isOpen()) {
    // open gate
    digitalWrite(GATE_PIN, HIGH);
    Display.displayMessage("Gate Opened", "");
    delay(800);
    status = true;
  }
}

void GateClass :: close() {
  if (isOpen()) {
    // close gate
    digitalWrite(GATE_PIN, LOW);
    Display.displayMessage("Gate Closed", "");
    delay(800);
    status = false;
  }
}

boolean GateClass :: isOpen() {
  return status;
}

void GateClass :: toggle() {
  // toggle gate
  if (isOpen()) {
    close();
  } else {
    open();
  }
}
