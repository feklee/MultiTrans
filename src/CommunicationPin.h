#pragma once

#include "Arduino.h"

// For pin mapping and registers, see:
//
//   * Pin Mapping of Atmega 168/328:
//     https://www.arduino.cc/en/Hacking/Atmega168Hardware
//
//   * Arduino Pro Mini data sheet:
//     https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/ProMini16MHzv1.pdf
//
//   * ATmega328/P data sheet (version DS40001984A):
//     <http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%
//     20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf>

template <typename T, uint8_t t>
class CommunicationPin {
  using Transceiver = T;

  static const uint8_t pinNumber = t; // in [2, 13]
  static const uint8_t bitNumber;
  static const uint8_t bitMask;
  static const uint8_t interruptBitMask;
  static volatile uint8_t * const dataDirectionRegister;
  static volatile uint8_t * const dataRegister;
  static volatile uint8_t * const inputRegister;
  static volatile uint8_t * const pinChangeMaskRegister;

public:
  CommunicationPin();
  inline static void write(const bool) __attribute__((always_inline));
  inline static bool read() __attribute__((always_inline));
  static void setToInputPullup();
  static void activatePinChangeInterrupt();
};

template <typename T, uint8_t t>
CommunicationPin<T, t>::CommunicationPin() {
  assert(pinNumber >= 2 && pinNumber <= 13);
}

template <typename T, uint8_t t>
const uint8_t CommunicationPin<T, t>::bitNumber =
  (pinNumber < 8) ? pinNumber : (pinNumber - 8);

template <typename T, uint8_t t>
const uint8_t CommunicationPin<T, t>::bitMask =
  1 << CommunicationPin<T, t>::bitNumber;

template <typename T, uint8_t t>
const uint8_t CommunicationPin<T, t>::interruptBitMask =
  CommunicationPin<T, t>::bitMask;

template <typename T, uint8_t t>
volatile uint8_t * const CommunicationPin<T, t>::dataDirectionRegister =
  (pinNumber < 8) ? &DDRD : &DDRB;

template <typename T, uint8_t t>
volatile uint8_t * const CommunicationPin<T, t>::dataRegister =
  (pinNumber < 8) ? &PORTD : &PORTB;

template <typename T, uint8_t t>
volatile uint8_t * const CommunicationPin<T, t>::inputRegister =
  (pinNumber < 8) ? &PIND : &PINB;

template <typename T, uint8_t t>
volatile uint8_t * const CommunicationPin<T, t>::pinChangeMaskRegister =
  (pinNumber < 8) ? &PCMSK2 : &PCMSK0;

template <typename T, uint8_t t>
void CommunicationPin<T, t>::write(const bool value) {
  const bool pinValue = T::invertTxPinValue ? !value : value;

  if (T::dontUseInputPullupForTxPin) {
    // TODO: directly manipulate registers for performance
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, pinValue);
    return;
  }

  if (pinValue) {
    *dataDirectionRegister &= ~bitMask;
    *dataRegister |= bitMask; // input pullup
  } else {
    // 1. Drive output low first:
    *dataRegister &= ~bitMask;

    // 2. Set up pin for output: (after driving output low, or else a short may
    // be caused if the pin is connected to ground)
    *dataDirectionRegister |= bitMask;
  }
}

template <typename T, uint8_t t>
bool CommunicationPin<T, t>::read() {
  return *inputRegister & bitMask;
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::setToInputPullup() {
  *dataDirectionRegister &= ~bitMask;
  *dataRegister |= bitMask;
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::activatePinChangeInterrupt() {
  *pinChangeMaskRegister |= interruptBitMask;
}
