// Writes an ID to EEPROM. Change the ID for each Arduino!

#include <EEPROM.h>

char id = '*';

void setup() {
  EEPROM.write(0, id);
}

void loop() {}
