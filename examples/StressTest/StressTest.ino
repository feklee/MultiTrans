// See image of board for testing: 
//
// Components for testing:
//
//   * Arduino Pro Mini, ATmega328P, 5V, 16Mhz (on some of them, I desoldered the
//     power LED)
//
//   * breadboard
//
//   * FTDI adapter
//
//   * cable to power Arduinos from USB with 5V
//
//   * jumper cables
//
//   * 470 Ω resistors (to prevent shorting in case of programming errors)
//
// Note: There is a bug with templates in Arduino IDE 1.8.5's compiler. So, use a
// compiler that comes with a newer version of the IDE.
//
// Five Arduinos are connected, each of them being a multi-channel transceiver
// (see photo of board):
//
//   * (*), the center Arduino, connected to (A) / pin 8 and (B) / pin 2, (C) /
//     pin 9, (D) / pin 3
//
//   * (A), connected to (*) / pin 3
//
//   * (B), connected to (*) / pin 2
//
//   * (C), connected to (*) / pin 9
//
//   * (D), connected to (*) / pin 8
//
// For testing, the Arduinos are first synchronized after starting up. (A), (B),
// (C), and (D) wait for signals from (*). Then all five start sending and
// receiving. The synchronization is quite primitive, and it's a good idea to
// proceed as follows:
//
//  1. Remove the FTDI and any power from all Arduinos.
//
//  2. Make sure that the FTDI is connected to the computer and that the serial
//     console is started.
//
//  3. Plug in the power connection. Eventually – possibly after step 4 – the LEDs
//     on all Arduinos should emit a fast triple-flash to indicate sync.
// 
//  4. Quickly thereafter – in order not to miss any messages – plug the FTDI into
//     the Arduino that should be monitored. (If the Arduino resets, then repeat the
//     procedure, possibly after fixing the electronic setup.)
//
// Synchronization is not strictly necessary for the test to run. It is there to
// test the rare case that all Arduinos are transmitting the exact same data in
// the exact same moment.

#include "MultiTrans.h"
#include "MemoryFree.h"

#include "settings.h"

static const uint8_t ledPinNumber = 13;
static const uint8_t communicationPinNumber1 = 2;
#ifdef TEST_ALL
static const uint8_t communicationPinNumber2 = 3;
static const uint8_t communicationPinNumber3 = 8;
static const uint8_t communicationPinNumber4 = 9;
#endif

static const uint8_t identificationPinNumber = 10;

using MT = MultiTrans<bitDurationExp,
                      maxNumberOfCharsPerTransmission,
                      recordDebugData>;
MT multiTransceiver;
MT::Transceiver<communicationPinNumber1> transceiver1;
#ifdef TEST_ALL
MT::Transceiver<communicationPinNumber2> transceiver2;
MT::Transceiver<communicationPinNumber3> transceiver3;
MT::Transceiver<communicationPinNumber4> transceiver4;
#endif

static const uint32_t timeForOtherArduinoToStartUp = 1000; // ms

static char set[maxNumberOfCharsPerTransmission + 1]; // set of characters to
                                                      // transmit

ISR(TIMER2_COMPA_vect) {
  transceiver1.handleTimer2Interrupt();
#ifdef TEST_ALL
  transceiver2.handleTimer2Interrupt();
  transceiver3.handleTimer2Interrupt();
  transceiver4.handleTimer2Interrupt();
#endif
}

ISR(PCINT2_vect) { // D0-D7
  transceiver1.handlePinChangeInterrupt();
#ifdef TEST_ALL
  transceiver2.handlePinChangeInterrupt();
#endif
}

#ifdef TEST_ALL
ISR(PCINT0_vect) { // D8-D13
  transceiver3.handlePinChangeInterrupt();
  transceiver4.handlePinChangeInterrupt();
}
#endif

void enablePinChangeInterrupts() {
  PCICR |= // Pin Change Interrupt Control Register
    bit(PCIE2) | // D0 to D7
    bit(PCIE0); // D8 to D15
}

template <typename T>
uint32_t countReceivedCharacters(uint8_t more = 0) {
  static uint32_t count = 0;
  count += more;
  return count;
}

template <typename T>
uint32_t countTransmittedCharacters(uint8_t more = 0) {
  static uint32_t count = 0;
  count += more;
  return count;
}

