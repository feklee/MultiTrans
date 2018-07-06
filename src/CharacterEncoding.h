#pragma once

#include "Arduino.h"

namespace CharacterEncoding {
  static const uint8_t breakLength = 10; // in number of bits
  static const uint8_t ceilOfBreakLengthExp = 4; // ceil(log2(breakLength))
  static const uint8_t payloadLength = 8; // in number of bits
  static const uint8_t totalLength =
    breakLength +
    1 + // start bit (high)
    payloadLength +
    1 + // stop bit (low)
    1; // minimum idle time
  static const uint8_t maxNumberOfSuccessiveHighBits =
    1 + // start bit (high)
    payloadLength;
  static const uint8_t valueOfBreakBit = LOW;
  static const uint8_t valueOfStartBit = HIGH;
  static const uint8_t valueOfStopBit = LOW;
  static const uint8_t valueOfIdleBit = HIGH;

  static const uint8_t maxNumberOfValueChanges =
    1 + // idle to break bit
    1 + // break to start bit
    8 + // payload worst case: U = 01010101
    1 + // payload worst case to stop bit
    1; // stop bit to idle
};
