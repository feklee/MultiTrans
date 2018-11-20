// Stress test
//
// This sketch is for stress testing the library, i.e. to see how fast and how
// slow communication can go without errors.
//
// See `README.md` in the current directory for a detailed explanation.
//
// Written by Felix E. Klee <felix.klee@inka.de>, released into the public
// domain.

#include "MultiTrans.h"
#include "MemoryFree.h"

#include "settings.h"

#if BINARY_TRANSMISSION
#define ITEM_NAME "byte" // human readable name
typedef byte item_t;
#else
#define ITEM_NAME "character"
typedef char item_t;
#endif

static const uint8_t ledPinNumber = 13;
static const uint8_t communicationPinNumber1 = 2;
#ifdef TEST_ALL
static const uint8_t communicationPinNumber2 = 3;
static const uint8_t communicationPinNumber3 = 8;
static const uint8_t communicationPinNumber4 = 9;
#endif

static const uint8_t identificationPinNumber = 10;

using MT = MultiTrans<bitDurationExp,
                      maxNumberOfItemsPerTransmission,
                      recordDebugData,
                      customReceiveBufferSize>;
MT multiTransceiver;
MT::Transceiver<communicationPinNumber1> transceiver1;
#ifdef TEST_ALL
MT::Transceiver<communicationPinNumber2> transceiver2;
MT::Transceiver<communicationPinNumber3> transceiver3;
MT::Transceiver<communicationPinNumber4> transceiver4;
#endif

static const uint32_t timeForOtherArduinoToStartUp = 1000; // ms

#if BINARY_TRANSMISSION
static item_t set[maxNumberOfItemsPerTransmission]; // set of items to transmit
#else
static item_t set[maxNumberOfItemsPerTransmission + 1]; // incl. 0 at the end
#endif
static uint8_t sizeOfSet;

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
uint32_t countReceivedItems(uint8_t more = 0) {
  static uint32_t count = 0;
  count += more;
  return count;
}

