#pragma once

#include "Arduino.h"
#include "CharacterEncoding.h"
#include <util/atomic.h>

template <typename T>
class ReceiveBuffer {
  using Transceiver = T;

  static const uint8_t paddingForNoise =
    1; // arbitrary, just to be on the safe side

  // It may be interesting to allow the user to specify a larger maximum buffer
  // size in order to be able to receive characters from multiple transmissions.
  static const uint8_t maxNumberOfElements = // <= 256
    Transceiver::maxNumberOfCharsPerTransmission *
    (CharacterEncoding::maxNumberOfValueChanges + paddingForNoise);

  byte _elements[maxNumberOfElements];
  bool _bufferWasEmptyOnLastAtomicShift = false;
  bool _noiseHasBeenDetected = false;
  volatile uint8_t _indexOfStart = 0;
  volatile uint8_t _indexOfNextElement = 0;
  char _character = 0;
  uint8_t _numberOfProcessedBits = 0;
  bool _startBitHasBeenPassed = false;
  bool _stopBitHasBeenPassed = false;
  bool _readingCharacterBitsHasStarted = false;
  bool _shiftingCharacterIsFinished = false;

  bool characterIsComplete();
  void interpretElement(const byte);
  bool getValueOfElapsedBits(const byte) const;
  byte getNumberOfElapsedBits(const byte) const;
  bool isBreak(byte) const;
  bool hasValueOfStopBit(byte) const;
  bool hasValueOfIdle(byte) const;
  inline void incrementIndex(uint8_t &) const __attribute__((always_inline));
  inline uint8_t precedingIndex(const uint8_t) const
    __attribute__((always_inline));
  byte atomicShift();
  void stopReadingCharacterBits();
  void startReadingCharacterBits();
  byte readCharacterBits(const byte);
  void cancelReadingCharacterDueToNoise();
  void discardCharacterBits();
  void resetShiftingOfCharacter();

public:
  ReceiveBuffer();
  inline void push(byte) __attribute__((always_inline));
  char shiftCharacter();
  bool noiseHasBeenDetected() const  { return _noiseHasBeenDetected; }
};

template <typename T>
bool ReceiveBuffer<T>::getValueOfElapsedBits(const byte element) const {
  return !(element >> 7);
}

template <typename T>
byte ReceiveBuffer<T>::getNumberOfElapsedBits(const byte element) const {
  return element & ~bit(7);
}

template <typename T>
bool ReceiveBuffer<T>::isBreak(const byte element) const {
  return
    getValueOfElapsedBits(element) == CharacterEncoding::valueOfBreakBit &&
    getNumberOfElapsedBits(element) == CharacterEncoding::breakLength;
}

template <typename T>
bool ReceiveBuffer<T>::hasValueOfIdle(const byte element) const {
  return getValueOfElapsedBits(element) == CharacterEncoding::valueOfIdleBit;
}

template <typename T>
bool ReceiveBuffer<T>::hasValueOfStopBit(const byte element) const {
  return getValueOfElapsedBits(element) == CharacterEncoding::valueOfStopBit;
}

template <typename T>
void ReceiveBuffer<T>::stopReadingCharacterBits() {
  _readingCharacterBitsHasStarted = false;
}

template <typename T>
void ReceiveBuffer<T>::startReadingCharacterBits() {
  _readingCharacterBitsHasStarted = true;
}

template <typename T>
void ReceiveBuffer<T>::cancelReadingCharacterDueToNoise() {
  _noiseHasBeenDetected = true;
  discardCharacterBits();
  stopReadingCharacterBits();
}

template <typename T>
byte ReceiveBuffer<T>::readCharacterBits(const byte element) {
  const byte valueOfElapsedBits = getValueOfElapsedBits(element);
  uint8_t numberOfElapsedBits = getNumberOfElapsedBits(element);

  bool elementIsUnexpected = numberOfElapsedBits == 0;
  if (elementIsUnexpected) {
    cancelReadingCharacterDueToNoise();
    return 0;
  }

  if (!_startBitHasBeenPassed) {
    elementIsUnexpected =
      valueOfElapsedBits != CharacterEncoding::valueOfStartBit;
    if (elementIsUnexpected) {
      cancelReadingCharacterDueToNoise();
      return 0;
    }
    numberOfElapsedBits --;
    _startBitHasBeenPassed = true;
  }

  if (_numberOfProcessedBits + numberOfElapsedBits > 8) {
    if (_numberOfProcessedBits + numberOfElapsedBits == 9) {
      // happens when value of last bit equals value of stop bit
      numberOfElapsedBits = 8 - _numberOfProcessedBits;
      _stopBitHasBeenPassed = true;
    } else {
      cancelReadingCharacterDueToNoise();
      return 0;
    }
  }

  byte characterBits;

  if (valueOfElapsedBits == 1) {
    characterBits = 0xff;
    characterBits >>= 8 - numberOfElapsedBits;
    characterBits <<= _numberOfProcessedBits;
  } else {
    characterBits = 0;
  }

  _numberOfProcessedBits += numberOfElapsedBits;

  return characterBits;
}

