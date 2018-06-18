#pragma once

// #define NDEBUG

struct {
  const bool arduinosShouldBeSynchronized = true;

  // There is a minimum delay between transmissions to give the other side time
  // to process the received characters:
  const uint32_t durationOfMinimumDelay = 1000; // ms

  const bool noiseShouldBeRandomlyInserted = true;

  const uint8_t tUnscaledBitDurationExp = 7;
  const uint8_t tPrescaleFactorExp = 3;
  const uint8_t rUnscaledBitDurationExp = 7;
  const uint8_t rPrescaleFactorExp = 3;
} settings;
