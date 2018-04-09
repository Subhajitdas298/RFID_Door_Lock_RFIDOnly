#include<EEPROM.h>
#include "SupportLib.h"

#define FLAG_SET    1
#define FLAG_RESET  0

#define FLAG_ADDRESS              0
#define ACCESS_CODE_SIZE_ADDRESS  1
#define ACCESS_CODE_ADDRESS       2

boolean DBDriver :: getInitializationFlag() {
  byte value = EEPROM.read(FLAG_ADDRESS);
  if (value == FLAG_SET) return true;
  else return false;
}

void DBDriver :: setInitializationFlag(boolean flag) {
  if (flag == true) EEPROM.write(FLAG_ADDRESS, FLAG_SET);
  else EEPROM.write(0, FLAG_RESET);
}

void DBDriver :: setAccessCode(byte* code, byte len) {
  EEPROM.write(ACCESS_CODE_SIZE_ADDRESS, len);
  for(int i = 0; i < len; i++){
    EEPROM.write(ACCESS_CODE_ADDRESS + i, code[i]);
  }
}

boolean DBDriver :: validateAccessCode(byte* code, byte len) {
  if(EEPROM.read(ACCESS_CODE_SIZE_ADDRESS) != len) return false;
  for(int i = 0; i < len; i++){
    if(EEPROM.read(ACCESS_CODE_ADDRESS + i) !=  code[i]){
      return false;
    }
  }
  return true;
}
