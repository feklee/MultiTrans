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

  inline static void driveLow() __attribute__((always_inline));
  inline static void driveHigh() __attribute__((always_inline));
  inline static void configureForInput() __attribute__((always_inline));
  inline static void configureForOutput() __attribute__((always_inline));
  inline static void writeToOutput(const bool) __attribute__((always_inline));
  inline static void writeSafely(const bool) __attribute__((always_inline));

public:
  inline static void write(const bool) __attribute__((always_inline));
  inline static bool read() __attribute__((always_inline));
  static void setToInputPullup();
  static void activatePinChangeInterrupt();
};

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
void CommunicationPin<T, t>::driveLow() {
  *dataRegister &= ~bitMask;
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::driveHigh() {
  *dataRegister |= bitMask;
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::configureForInput() {
  *dataDirectionRegister &= ~bitMask;
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::configureForOutput() {
  *dataDirectionRegister |= bitMask;
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::writeToOutput(const bool pinValue) {
  configureForOutput();
  if (pinValue) {
    // short, if pin on other board is ground
    driveHigh();
  } else {
    driveLow();
  }
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::writeSafely(const bool pinValue) {
  if (pinValue) {
    // Input pullup: avoids short, if pin on other board is ground
    configureForInput();
    driveHigh();
  } else {
    // 1. Drive output low first:
    driveLow();

    // 2. Set up pin for output: (after driving output low, or else a short may
    // be caused if the pin is connected to ground)
    configureForOutput();
  }
}

template <typename T, uint8_t t>
void CommunicationPin<T, t>::write(const bool value) {
  const bool pinValue = T::invertTxPinValue ? !value : value;

  if (T::dontUseInputPullupForTxPin) {
    writeToOutput(pinValue);
  } else {
    writeSafely(pinValue);
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
