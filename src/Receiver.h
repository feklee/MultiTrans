#pragma once

#include "Arduino.h"
#include "./ReceiveBuffer.h"
#include "./CommunicationPin.h"

template <typename T, uint8_t t>
class Receiver {
  using Transceiver = T;

  static const uint8_t pinNumber = Transceiver::pinNumber;
  static const uint8_t unscaledBitDurationExp = t;
  static const uint16_t unscaledBitDuration =
    1 << unscaledBitDurationExp; // in CPU cycles / prescale factor

  ReceiveBuffer<Transceiver> _buffer;

  inline uint8_t numberOfBitsInInterval(uint16_t)
    __attribute__((always_inline));
  inline uint16_t elapsedTime(uint16_t, uint16_t)
    __attribute__((always_inline));

public:
  inline void handlePinChangeInterrupt(const uint16_t, const bool)
    __attribute__((always_inline));
  void begin();
  char shiftCharacterFromBuffer() {
    return _buffer.shiftCharacter(); // 0 if there is no character
  }
  byte shiftByteFromBuffer(bool &byteWasFound) {
    return _buffer.shiftCharacter(&byteWasFound);
  }
  bool noiseWhileGettingCharacter() const  {
    return _buffer.noiseHasBeenDetected();
  }
  bool noiseWhileGettingByte() const  {
    return _buffer.noiseHasBeenDetected();
  }
};

template <typename T, uint8_t t>
uint8_t Receiver<T, t>::numberOfBitsInInterval(
  uint16_t unscaledDuration // in CPU cycles / prescale factor
) {
  const uint16_t unscaledHalfBitDuration = unscaledBitDuration >> 1;

  // Same as `round(float(duration) / unscaledBitDuration)`:
  return (unscaledDuration + unscaledHalfBitDuration) >> unscaledBitDurationExp;
}

template <typename T, uint8_t t>
uint16_t Receiver<T, t>::
elapsedTime( // in CPU cycles / prescale factor
  uint16_t timeAtStart, // in CPU cycles / prescale factor
  uint16_t timeAtEnd // in CPU cycles / prescale factor
) {
  static const uint16_t maxTime = UINT16_MAX;
  if (timeAtEnd < timeAtStart) {
    return timeAtEnd + (maxTime - timeAtStart);
  }
  return timeAtEnd - timeAtStart;
}

template <typename T, uint8_t t>
void Receiver<T, t>::handlePinChangeInterrupt(
  const uint16_t now, // in CPU cycles / prescale factor
  const bool valueAfterPinChange
) {
  static uint16_t lastTime = 0; // in CPU cycles / prescale factor

  const uint16_t unscaledDuration = elapsedTime(lastTime, now);
  const uint8_t numberOfElapsedBits = numberOfBitsInInterval(unscaledDuration);

  byte element = numberOfElapsedBits;
  element &= ~bit(7);
  element |= valueAfterPinChange << 7;
  _buffer.push(element);

  lastTime = now;
}

template <typename T, uint8_t t>
void Receiver<T, t>::begin() {
  CommunicationPin<pinNumber>::setToInputPullup();
  CommunicationPin<pinNumber>::activatePinChangeInterrupt();
}