template <typename T>
uint32_t countNoise(uint8_t more = 0) {
  static uint32_t count = 0;
  count += more;
  return count;
}

bool randomBool() {
  return rand() % 2;
}

void flashLed(uint16_t duration = 100) {
  digitalWrite(ledPinNumber, HIGH);
  delay(duration);
  digitalWrite(ledPinNumber, LOW);
}

bool thisIsTheArduinoWithAnAsterisk() {
  pinMode(identificationPinNumber, INPUT_PULLUP);
  return !digitalRead(identificationPinNumber);
}

bool thisArduinoHasToWaitForSync() {
  return !thisIsTheArduinoWithAnAsterisk();
}

void loadSet(const uint8_t i) {
  strcpy_P(set, (char*)pgm_read_word(&(setsOfCharacters[i])));
}

template <typename T>
char firstReceivedCharacter(char character = 0) {
  static char recordedCharacter = 0;
  if (character != 0) {
    recordedCharacter = character;
  }
  return recordedCharacter;
}

template <typename T>
char lastReceivedCharacter(char character = 0) {
  static char recordedCharacter = 0;
  if (character != 0) {
    recordedCharacter = character;
  }
  return recordedCharacter;
}

template <typename T>
void errorRatioRecorderPrint(uint32_t errorsCounted) {
  uint32_t charactersCounted = countReceivedCharacters<T>();
  float ratio = charactersCounted == 0
    ? 0
    : float(errorsCounted) / charactersCounted;

  Serial.print(F("Error ratio (error = unexpected character): "));
  Serial.print(ratio);
  Serial.print(F(" = "));
  Serial.print(errorsCounted);
  Serial.print(F(" / "));
  Serial.print(charactersCounted);
}

bool getCharacterPosition(const char character,
                          uint8_t &setNumber,
                          uint8_t &positionInSet) {
  for (setNumber = 0; setNumber < numberOfSets; setNumber ++) {
    loadSet(setNumber);
    const char *characterLocation = strchr(set, character);
    if (characterLocation != NULL) {
      positionInSet = (uint8_t)(characterLocation - set);
      return true;
    }
  }
  setNumber = 0;
  positionInSet = 0;
  return false;
}

// Returns the next expected character, or the specified optional character,
// which also syncs the position.
template <typename T>
char nextExpectedCharacter(char characterToSyncTo = 0) {
  static uint8_t setNumber = 0;
  static uint8_t positionInSet = 0;

  bool positionNeedsToBeSynced = characterToSyncTo != 0;
  if (positionNeedsToBeSynced) {
    bool gotCharacterPosition = getCharacterPosition(characterToSyncTo,
                                                     setNumber, positionInSet);
    if (!gotCharacterPosition) {
      return 0;
    }
  } else {
    loadSet(setNumber);
    positionInSet ++;
    if (positionInSet >= strlen(set)) {
      setNumber = (setNumber + 1) % numberOfSets;
      positionInSet = 0;
      loadSet(setNumber);
    }
  }

  return set[positionInSet];
}

template <typename T>
void errorRatioRecorderUpdate(uint32_t &errorsCounted,
                              char character) {
  static bool initialSyncIsNeeded = true;

  if (initialSyncIsNeeded) {
    nextExpectedCharacter<T>(character);
    initialSyncIsNeeded = false;
    return;
  }

  bool characterIsUnexpected = character != nextExpectedCharacter<T>();
  if (characterIsUnexpected && countReceivedCharacters<T>() > 1) {
    errorsCounted ++;
    nextExpectedCharacter<T>(character);
  }
}

template <typename T>
void errorRatioRecorder(char character, bool print) {
  static uint32_t errorsCounted = 0;

  if (print) {
    errorRatioRecorderPrint<T>(errorsCounted);
  } else {
    errorRatioRecorderUpdate<T>(errorsCounted, character);
  }
}

template <typename T>
void updateErrorRatio(char character) {
  errorRatioRecorder<T>(character, false);
}

template <typename T>
void printErrorRatio() {
  errorRatioRecorder<T>(0, true);
}