template <typename T>
uint32_t countTransmittedItems(uint8_t more = 0) {
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

void loadSet(const uint8_t setNumber) {
#if BINARY_TRANSMISSION
  sizeOfSet = sizesOfSets[i];
  strncpy_P(set, (byte *)pgm_read_word(sets + setNumber), sizeOfSet);
#else
  strcpy_P(set, (char *)pgm_read_word(sets + setNumber));
  sizeOfSet = strlen(set);
#endif
}

template <typename T>
item_t firstReceivedItem(item_t item = 0) {
  static item_t recordedItem = 0;
  if (item != 0) {
    recordedItem = item;
  }
  return recordedItem;
}

template <typename T>
item_t lastReceivedItem(item_t item = 0) {
  static item_t recordedItem = 0;
  if (item != 0) {
    recordedItem = item;
  }
  return recordedItem;
}

template <typename T>
void errorRatioRecorderPrint(uint32_t errorsCounted) {
  uint32_t itemsCounted = countReceivedItems<T>();
  float ratio = itemsCounted == 0
    ? 0
    : float(errorsCounted) / itemsCounted;

  Serial.print(F("Error ratio (error = unexpected " ITEM_NAME "): "));
  Serial.print(ratio);
  Serial.print(F(" = "));
  Serial.print(errorsCounted);
  Serial.print(F(" / "));
  Serial.print(itemsCounted);
}

// if item position is not found, goes to the beginning
void getItemPosition(const item_t item,
                     uint8_t &setNumber,
                     uint8_t &positionInSet) {
  for (setNumber = 0; setNumber < numberOfSets; setNumber ++) {
    loadSet(setNumber);
    
#if BINARY_TRANSMISSION
    const uint8_t sizeOfSet = sizesOfSets[setNumber];
    const item_t *itemLocation = memchr(set, item, sizeOfSet);
#else
    const item_t *itemLocation = strchr(set, item);
#endif

    if (itemLocation != NULL) {
      positionInSet = (uint8_t)(itemLocation - set);
    }
  }
  setNumber = 0;
  positionInSet = 0;
}

// Returns the next item following the order of transmitted items, or returns
// the specified optional item in case the position should be synced.
template <typename T>
item_t nextExpectedItem(bool positionNeedsToBeSynced = false,
                        item_t itemToSyncTo = 0) {
  static uint8_t setNumber = 0;
  static uint8_t positionInSet = 0;

  if (positionNeedsToBeSynced) {
    getItemPosition(itemToSyncTo, setNumber, positionInSet);
    return itemToSyncTo;
  } else {
    loadSet(setNumber);
    positionInSet ++;

    if (positionInSet >= sizeOfSet) {
      // go to next set
      setNumber = (setNumber + 1) % numberOfSets;
      positionInSet = 0;
      loadSet(setNumber);
    }
  }

  return set[positionInSet];
}

template <typename T>
void syncToItem(item_t item) {
  nextExpectedItem<T>(true, item);
}

template <typename T>
void errorRatioRecorderUpdate(uint32_t &errorsCounted, item_t item) {
  static bool initialSyncIsNeeded = true;

  if (initialSyncIsNeeded) {
    syncToItem<T>(item);
    initialSyncIsNeeded = false;
    return;
  }

  bool itemIsUnexpected = item != nextExpectedItem<T>();
  if (itemIsUnexpected && countReceivedItems<T>() > 1) {
    errorsCounted ++;
    syncToItem<T>(item);
  }
}

template <typename T>
void errorRatioRecorder(item_t item, bool print) {
  static uint32_t errorsCounted = 0;

  if (print) {
    errorRatioRecorderPrint<T>(errorsCounted);
  } else {
    errorRatioRecorderUpdate<T>(errorsCounted, item);
  }
}

template <typename T>
void updateErrorRatio(item_t item) {
  errorRatioRecorder<T>(item, false);
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

  countTransmittedItems<T>(sizeOfSet);
#if BINARY_TRANSMISSION
  transceiver.startTransmissionOfBytes(set, sizeOfSet);
#else
  transceiver.startTransmissionOfCharacters(set);
#endif
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
void printInfoAboutItem(T &transceiver, item_t item) {
  Serial.print(item);
  Serial.print(F(" = "));
  Serial.print(stringFromBinary(item));
  Serial.print(F(" "));
  printErrorRatio<T>();
  Serial.println();

  if (multiTransceiver.debugDataIsRecorded) {
    reportCollisions(transceiver);
    reportReceiveBufferOverflows(transceiver);
  }
}

template <typename T>
bool noiseWhileGettingItem(T &transceiver) {
#if BINARY_TRANSMISSION
  return transceiver.noiseWhileGettingByte();
#else
  return transceiver.noiseWhileGettingCharacter();
#endif  
}

template <typename T>
void printInfoAboutNoise(T &transceiver) {
  if (noiseWhileGettingItem(transceiver)) {
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
void printReport(T &transceiver, item_t item) {
  uint8_t receiveBufferStart = transceiver.debugData.receiveBufferStart;
  uint8_t receiveBufferEnd = transceiver.debugData.receiveBufferEnd;

  printInfoAboutNoise(transceiver);
  printPinNumberPrefix(transceiver);
  if (multiTransceiver.debugDataIsRecorded) {
    Serial.print(stringFromBufferDimensions(receiveBufferStart,
                                            receiveBufferEnd));
    Serial.print(F(": "));
  }
  printInfoAboutItem<T>(transceiver, item);
}

template <typename T>
bool processNextItem(T &transceiver) {
  static bool firstReceivedItemWasRecorded = false;

#if BINARY_TRANSMISSION
  bool itemWasFound;
  item_t item = transceiver.getNextByte(itemWasFound);
#else
  item_t item = transceiver.getNextCharacter();
  bool itemWasFound = item != 0;
#endif

  if (!itemWasFound) {
    return itemWasFound;
  }

  if (!firstReceivedItemWasRecorded) {
    firstReceivedItem<T>(item);
    firstReceivedItemWasRecorded = true;
  }
  lastReceivedItem<T>(item);

  countReceivedItems<T>(1);
  countNoise<T>(noiseWhileGettingItem(transceiver) ? 1 : 0);
  updateErrorRatio<T>(item);
  if (verbose) {
    printReport<T>(transceiver, item);
  }

  return itemWasFound;
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

void processReceivedItems() {
  bool itemWasFound;
  do {
    bool itemWasFound1 = processNextItem(transceiver1);
#ifdef TEST_ALL
    bool itemWasFound2 = processNextItem(transceiver2);
    bool itemWasFound3 = processNextItem(transceiver3);
    bool itemWasFound4 = processNextItem(transceiver4);
#endif
    itemWasFound = (itemWasFound1
#ifdef TEST_ALL
                    || itemWasFound2
                    || itemWasFound3
                    || itemWasFound4
#endif
    );
  } while(itemWasFound);
}

template <typename T>
void printMeasuredRate() {
  float duration = float(durationOfTest) / 1000; // s
  uint8_t bitsPerItem = 8;
  float dRate = bitsPerItem *
    float(countReceivedItems<T>()) / duration;
  float uRate = bitsPerItem *
    float(countTransmittedItems<T>()) / duration;

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
  item_t item;

  Serial.print(F("Pin "));
  Serial.print(transceiver.pinNumber);
  Serial.println(":");

  Serial.print("  ");
  printErrorRatio<T>();
  Serial.println();

  Serial.print(F("  Number of received / transmitted " ITEM_NAME "s: "));
  Serial.print(countReceivedItems<T>());
  Serial.print(F(" / "));
  Serial.println(countTransmittedItems<T>());

  Serial.print(F("  Number of bit collisions: "));
  Serial.println(transceiver.debugData.numberOfCollisions);

  Serial.print(F("  Number of receive buffer overflows: "));
  Serial.println(transceiver.debugData.receiveBufferOverflowCount);

  Serial.print(F("  Number of elements currently in receive buffer: "));
  Serial.println(transceiver.debugData.numberOfElementsInReceiveBuffer);

  Serial.print(F("  First / Last received " ITEM_NAME ": "));
  item = firstReceivedItem<T>();
  if (item) {
    Serial.print(item);
    Serial.print(F(" = "));
  }
  Serial.print(stringFromBinary(firstReceivedItem<T>()));
  Serial.print(F(" / "));
  item = lastReceivedItem<T>();
  if (item) {
    Serial.print(item);
    Serial.print(F(" = "));
  }
  Serial.println(stringFromBinary(lastReceivedItem<T>()));

  Serial.print(
    F("  Number of times noise was detected when reading a " ITEM_NAME ": ")
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
    processReceivedItems();
  } while (millis() < endOfMinimumDelay);
}
