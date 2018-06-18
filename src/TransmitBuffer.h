#pragma once

#include "Arduino.h"
#include "CharacterEncoding.h"

template <uint8_t t>
class TransmitBuffer {
  static const uint8_t maxNumberOfCharsPerTransmission = t; // < 13 (characters)
  static const uint8_t maxNumberOfBits =
    maxNumberOfCharsPerTransmission * CharacterEncoding::totalLength;

  volatile uint8_t _numberOfBits;
  volatile uint8_t _bitPosition;
  volatile byte _bits[maxNumberOfBits];
  uint8_t _numberOfCharacters = 0;

  bool randomBool();

public:
  void clear();
  void addBreak(uint8_t &);
  void addPayload(uint8_t &, char);
  void addCharacter(char);
  void fillWithNoise();
  uint8_t bitPosition() const { return _bitPosition; }
  void setBitPosition(uint8_t x) { _bitPosition = x; }
  uint8_t numberOfBits() const { return _numberOfBits; }
  byte bitAtPosition(const uint8_t position) const {
    return _bits[position];
  }
};

template <uint8_t t>
void TransmitBuffer<t>::clear() {
  _numberOfCharacters = 0;
  _numberOfBits = 0;
  _bitPosition = 0;
}

template <uint8_t t>
void TransmitBuffer<t>::addBreak(uint8_t &j) {
  for (uint8_t i = 0; i < CharacterEncoding::breakLength; i ++) {
    _bits[j ++] = CharacterEncoding::valueOfBreakBit;
  }
}

template <uint8_t t>
void TransmitBuffer<t>::addPayload(uint8_t &j, char character) {
  for (uint8_t i = 0; i < 8; i ++) {
    _bits[j ++] = character & 1;
    character >>= 1;
  }
}

template <uint8_t t>
void TransmitBuffer<t>::addCharacter(char character) {
  uint8_t j = _numberOfBits;

  if (_numberOfCharacters >= maxNumberOfCharsPerTransmission) {
    return;
  }

  addBreak(j);

  _bits[j ++] = CharacterEncoding::valueOfStartBit;

  addPayload(j, character);

  _bits[j ++] = CharacterEncoding::valueOfStopBit;
  _bits[j ++] = CharacterEncoding::valueOfIdleBit; // start idling

  _numberOfBits = j;
  _numberOfCharacters ++;
}

template <uint8_t t>
bool TransmitBuffer<t>::randomBool() {
  return rand() % 2;
}

template <uint8_t t>
void TransmitBuffer<t>::fillWithNoise() {
  const uint8_t maxLengthOfRandomSegment =
    CharacterEncoding::breakLength + 1 + CharacterEncoding::payloadLength
    -1; // shorten to prevent accidental generation of bits that look like a
        // character being transmitted

  uint8_t j = 0;

  const bool breakShouldBeIncluded = randomBool();
  if (breakShouldBeIncluded) {
    while (j < CharacterEncoding::breakLength) {
      _bits[j ++] = CharacterEncoding::valueOfBreakBit;
    }
  }

  while (j < maxLengthOfRandomSegment) {
    _bits[j ++] = random(1);
  }

  _bits[j ++] = CharacterEncoding::valueOfIdleBit; // start idling

  _numberOfBits = j;
}