void pullUpCommunicationPins() {
  pinMode(communicationPinNumber1, INPUT_PULLUP);
#ifdef TEST_ALL
  pinMode(communicationPinNumber2, INPUT_PULLUP);
  pinMode(communicationPinNumber3, INPUT_PULLUP);
  pinMode(communicationPinNumber4, INPUT_PULLUP);
#endif
}

void indicateSyncDone() {
  Serial.println(F("done"));
  flashLed(50);
  delay(50);
  flashLed(50);
  delay(50);
  flashLed(50);
}

void waitForSync() {
  pullUpCommunicationPins();
  delay(timeForOtherArduinoToStartUp);

  Serial.print(F("Waiting for sync..."));
  pinMode(communicationPinNumber1, INPUT_PULLUP);
#ifdef TEST_ALL
  pinMode(communicationPinNumber2, INPUT_PULLUP);
  pinMode(communicationPinNumber3, INPUT_PULLUP);
  pinMode(communicationPinNumber4, INPUT_PULLUP);
#endif
  while (
    digitalRead(communicationPinNumber1) == HIGH
#ifdef TEST_ALL
    && digitalRead(communicationPinNumber2) == HIGH
    && digitalRead(communicationPinNumber3) == HIGH
    && digitalRead(communicationPinNumber4) == HIGH
#endif
  ) {}
  indicateSyncDone();
}

void initiateSync() {
  pullUpCommunicationPins();
  delay(timeForOtherArduinoToStartUp);
  delay(1000);

  Serial.print(F("Initiating sync..."));
  pinMode(communicationPinNumber1, OUTPUT);
  digitalWrite(communicationPinNumber1, LOW);
#ifdef TEST_ALL
  pinMode(communicationPinNumber2, OUTPUT);
  digitalWrite(communicationPinNumber2, LOW);
  pinMode(communicationPinNumber3, OUTPUT);
  digitalWrite(communicationPinNumber3, LOW);
  pinMode(communicationPinNumber4, OUTPUT);
  digitalWrite(communicationPinNumber4, LOW);
#endif
  indicateSyncDone();
}

// E.g. in over current situations, the Arduino may restart. Flashing the LED
// shows when a restart is happening.
void indicateStartup() {
  flashLed();
  delay(100);
  flashLed();
}

void printStartupInformation() {
  printMemoryUsage(); // Initial use interesting in case of crash

  Serial.print(
    F("Test duration after initial sync (indicated by tripple flash): "));
  Serial.print(durationOfTest);
  Serial.println(F(" ms"));
}

void setup() {
  pinMode(ledPinNumber, OUTPUT);
  indicateStartup();

  Serial.begin(9600);
  printStartupInformation();

  if (arduinosShouldBeSynchronized) {
    if (thisArduinoHasToWaitForSync()) {
      waitForSync();
    } else {
      initiateSync();
    }
  }

  multiTransceiver.startTimer1();
  multiTransceiver.startTimer2();
  enablePinChangeInterrupts();

  transceiver1.begin();
#ifdef TEST_ALL
  transceiver2.begin();
  transceiver3.begin();
  transceiver4.begin();
#endif

  uint32_t timeToWaitBeforeInitialTransmit = 10; // ms
  delay(timeToWaitBeforeInitialTransmit);
}

template <typename T>
void transmitNextSet(T &transceiver) {
  static uint8_t i = 0;
 
  loadSet(i);
  if (verbose) {
    flashLed();
    printPinNumberPrefix(transceiver);
    Serial.print(F("Starting transmission of: "));
    Serial.println(set);
  }
  countTransmittedCharacters<T>(strlen(set));
  transceiver.startTransmissionOfCharacters(set);
  i = (i + 1) % numberOfSets;
}

const char *stringFromBinary(uint8_t x) {
  static char s[9];
  uint8_t i = 0;
  for (i = 0; i < 7; i ++) {
    uint8_t j = 7 - i;
    s[i] = (x & (1 << j)) ? '1' : '0';
  }
  s[i] = '\0';
  return s;
}

const char *stringFromBufferDimensions(
  uint8_t receiveBufferStart,
  uint8_t receiveBufferEnd
) {
  static char s[11];
  sprintf(s, "[%3d, %3d]", receiveBufferStart, receiveBufferEnd);
  return s;
}

