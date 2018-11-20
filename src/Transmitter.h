#pragma once

#include <assert.h>
#include <util/atomic.h>
#include "Arduino.h"
#include "./TransmitBuffer.h"
#include "./CommunicationPin.h"
#include "./CharacterEncoding.h"

template <typename T>
class Transmitter {
  using Transceiver = T;

  static const uint8_t pinNumber = Transceiver::pinNumber;
  volatile uint8_t _numberOfSuccessiveHighBits = 0;
  volatile bool _transmissionIsInProgress = false;
  volatile bool _isWaitingForFreeLine = false;
  TransmitBuffer<Transceiver::maxNumberOfCharsPerTransmission> _buffer;

  inline void checkIfLineIsFree() __attribute__((always_inline));
  void startWaitingForFreeLine();
  void startIdling();
  inline void stopTransmission() __attribute__((always_inline));
  void startTransmission();
  inline void transmitBit() __attribute__((always_inline));
  inline void checkForCollision() __attribute__((always_inline));

public:
  inline void handleTimer2Interrupt() __attribute__((always_inline));
  void startTransmissionOfCharacters(const char * const);
  void startTransmissionOfBytes(const byte * const, const uint8_t);
  void startTransmissionOfNoise();
  void begin();
  bool transmissionIsInProgress() const { return _transmissionIsInProgress; }
  bool isWaitingForFreeLine() const { return _isWaitingForFreeLine; }
};

template <typename T>
void Transmitter<T>::transmitBit() {
  // Avoid reloading volatile variable often (this code only runs from an
  // interrupt, i.e. it is executed atomically):
  uint8_t cachedBitPosition = _buffer.bitPosition();

  if (cachedBitPosition >= _buffer.numberOfBits()) {
    stopTransmission();
  } else {
    CommunicationPin<pinNumber>::write(
      _buffer.bitAtPosition(cachedBitPosition)
    );
    cachedBitPosition ++;
    _buffer.setBitPosition(cachedBitPosition);
  }
}

template <typename T>
void Transmitter<T>::checkIfLineIsFree() {
  const uint8_t padding = 8; // arbitrary, just to be on the safe side
  bool noCharacterIsBeingTransmitted =
    _numberOfSuccessiveHighBits >
    CharacterEncoding::maxNumberOfSuccessiveHighBits + padding;
  if (noCharacterIsBeingTransmitted) {
    _isWaitingForFreeLine = false;
  }
}

template <typename T>
void Transmitter<T>::startWaitingForFreeLine() {
  CommunicationPin<pinNumber>::write(HIGH);
  _numberOfSuccessiveHighBits = 0;
  _isWaitingForFreeLine = true;
}

template <typename T>
void Transmitter<T>::checkForCollision() {
  const bool value = CommunicationPin<pinNumber>::read();
  const bool collisionDetected = value == LOW; // because pin is input pull-up
                                               // when waiting for free line

  if (collisionDetected) {
    _numberOfSuccessiveHighBits = 0;
    if (Transceiver::debugDataIsRecorded) {
      Transceiver::debugData.numberOfCollisions ++;
    }
  } else {
    if (_isWaitingForFreeLine) {
      _numberOfSuccessiveHighBits ++;
      checkIfLineIsFree();
    }
  }
}

template <typename T>
void Transmitter<T>::handleTimer2Interrupt() {
  if (!_transmissionIsInProgress) {
    return;
  }

  if (_isWaitingForFreeLine) {
    checkForCollision();

    // Don't return! When the line becomes free, the first bit is transmitted
    // right away. The first bit draws the line low for the break. This also
    // indicates the other side that there is a transmission in progress. If
    // both sides want to start sending at almost the same time , then a delay
    // of one bit duration could be too long for the other side to notice the
    // start of transmission.
  }

  bool lineIsFree = !_isWaitingForFreeLine; // may have changed above
  if (lineIsFree) {
    transmitBit();
  }
}

template <typename T>
void Transmitter<T>::startTransmission() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    startWaitingForFreeLine();
    _transmissionIsInProgress = true;
  }
}

template <typename T>
void Transmitter<T>::stopTransmission() {
  _transmissionIsInProgress = false;
}

template <typename T>
void Transmitter<T>::startTransmissionOfCharacters(
  const char * const s
) {
  _buffer.clear();

  const char *character = s;
  while (*character) {
    _buffer.addCharacter(*character);
    character ++;
  }

  startTransmission();
}

template <typename T>
void Transmitter<T>::startTransmissionOfBytes(
  const byte * const bytes,
  const uint8_t numberOfBytes
) {
  _buffer.clear();

  const byte *b = bytes;
  uint8_t i = numberOfBytes;
  while (i) {
    _buffer.addCharacter((char) *b);
    b ++;
    i --;
  }

  startTransmission();
}

// Noise is for testing. Noise is generated in a way so that it cannot be
// confused with a character transmitted.
template <typename T>
void Transmitter<T>::startTransmissionOfNoise() {
  _buffer.clear();
  _buffer.fillWithNoise();
  startTransmission();
}

template <typename T>
void Transmitter<T>::startIdling() {
  CommunicationPin<pinNumber>::write(HIGH);
}

template <typename T>
void Transmitter<T>::begin() {
  startIdling();
}
