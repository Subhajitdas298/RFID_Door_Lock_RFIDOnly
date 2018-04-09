#include "SupportLib.h"
// Designed for RC522 Chip
// Library : https://github.com/miguelbalboa/rfid

/*
    Note : Authentication and security is not yet implemented
*/

/*
   Occupies pins:
   13,12,11,10,9

   Pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

void RFIDClass :: begin() {
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);
}

boolean RFIDClass :: cardReady() {
  return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

void RFIDClass :: waitForCard() {
  while (!cardReady());
}

boolean RFIDClass :: waitForCard(long max) {
  long startTime = millis();
  while (millis() < (startTime + max)){
    if(cardReady()) return true;
    delay(10);
  }
  return false;
}

// read UID of card
byte* RFIDClass :: getPICCUID() {
  //  String content = "";
  //  for (byte i = 0; i < rfid.uid.size; i++) {
  //    content.concat(String(rfid.uid.uidByte[i], HEX));
  //  }
  return rfid.uid.uidByte;
}

byte RFIDClass :: getPICCUIDSize() {
  //  String content = "";
  //  for (byte i = 0; i < rfid.uid.size; i++) {
  //    content.concat(String(rfid.uid.uidByte[i], HEX));
  //  }
  return rfid.uid.size;
}

void RFIDClass :: endCommunication() {
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  //rfid.PCD_StopCrypto1();
}
