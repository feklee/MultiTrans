#include "MultiTrans.h"

static const uint8_t ledPinNumber = 13;
static const uint8_t communicationPinNumber1 = 2;
static const uint8_t communicationPinNumber2 = 3;
static const uint8_t communicationPinNumber3 = 8;
static const uint8_t communicationPinNumber4 = 9;

static const uint8_t bitDurationExp = 14; // 2^bitDurationExp milli seconds is
                                          // the duration of one transmitted bit
static const uint8_t maxNumberOfCharsPerTransmission = 12;
using MT = MultiTrans<bitDurationExp, maxNumberOfCharsPerTransmission>;
MT multiTransceiver;
MT::Transceiver<communicationPinNumber1> transceiver1;
MT::Transceiver<communicationPinNumber2> transceiver2;
MT::Transceiver<communicationPinNumber3> transceiver3;
MT::Transceiver<communicationPinNumber4> transceiver4;

ISR(TIMER2_COMPA_vect) {
  transceiver1.handleTimer2Interrupt();
  transceiver2.handleTimer2Interrupt();
  transceiver3.handleTimer2Interrupt();
  transceiver4.handleTimer2Interrupt();
}

ISR(PCINT2_vect) { // D0-D7
  transceiver1.handlePinChangeInterrupt();
  transceiver2.handlePinChangeInterrupt();
}

ISR(PCINT0_vect) { // D8-D13
  transceiver3.handlePinChangeInterrupt();
  transceiver4.handlePinChangeInterrupt();
}

void enablePinChangeInterrupts() {
  PCICR |= // Pin Change Interrupt Control Register
    bit(PCIE2) | // D0 to D7
    bit(PCIE0); // D8 to D15
}

void flashLed() {
  digitalWrite(ledPinNumber, HIGH);
  delay(100);
  digitalWrite(ledPinNumber, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(ledPinNumber, OUTPUT);

  multiTransceiver.startTimer1();
  multiTransceiver.startTimer2();
  enablePinChangeInterrupts();

  transceiver1.begin();
  transceiver2.begin();
  transceiver3.begin();
  transceiver4.begin();
}

template <typename T>
void transmitIfPossible(T &transceiver) {
  if (!transceiver.transmissionIsInProgress()) {
    transceiver.startTransmissionOfCharacters("Hello world!");
  }
}

void transmitWherePossible() {
  transmitIfPossible(transceiver1);
  transmitIfPossible(transceiver2);
  transmitIfPossible(transceiver3);
  transmitIfPossible(transceiver4);
}

void printLine(char characters[]) {
  for (uint8_t i = 0; i < 4; i ++) {
    char character = characters[i];
    Serial.print(character == 0 ? ' ' : character);
    Serial.print(" ");
  }
  Serial.println();
}

void processReceivedCharacters() {
  bool characterWasFound;
  do {
    char characters[] = {
      transceiver1.getNextCharacter(),
      transceiver2.getNextCharacter(),
      transceiver3.getNextCharacter(),
      transceiver4.getNextCharacter()
    };
    characterWasFound = (characters[0] != 0 ||
                         characters[1] != 0 ||
                         characters[2] != 0 ||
                         characters[3] != 0);
    if (characterWasFound) {
      printLine(characters);
    }
  } while(characterWasFound);
}

void loop() {
  processReceivedCharacters();
  transmitWherePossible();
}