void printDataRate() {
  Serial.print(F("Data rate / Effective data rate: "));
  Serial.print(multiTransceiver.baudRate);
  Serial.print(F(" baud / "));
  Serial.print(multiTransceiver.effectiveDataRate);
  Serial.println(F(" bit/s"));
  Serial.print(F("Bit duration exponent for transmitter: "));
  Serial.print(multiTransceiver.tPrescaleFactorExp);
  Serial.print(F(" + "));
  Serial.print(multiTransceiver.tUnscaledBitDurationExp);
  Serial.print(F(", for receiver: "));
  Serial.print(multiTransceiver.rPrescaleFactorExp);
  Serial.print(F(" + "));
  Serial.println(multiTransceiver.rUnscaledBitDurationExp);
}

void printMemoryUsage() {
  Serial.print(F("Free memory: "));
  Serial.println(freeMemory());
}

template <typename T>
void printInfoAboutCharacter(T &transceiver, char character) {
  Serial.print(character);
  Serial.print(F(" = "));
  Serial.print(stringFromBinary(character));
  Serial.print(F(" "));
  printErrorRatio<T>();
  Serial.println();

  if (multiTransceiver.debugDataIsRecorded) {
    reportCollisions(transceiver);
    reportReceiveBufferOverflows(transceiver);
  }
}

template <typename T>
void printInfoAboutNoise(T &transceiver) {
  if (transceiver.noiseWhileGettingCharacter()) {
    Serial.print(F("Noise has been detected on pin "));
    Serial.println(transceiver.pinNumber);
  }
}

template <typename T>
void printPinNumberPrefix(T &transceiver) {
  Serial.print(F("Pin "));
  Serial.print(transceiver.pinNumber);
  Serial.print(F(": "));
}

template <typename T>
void printReport(T &transceiver, char character) {
  uint8_t receiveBufferStart = transceiver.debugData.receiveBufferStart;
  uint8_t receiveBufferEnd = transceiver.debugData.receiveBufferEnd;

  printInfoAboutNoise(transceiver);
  printPinNumberPrefix(transceiver);
  if (multiTransceiver.debugDataIsRecorded) {
    Serial.print(stringFromBufferDimensions(receiveBufferStart,
                                            receiveBufferEnd));
    Serial.print(F(": "));
  }
  printInfoAboutCharacter<T>(transceiver, character);
}

template <typename T>
bool processNextCharacter(T &transceiver) {
  static bool firstReceivedCharacterRecorded = false;
  char character = transceiver.getNextCharacter();
  bool characterWasFound = character != 0;

  if (!characterWasFound) {
    return characterWasFound;
  }

  if (!firstReceivedCharacterRecorded) {
    firstReceivedCharacter<T>(character);
    firstReceivedCharacterRecorded = true;
  }
  lastReceivedCharacter<T>(character);

  countReceivedCharacters<T>(1);
  countNoise<T>(transceiver.noiseWhileGettingCharacter() ? 1 : 0);
  updateErrorRatio<T>(character);
  if (verbose) {
    printReport<T>(transceiver, character);
  }

  return characterWasFound;
}

template <typename T>
void transmitNoise(T &transceiver) {
  if (verbose) {
    printPinNumberPrefix(transceiver);
    Serial.println(F("Starting transmission of noise."));
  }
  transceiver.startTransmissionOfNoise();
}

template <typename T>
void transmitSomething(T &transceiver) {
  const bool noiseShouldBeInserted =
    noiseShouldBeRandomlyInserted ? randomBool() : false;

  if (noiseShouldBeInserted) {
    transmitNoise(transceiver);
  } else {
    transmitNextSet(transceiver);
  }
}

template <typename T>
void transmitIfPossible(T &transceiver) {
  if (!transceiver.transmissionIsInProgress()) {
    transmitSomething(transceiver);
  }
}

void transmitWherePossible() {
  transmitIfPossible(transceiver1);
#ifdef TEST_ALL
  transmitIfPossible(transceiver2);
  transmitIfPossible(transceiver3);
  transmitIfPossible(transceiver4);
#endif
}

template <typename T>
void reportCollisions(T &transceiver) {
  static uint16_t oldNumberOfCollisions = 0;
  uint16_t numberOfCollisions = transceiver.debugData.numberOfCollisions;

  if (numberOfCollisions == oldNumberOfCollisions) {
    return;
  }

  printPinNumberPrefix(transceiver);
  Serial.print(F("Number of collisions increased to: "));
  Serial.println(numberOfCollisions);
  oldNumberOfCollisions = numberOfCollisions;
}

