#pragma once

#include <assert.h>
#include "Arduino.h"
#include "./MultiTrans.h"
#include "./Receiver.h"
#include "./Transmitter.h"
#include "./DebugData.h"

template <uint8_t t, uint8_t u, bool v, uint8_t w>
template <uint8_t x, uint8_t y = x>
class MultiTrans<t, u, v, w>::Transceiver {
public:
  static const uint8_t txPinNumber = x; // in [2, 13]
  static const uint8_t rxPinNumber = y; // in [2, 13]
  static const bool debugDataIsRecorded =
    MultiTrans<t, u, v, w>::debugDataIsRecorded;
  static const uint8_t maxNumberOfCharsPerTransmission = // < 13 (characters)
    MultiTrans<t, u, v, w>::maxNumberOfCharsPerTransmission;
  static const uint8_t customReceiveBufferSize =
    MultiTrans<t, u, v, w>::customReceiveBufferSize;

private:
  Transmitter<Transceiver<x, y>> _transmitter;
  Receiver<Transceiver<x, y>, rUnscaledBitDurationExp> _receiver;

public:
  static DebugData debugData;

  void begin();
  void startTransmissionOfCharacters(const char * const s) {
    _transmitter.startTransmissionOfCharacters(s);
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

template <uint8_t t, uint8_t u, bool v, uint8_t w>
template <uint8_t x>
DebugData MultiTrans<t, u, v, w>::Transceiver<x, y>::debugData =
  {0, 0, 0, 0, 0};

template <uint8_t t, uint8_t u, bool v, uint8_t w>
template <uint8_t x>
void MultiTrans<t, u, v, w>::Transceiver<x, y>::begin() {
  _transmitter.begin();
  _receiver.begin();
}

template <uint8_t t, uint8_t u, bool v, uint8_t w>
template <uint8_t x>
void MultiTrans<t, u, v, w>::Transceiver<x, y>::handleOwnPinChange(
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

template <uint8_t t, uint8_t u, bool v, uint8_t w>
template <uint8_t x>
void MultiTrans<t, u, v, w>::Transceiver<x, y>::handlePinChangeInterrupt() {
  const uint16_t now = TCNT1; // Read is done with the help of the `TEMP`
                              // register, making it atomic (as long as no
                              // interrupt is using `TEMP` as well).

  // Alternatively, `now` could be read from the top level interrupt handler.
  // However, that's not necessarily more precise, as the change of the current
  // pin may have occured after the top level interrupt handler got called.

  const bool valueAfterPinChange = CommunicationPin<pinNumber>::read();
  static bool valueBeforePinChange = HIGH;

  const bool ownPinHasChanged = valueAfterPinChange != valueBeforePinChange;
  if (ownPinHasChanged) {
    handleOwnPinChange(now, valueAfterPinChange);
  }

  valueBeforePinChange = valueAfterPinChange;
}
