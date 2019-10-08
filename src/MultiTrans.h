#ifndef MultiTrans_h
#define MultiTrans_h

#include "Arduino.h"
#include "./CharacterEncoding.h"

#ifndef __AVR__
#warning "This library has not been tested with your board."
#endif

template <uint8_t t, uint8_t u, bool v = false, uint8_t w = 0>
class MultiTrans {
private:
  static_assert(t <= 18, "Bit duration is too long.");
  static_assert(u <= 12,
                "Too high maximum number characters per transmission.");

  // Bit duration (in CPU cycles): 2^bitDurationExp
  //
  // Baud rate (in bits / time unit): CPU clock speed / bit duration
  static const uint8_t bitDurationExp = t; // < 18

  static const uint8_t maxNumberOfCharsPerTransmission = u;

  static uint8_t rPrescaleBits();
  static uint8_t tPrescaleBits();
  static void configureTimer2();
  static void enableTimer2Interrupt();

public:
  static const bool debugDataIsRecorded = v;
  static const uint32_t bitDuration;
  static const float baudRate;
  static const float effectiveDataRate;

  // 0: compute receiver buffer size automatically based on number of characters
  static const uint8_t customReceiveBufferSize = w;

  // Prefixes: `t` = transmitter, `r` = receiver
  static const uint8_t tUnscaledBitDurationExp; // < 8
  static const uint8_t tPrescaleFactorExp; // 0, 3, 5, 6, 7, 8, or 10
  static const uint8_t rUnscaledBitDurationExp; // < 16
  static const uint8_t rPrescaleFactorExp; // 0, 3, 6, 8, or 10

  template <uint8_t, uint8_t> class Transceiver;

  static void startTimer1();
  static void startTimer2();
};

template <uint8_t t, uint8_t u, bool v, uint8_t w>
// Transmit prescaling should be as large as possible (to maximize the maximum
// possible duration):
const uint8_t MultiTrans<t, u, v, w>::tPrescaleFactorExp =
  (MultiTrans<t, u, v, w>::bitDurationExp >= 10) ? 10 :
  (MultiTrans<t, u, v, w>::bitDurationExp >= 8) ? 8 :
  (MultiTrans<t, u, v, w>::bitDurationExp >= 7) ? 7 :
  (MultiTrans<t, u, v, w>::bitDurationExp >= 6) ? 6 :
  (MultiTrans<t, u, v, w>::bitDurationExp >= 5) ? 5 :
  (MultiTrans<t, u, v, w>::bitDurationExp >= 3) ? 3 : 0;

template <uint8_t t, uint8_t u, bool v, uint8_t w>
const uint8_t MultiTrans<t, u, v, w>::tUnscaledBitDurationExp =
  MultiTrans<t, u, v, w>::bitDurationExp -
  MultiTrans<t, u, v, w>::tPrescaleFactorExp;

// Receive prescaling should be as small as possible (for maximum precision),
// but long enough to count a break (see character encoding):
template <uint8_t t, uint8_t u, bool v, uint8_t w>
const uint8_t MultiTrans<t, u, v, w>::rPrescaleFactorExp =
  (MultiTrans<t, u, v, w>::bitDurationExp >=
   8 // previous prescale factor, which may not be sufficient (see next section)
   + 16 // >= 2^16 would not fit in an `uint16_t`
   - CharacterEncoding::ceilOfBreakLengthExp // divides by number of character
                                             // bits needed to count break,
                                             // rounded up
  ) ? 10 :
  (MultiTrans<t, u, v, w>::bitDurationExp >=
   6 + 16 - CharacterEncoding::ceilOfBreakLengthExp) ? 8 :
  (MultiTrans<t, u, v, w>::bitDurationExp >=
   3 + 16 - CharacterEncoding::ceilOfBreakLengthExp) ? 6 :
  (MultiTrans<t, u, v, w>::bitDurationExp >=
   0 + 16 - CharacterEncoding::ceilOfBreakLengthExp) ? 3 :
  0;

template <uint8_t t, uint8_t u, bool v, uint8_t w>
const uint8_t MultiTrans<t, u, v, w>::rUnscaledBitDurationExp =
  MultiTrans<t, u, v, w>::bitDurationExp -
  MultiTrans<t, u, v, w>::rPrescaleFactorExp;

template <uint8_t t, uint8_t u, bool v, uint8_t w>
const uint32_t MultiTrans<t, u, v, w>::bitDuration =
  1ul << MultiTrans<t, u, v, w>::bitDurationExp;

template <uint8_t t, uint8_t u, bool v, uint8_t w>
const float MultiTrans<t, u, v, w>::baudRate =
  float(F_CPU) / MultiTrans<t, u, v, w>::bitDuration;

template <uint8_t t, uint8_t u, bool v, uint8_t w>
const float MultiTrans<t, u, v, w>::effectiveDataRate =
  baudRate * CharacterEncoding::payloadLength / CharacterEncoding::totalLength;

template <uint8_t t, uint8_t u, bool v, uint8_t w>
byte MultiTrans<t, u, v, w>::rPrescaleBits() {
  const uint16_t rPrescaleFactor = 1 << rPrescaleFactorExp;

  switch (rPrescaleFactor) {
  case 1:
    return bit(CS10);
  case 8:
    return bit(CS11);
  case 64:
    return bit(CS11) | bit(CS10);
  case 256:
    return bit(CS12);
  case 1024:
    return bit(CS12) | bit(CS10);
  }
  return 0;
}

// for receiving
template <uint8_t t, uint8_t u, bool v, uint8_t w>
void MultiTrans<t, u, v, w>::startTimer1() {
  TCCR1A = 0; // normal operation
  TCCR1B = rPrescaleBits();
  TCCR1C = 0;
  OCR1A = 0;
  OCR1B = 0;
  TIMSK1 = 0; // no interrupts
}

template <uint8_t t, uint8_t u, bool v, uint8_t w>
uint8_t MultiTrans<t, u, v, w>::tPrescaleBits() {
  const uint16_t prescaleFactor = 1 << tPrescaleFactorExp;

  switch (prescaleFactor) {
  case 1:
    return bit(CS20);
  case 8:
    return bit(CS21);
  case 32:
    return bit(CS21) | bit(CS20);
  case 64:
    return bit(CS22);
  case 128:
    return bit(CS22) | bit(CS20);
  case 256:
    return bit(CS22) | bit(CS21);
  case 1024:
    return bit(CS22) | bit(CS21) | bit(CS20);
  }

  return 0;
}

template <uint8_t t, uint8_t u, bool v, uint8_t w>
void MultiTrans<t, u, v, w>::configureTimer2() {
  // Timer control registers:
  TCCR2A = 0;
  TCCR2B = tPrescaleBits();

  // Output compare registers:
  const uint16_t unscaledBitDuration =
    1 << tUnscaledBitDurationExp; // in CPU cycles
  OCR2A = unscaledBitDuration - 1;
  OCR2B = 0;

  TCCR2A = bit(WGM21); // CTC - Clear Timer on Compare
}

template <uint8_t t, uint8_t u, bool v, uint8_t w>
void MultiTrans<t, u, v, w>::enableTimer2Interrupt() {
  TIMSK2 = bit(OCIE2A); // Output Compare A Match Interrupt Enable
}

// for transmitting
template <uint8_t t, uint8_t u, bool v, uint8_t w>
void MultiTrans<t, u, v, w>::startTimer2() {
  configureTimer2();
  enableTimer2Interrupt();
}

#include "Transceiver.h"

#endif