template <typename T>
void reportReceiveBufferOverflows(T &transceiver) {
  static uint16_t oldReceiveBufferOverflowCount = 0;
  uint16_t receiveBufferOverflowCount =
    transceiver.debugData.receiveBufferOverflowCount;

  if (receiveBufferOverflowCount == oldReceiveBufferOverflowCount) {
    return;
  }
  printPinNumberPrefix(transceiver);
  Serial.print(F("Number of receive buffer overflows increased to: "));
  Serial.println(receiveBufferOverflowCount);
  oldReceiveBufferOverflowCount = receiveBufferOverflowCount;
}

void processReceivedCharacters() {
  bool characterWasFound;
  do {
    bool characterWasFound1 = processNextCharacter(transceiver1);
#ifdef TEST_ALL
    bool characterWasFound2 = processNextCharacter(transceiver2);
    bool characterWasFound3 = processNextCharacter(transceiver3);
    bool characterWasFound4 = processNextCharacter(transceiver4);
#endif
    characterWasFound = (characterWasFound1
#ifdef TEST_ALL
                         || characterWasFound2
                         || characterWasFound3
                         || characterWasFound4
#endif
    );
  } while(characterWasFound);
}

template <typename T>
void printMeasuredRate() {
  float duration = float(durationOfTest) / 1000; // s
  uint8_t bitsPerCharacter = 8;
  float dRate = bitsPerCharacter *
    float(countReceivedCharacters<T>()) / duration;
  float uRate = bitsPerCharacter *
    float(countTransmittedCharacters<T>()) / duration;

  Serial.print(F("  Measured data rate (downstream + upstream): "));
  Serial.print(dRate);
  Serial.print(" bit/s + ");
  Serial.print(uRate);
  Serial.print(" bit/s = ");
  Serial.print(dRate + uRate);
  Serial.println(" bit/s");
}

template <typename T>
void printTestSummary(T &transceiver) {
  Serial.print(F("Pin "));
  Serial.print(transceiver.pinNumber);
  Serial.println(":");

  Serial.print("  ");
  printErrorRatio<T>();
  Serial.println();

  Serial.print(F("  Number of received / transmitted characters: "));
  Serial.print(countReceivedCharacters<T>());
  Serial.print(F(" / "));
  Serial.println(countTransmittedCharacters<T>());

  Serial.print(F("  Number of bit collisions: "));
  Serial.println(transceiver.debugData.numberOfCollisions);

  Serial.print(F("  Number of receive buffer overflows: "));
  Serial.println(transceiver.debugData.receiveBufferOverflowCount);

  Serial.print(F("  Number of elements currently in receive buffer: "));
  Serial.println(transceiver.debugData.numberOfElementsInReceiveBuffer);

  Serial.print(F("  First / Last received character: "));
  Serial.print(firstReceivedCharacter<T>());
  Serial.print(F(" = "));
  Serial.print(stringFromBinary(firstReceivedCharacter<T>()));
  Serial.print(F(" / "));
  Serial.print(lastReceivedCharacter<T>());
  Serial.print(F(" = "));
  Serial.println(stringFromBinary(lastReceivedCharacter<T>()));

  Serial.print(
    F("  Number of times noise was detected when reading a character: ")
  );
  Serial.println(countNoise<T>());

  printMeasuredRate<T>();
}

void printTestSummary() {
  printDataRate();
  printMemoryUsage();
  printTestSummary(transceiver1);
#ifdef TEST_ALL
  printTestSummary(transceiver2);
  printTestSummary(transceiver3);
  printTestSummary(transceiver4);
#endif
}

void loop() {
  static bool testIsRunning = true;

  if (!testIsRunning) {
    return;
  }

  bool testHasEnded = millis() > durationOfTest;
  if (testHasEnded) {
    Serial.println("Test has ended!");
    printTestSummary();
    testIsRunning = false;
    return;
  }

  transmitWherePossible();

  uint32_t endOfMinimumDelay = millis() + durationOfMinimumDelay;
  do {
    processReceivedCharacters();
  } while (millis() < endOfMinimumDelay);
}
