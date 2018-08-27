// Triangle communication example
//
// Three Arduinos are connected in a triangle. All are sending and receiving
// simultaneously.
//
// See `README.md` in the current directory for a detailed explanation.
//
// Written by Felix E. Klee <felix.klee@inka.de>, released into the public
// domain.

#include "MultiTrans.h"

// Pins that connect the Arduinos:
const int communicationPinNumber1 = 2;
const int communicationPinNumber2 = 8;

// The bit duration exponent determines communication speed. The lower it is,
// the faster the communication is. The maximum value is 18 (slowest). Very fast
// communication leads to transmission errors.
//
// Math: The duration for the transmission of one bit is (in CPU cycles):
//
//     bitDuration = 2 ^ bitDurationExp
//
// Bits being transmitted include an overhead necessary for communication.
// Therefore, the effective data rate is less than `1 / bitDuration`.
const int bitDurationExp = 16;

// The maximum number of characters per transmission can be configured. It
// should not be more than 12. Lower values reduce memory consumption.
const uint8_t maxNumberOfCharsPerTransmission = 12;

// Here the transceivers are created, one for each communication pin.
using MT = MultiTrans<bitDurationExp, maxNumberOfCharsPerTransmission>;
MT multiTransceiver;
MT::Transceiver<communicationPinNumber1> transceiver1;
MT::Transceiver<communicationPinNumber2> transceiver2;

// This function, the timer 2 interrupt handler, is called every time a bit of
// data is to be transmitted.
ISR(TIMER2_COMPA_vect) {
  transceiver1.handleTimer2Interrupt();
  transceiver2.handleTimer2Interrupt();
}

// Interrupt handler for receiving data on pins 0-7.
ISR(PCINT2_vect) {
  transceiver1.handlePinChangeInterrupt();
}

// Interrupt handler for receiving data on pins 8-13.
ISR(PCINT0_vect) {
  transceiver2.handlePinChangeInterrupt();
}

void setup() {
  Serial.begin(9600);

  // Start timer interrupts:
  multiTransceiver.startTimer1();
  multiTransceiver.startTimer2();

  // Start interrupt handler for receiving bits:
  PCICR |= // Pin Change Interrupt Control Register
    bit(PCIE2) | // D0 to D7
    bit(PCIE0); // D8 to D15

  // Everything has been set up, now start transceivers:
  transceiver1.begin();
  transceiver2.begin();
}

void loop() {
  printReceivedCharacters();

  if (!transceiver1.transmissionIsInProgress()) {
    transceiver1.startTransmissionOfCharacters("Hello world!");
  }

  if (!transceiver2.transmissionIsInProgress()) {
    transceiver2.startTransmissionOfCharacters("foo");
  }

  delay(500);
}

void printReceivedCharacters() {
  while (true) {
    // `getNextCharacter` returns 0 if no character was received:
    char character1 = transceiver1.getNextCharacter();
    char character2 = transceiver2.getNextCharacter();

    if (character1 == 0 && character2 == 0) {
      return; // no character was received
    }

    printCharacter(character1);
    Serial.print(", ");
    printCharacter(character2);
    Serial.println();
  }
}

void printCharacter(char character) {
  if (character != 0) {
    Serial.print(character);
  } else {
    Serial.print(" ");
  }
}
