#pragma once

#include <assert.h>
#include "Arduino.h"
#include "MultiTrans.h"
#include "Receiver.h"
#include "Transmitter.h"
#include "DebugData.h"

template <uint8_t t, uint8_t u, bool v>
template <uint8_t w>
class MultiTrans<t, u, v>::Transceiver {
public:
  static const uint8_t pinNumber = w; // in [2, 13]
  static const bool debugDataIsRecorded =
    MultiTrans<t, u, v>::debugDataIsRecorded;
  static const uint8_t maxNumberOfCharsPerTransmission = // < 13 (characters)
    MultiTrans<t, u, v>::maxNumberOfCharsPerTransmission;

private:
  Transmitter<Transceiver<w>> _transmitter;
  Receiver<Transceiver<w>, rUnscaledBitDurationExp> _receiver;

public:
  static DebugData debugData;

  void begin();
  void startTransmissionOfCharacters(const char * const s) {
    _transmitter.startTransmissionOfCharacters(s);
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

  bool transmissionIsInProgress() const {
    return _transmitter.transmissionIsInProgress();
  }
  bool noiseWhileGettingCharacter() const {
    return _receiver.noiseWhileGettingCharacter();
  }
};

template <uint8_t t, uint8_t u, bool v>
template <uint8_t w>
DebugData MultiTrans<t, u, v>::Transceiver<w>::debugData = {0, 0, 0, 0};

template <uint8_t t, uint8_t u, bool v>
template <uint8_t w>
void MultiTrans<t, u, v>::Transceiver<w>::begin() {
  _transmitter.begin();
  _receiver.begin();
}

template <uint8_t t, uint8_t u, bool v>
template <uint8_t w>
void MultiTrans<t, u, v>::Transceiver<w>::handleOwnPinChange(
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

template <uint8_t t, uint8_t u, bool v>
template <uint8_t w>
void MultiTrans<t, u, v>::Transceiver<w>::handlePinChangeInterrupt() {
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