template <typename T>
void ReceiveBuffer<T>::incrementIndex(uint8_t &index) const {
  index ++;
  if (index > maxNumberOfElements - 1) {
    index = 0;
  }
}

template <typename T>
uint8_t ReceiveBuffer<T>::precedingIndex(const uint8_t index) const {
  return (index > 0) ? (index - 1) : (maxNumberOfElements - 1);
}

template <typename T>
byte ReceiveBuffer<T>::atomicShift() {
  byte element;
  bool bufferIsEmpty;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    // Copy volatile variables to avoid too many memory accesses (this code runs
    // atomically):
    uint8_t cachedIndexOfStart = _indexOfStart;

    bufferIsEmpty = cachedIndexOfStart == _indexOfNextElement;
    if (bufferIsEmpty) {
      element = 0;
    } else {
      element = _elements[cachedIndexOfStart];
      incrementIndex(cachedIndexOfStart);
      _indexOfStart = cachedIndexOfStart;
    }

    if (Transceiver::debugDataIsRecorded) {
      Transceiver::debugData.receiveBufferStart = cachedIndexOfStart;
    }
  }

  _bufferWasEmptyOnLastAtomicShift = bufferIsEmpty;
  return element;
}

template <typename T>
bool ReceiveBuffer<T>::characterIsComplete() {
  return _numberOfProcessedBits == 8;
}

template <typename T>
void ReceiveBuffer<T>::discardCharacterBits() {
  _numberOfProcessedBits = 0;
}

template <typename T>
void ReceiveBuffer<T>::interpretElement(const byte element) {
  if (isBreak(element)) {
    discardCharacterBits();
    startReadingCharacterBits();
  } else if (_readingCharacterBitsHasStarted) {
    _character |= readCharacterBits(element);
    if (characterIsComplete()) {
      stopReadingCharacterBits();
    }
  } else if (characterIsComplete() && !_stopBitHasBeenPassed) {
    if (hasValueOfStopBit(element)) {
      _stopBitHasBeenPassed = true;
    } else {
      cancelReadingCharacterDueToNoise();
    }
  } else if (!hasValueOfIdle(element)) {
    _noiseHasBeenDetected = true;
  }
}

template <typename T>
void ReceiveBuffer<T>::resetShiftingOfCharacter() {
  _character = 0;
  _startBitHasBeenPassed = false;
  _stopBitHasBeenPassed = false;
  _noiseHasBeenDetected = false;
  _numberOfProcessedBits = 0;
}

// Returns 0 if no character is found.
template <typename T>
char ReceiveBuffer<T>::shiftCharacter() {
  bool startAgain = _shiftingCharacterIsFinished;
  if (startAgain) {
    resetShiftingOfCharacter();
    _shiftingCharacterIsFinished = false;
  }

  // ReceiveBuffer overflows should be avoided or else there may be issues when
  // they happen during the loop.
  byte element = atomicShift();
  while (!_bufferWasEmptyOnLastAtomicShift) {
    interpretElement(element);
    _shiftingCharacterIsFinished =
      characterIsComplete() && _stopBitHasBeenPassed;
    if (_shiftingCharacterIsFinished) {
      _shiftingCharacterIsFinished = true;
      return _character;
    }
    element = atomicShift();
  }

  return 0;
}

template <typename T>
void ReceiveBuffer<T>::push(const byte element) {
  // Copy volatile variables to avoid too many memory accesses (this code only
  // runs from an interrupt, i.e. it is executed atomically):
  uint8_t cachedIndexOfNextElement = _indexOfNextElement;
  uint8_t cachedIndexOfStart = _indexOfStart;

  _elements[cachedIndexOfNextElement] = element;
  incrementIndex(cachedIndexOfNextElement);
  bool bufferIsFull = cachedIndexOfNextElement == cachedIndexOfStart;
  if (bufferIsFull) {
    if (Transceiver::debugDataIsRecorded) {
      Transceiver::debugData.receiveBufferOverflowCount ++;
    }
    incrementIndex(cachedIndexOfStart);
    _indexOfStart = cachedIndexOfStart;
  }

  _indexOfNextElement = cachedIndexOfNextElement;
  if (Transceiver::debugDataIsRecorded) {
    Transceiver::debugData.receiveBufferEnd =
      precedingIndex(cachedIndexOfNextElement);
  }
}

template <typename T>
ReceiveBuffer<T>::ReceiveBuffer() {
  resetShiftingOfCharacter();
}
