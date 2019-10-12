// Simple communication example
//
// Two Arduinos are connected. Both are sending and receiving simultaneously.
//
// See `README.md` in the current directory for a detailed explanation.
//
// Written by Felix E. Klee <felix.klee@inka.de>, released into the public
// domain.

#include "MultiTrans.h"

// Pin that connects the Arduinos:
const int rxPinNumber = 2;
const int txPinNumber = 3;

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

// The maximum number of characters per transmission can be configured. For the
// Arduino Uno, it cannot be more than 12. Lower values reduce memory
// consumption.
const int maxNumberOfCharsPerTransmission = 12;

// Connecting this pin to ground changes the test message:
const int messageSelectPin = 10;

// Message to send (may be shorter than the maximum length configured above):
char *message;

const bool recordDebugData = false;
const uint8_t customReceiveBufferSize = false;

const bool dontUseInputPullupForTxPin = true;
const bool invertTxPinValue = true;

// Here the transceiver is created.
using MT = MultiTrans<bitDurationExp, maxNumberOfCharsPerTransmission,
                      recordDebugData, customReceiveBufferSize,
                      dontUseInputPullupForTxPin, invertTxPinValue>;
MT multiTransceiver;
MT::Transceiver<rxPinNumber, txPinNumber> transceiver;

// This function, the timer 2 interrupt handler, is called every time a bit of
// data is to be transmitted.
ISR(TIMER2_COMPA_vect) {
  transceiver.handleTimer2Interrupt();
}

// Interrupt handler for receiving data on pins 0-7.
ISR(PCINT2_vect) {
  transceiver.handlePinChangeInterrupt();
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

  pinMode(messageSelectPin, INPUT_PULLUP);
  if (digitalRead(messageSelectPin) == HIGH) {
    message = "Hello world!";
  } else {
    message = "What's up?";
  }

  // Everything has been set up, now start transceiver:
  transceiver.begin();
}

void loop() {
  if (!transceiver.transmissionIsInProgress()) {
    transceiver.startTransmissionOfCharacters(message);
    Serial.print("Started sending: ");
    Serial.println(message);
  }

  printReceivedCharacters();

  delay(500);
}

void printReceivedCharacters() {
  while (true) {
    // `getNextCharacter` returns 0 if no character was received:
    char character = transceiver.getNextCharacter();

    if (character == 0) {
      return; // no character was received
    }

    Serial.print("Received: ");
    Serial.println(character);
  }
}
