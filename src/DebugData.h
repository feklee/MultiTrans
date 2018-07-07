#pragma once

struct DebugData {
  volatile uint16_t receiveBufferOverflowCount;
  volatile uint8_t numberOfElementsInReceiveBuffer;
  volatile uint16_t numberOfCollisions;
  volatile uint8_t receiveBufferStart;
  volatile uint8_t receiveBufferEnd;
};
