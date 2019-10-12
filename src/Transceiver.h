#pragma once

#include <assert.h>
#include "Arduino.h"
#include "./MultiTrans.h"
#include "./Receiver.h"
#include "./Transmitter.h"
#include "./DebugData.h"

template <uint8_t s, uint8_t t, bool u, uint8_t v, bool w, bool x>
template <uint8_t y, uint8_t z>
class MultiTrans<s, t, u, v, w, x>::Transceiver {
public:
  static const uint8_t rxPinNumber = y; // in [2, 13]
  static const uint8_t txPinNumber = z; // in [2, 13]

  // for compatibility with previous version where there were no separate RX/TX
  // pin numbers:
  static const uint8_t pinNumber = rxPinNumber;

  static const bool debugDataIsRecorded =
    MultiTrans<s, t, u, v, w, x>::debugDataIsRecorded;
  static const uint8_t maxNumberOfCharsPerTransmission = // < 13 (characters)
    MultiTrans<s, t, u, v, w, x>::maxNumberOfCharsPerTransmission;
  static const uint8_t customReceiveBufferSize =
    MultiTrans<s, t, u, v, w, x>::customReceiveBufferSize;
  static const bool dontUseInputPullupForTxPin =
    MultiTrans<s, t, u, v, w, x>::dontUseInputPullupForTxPin;
  static const bool invertTxPinValue =
    MultiTrans<s, t, u, v, w, x>::invertTxPinValue;

private:
  Transmitter<Transceiver<y, z>> _transmitter;
  Receiver<Transceiver<y, z>, rUnscaledBitDurationExp> _receiver;

public:
  static DebugData debugData;

  void begin();
  void startTransmissionOfCharacters(const char * const characters) {
    _transmitter.startTransmissionOfCharacters(characters);
  }
  void startTransmissionOfBytes(const byte * const bytes,
                                const uint8_t numberOfBytes) {
    _transmitter.startTransmissionOfBytes(bytes, numberOfBytes);
  }
  void startTransmissionOfNoise() { _transmitter.startTransmissionOfNoise(); }
  inline void handleTimer2Interrupt() __attribute__((always_inline)) {
    _transmitter.handleTimer2Interrupt();
  }
  void handleOwnPinChange(const uint16_t, const bool);
  void handlePinChangeInterrupt();
  char getNextCharacter() {
    return _receiver.shiftCharacterFromBuffer(); // 0 if there is no character
  }
  byte getNextByte(bool &byteWasFound) {
    return _receiver.shiftByteFromBuffer(byteWasFound);
  }
  bool transmissionIsInProgress() const {
    return _transmitter.transmissionIsInProgress();
  }
  bool noiseWhileGettingCharacter() const {
    return _receiver.noiseWhileGettingCharacter();
  }
  bool noiseWhileGettingByte() const {
    return _receiver.noiseWhileGettingByte();
  }
};

template <uint8_t s, uint8_t t, bool u, uint8_t v, bool w, bool x>
template <uint8_t y, uint8_t z>
DebugData MultiTrans<s, t, u, v, w, x>::Transceiver<y, z>::debugData =
  {0, 0, 0, 0, 0};

template <uint8_t s, uint8_t t, bool u, uint8_t v, bool w, bool x>
template <uint8_t y, uint8_t z>
void MultiTrans<s, t, u, v, w, x>::Transceiver<y, z>::begin() {
  _transmitter.begin();
  _receiver.begin();
}

template <uint8_t s, uint8_t t, bool u, uint8_t v, bool w, bool x>
template <uint8_t y, uint8_t z>
void MultiTrans<s, t, u, v, w, x>::Transceiver<y, z>::handleOwnPinChange(
  const uint16_t now, // in CPU cycles / prescale factor
  const bool valueAfterPinChange
) {
  bool interruptCausedByOwnTransmitter =
    _transmitter.transmissionIsInProgress() &&
    !_transmitter.isWaitingForFreeLine();

  if (!interruptCausedByOwnTransmitter) {
    _receiver.handlePinChangeInterrupt(now, valueAfterPinChange);
  }
}

template <uint8_t s, uint8_t t, bool u, uint8_t v, bool w, bool x>
template <uint8_t y, uint8_t z>
void
MultiTrans<s, t, u, v, w, x>::Transceiver<y, z>::handlePinChangeInterrupt() {
  const uint16_t now = TCNT1; // Read is done with the help of the `TEMP`
                              // register, making it atomic (as long as no
                              // interrupt is using `TEMP` as well).

  // Alternatively, `now` could be read in the top level interrupt handler.
  // However, that's not necessarily more precise, as the change of the current
  // pin may have occured after the top level interrupt handler got called.

  const bool valueAfterPinChange =
    CommunicationPin<Transceiver<y, z>, rxPinNumber>::read();
  static bool valueBeforePinChange = HIGH;

  const bool ownPinHasChanged = valueAfterPinChange != valueBeforePinChange;
  if (ownPinHasChanged) {
    handleOwnPinChange(now, valueAfterPinChange);
  }

  valueBeforePinChange = valueAfterPinChange;
}
