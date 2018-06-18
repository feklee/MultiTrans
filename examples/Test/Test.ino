// Felix E. Klee <felix.klee@inka.de>

#include <EEPROM.h>
#include "Transceiver.h"
#include "CharacterEncoding.h"
#include "MemoryFree.h"

#include "config.h"

static const uint8_t ledPinNumber = 13;
static const uint8_t communicationPinNumber1 = 2;
static const uint8_t communicationPinNumber2 = 3;
static const uint8_t communicationPinNumber3 = 8;
static const uint8_t communicationPinNumber4 = 9;

using MT = MultiTrans<bitDurationExp,
                      maxNumberOfCharsPerTransmission,
                      recordDebugData>;
MT multiTransceiver;
MT::Transceiver<communicationPinNumber1> transceiver1;
MT::Transceiver<communicationPinNumber2> transceiver2;
MT::Transceiver<communicationPinNumber3> transceiver3;
MT::Transceiver<communicationPinNumber4> transceiver4;

static char id;

static const uint32_t timeForOtherArduinoToStartUp = 1000; // ms

static char set[maxNumberOfCharsPerTransmission + 1]; // set of characters to
                                                      // transmit

ISR(TIMER2_COMPA_vect) {
  transceiver1.handleTimer2Interrupt();
  transceiver2.handleTimer2Interrupt();
  transceiver3.handleTimer2Interrupt();
  transceiver4.handleTimer2Interrupt();
}

ISR(PCINT2_vect) { // D0-D7
  transceiver1.handlePinChangeInterrupt();
  transceiver2.handlePinChangeInterrupt();
}

ISR(PCINT0_vect) { // D8-D13
  transceiver3.handlePinChangeInterrupt();
  transceiver4.handlePinChangeInterrupt();
}

bool randomBool() {
  return rand() % 2;
}

void flashLed() {
  digitalWrite(ledPinNumber, HIGH);
  delay(100);
  digitalWrite(ledPinNumber, LOW);
}

bool thisArduinoHasToWaitForSync() {
  return id != '*';
}

void loadSet(const uint8_t i) {
  strcpy_P(set, (char*)pgm_read_word(&(setsOfCharacters[i])));
}

void printErrorRatio(uint32_t errorsCounted, uint32_t charactersCounted) {
  float ratio = charactersCounted == 0
    ? 0
    : float(errorsCounted) / charactersCounted;

  Serial.print(F(" Error ratio w/o noise: "));
  Serial.print(ratio);
  Serial.print(F(" = "));
  Serial.print(errorsCounted);
  Serial.print(F(" / "));
  Serial.print(charactersCounted);
}

void getCharacterPosition(const char character, 
                          uint8_t &setNumber,
                          uint8_t &positionInSet) {
  for (setNumber = 0; setNumber < numberOfSets; setNumber ++) {
    loadSet(setNumber);
    const char *characterLocation = strchr(set, character);
    if (characterLocation != NULL) {
      positionInSet = (uint8_t)(characterLocation - set);
      return;
    }
  }
}

template <typename T>
char nextExpectedCharacter(char characterToStartFrom = 0) {
  static uint8_t setNumber = 0;
  static uint8_t positionInSet = 0;

  if (characterToStartFrom != 0) {
    getCharacterPosition(characterToStartFrom,
                         setNumber, positionInSet);
  }

  loadSet(setNumber);
  positionInSet ++;
  if (positionInSet >= strlen(set)) {
    setNumber = (setNumber + 1) % numberOfSets;
    positionInSet = 0;
    loadSet(setNumber);
  }

  return set[positionInSet];
}

template <typename T>
void reportErrorRatio(char character) {
  static uint32_t errorsCounted = 0;
  static uint32_t charactersCounted = 0;
  static bool lastCharacterWasUnexpected = false;
  static char lastCharacter = 0;

  char expectedCharacter =
    lastCharacterWasUnexpected ?
    nextExpectedCharacter<T>(lastCharacter) :
    nextExpectedCharacter<T>();

  bool characterIsUnexpected = character != expectedCharacter;
  charactersCounted ++;
  if (characterIsUnexpected && charactersCounted > 1) {
    errorsCounted ++;
  }

  printErrorRatio(errorsCounted, charactersCounted);

  lastCharacter = character;
  lastCharacterWasUnexpected = characterIsUnexpected;
}

void pullUpCommunicationPins() {
  pinMode(communicationPinNumber1, INPUT_PULLUP);
  pinMode(communicationPinNumber2, INPUT_PULLUP);
  pinMode(communicationPinNumber3, INPUT_PULLUP);
  pinMode(communicationPinNumber4, INPUT_PULLUP);
}

void waitForSync() {
  pullUpCommunicationPins();
  delay(timeForOtherArduinoToStartUp);

  Serial.print(F("Waiting for sync..."));
  pinMode(communicationPinNumber1, INPUT_PULLUP);
  pinMode(communicationPinNumber2, INPUT_PULLUP);
  pinMode(communicationPinNumber3, INPUT_PULLUP);
  pinMode(communicationPinNumber4, INPUT_PULLUP);
  while (
    digitalRead(communicationPinNumber1) == HIGH &&
    digitalRead(communicationPinNumber2) == HIGH &&
    digitalRead(communicationPinNumber3) == HIGH &&
    digitalRead(communicationPinNumber4) == HIGH
  ) {}
  Serial.println(F("done"));
}

void initiateSync() {
  pullUpCommunicationPins();
  delay(timeForOtherArduinoToStartUp);
  delay(1000);

  Serial.print(F("Initiating sync..."));
  pinMode(communicationPinNumber1, OUTPUT);
  digitalWrite(communicationPinNumber1, LOW);
  pinMode(communicationPinNumber2, OUTPUT);
  digitalWrite(communicationPinNumber2, LOW);
  pinMode(communicationPinNumber3, OUTPUT);
  digitalWrite(communicationPinNumber3, LOW);
  pinMode(communicationPinNumber4, OUTPUT);
  digitalWrite(communicationPinNumber4, LOW);
  Serial.println(F("done"));
}

void setup() {
  Serial.begin(9600);

  id = EEPROM.read(0);

  if (arduinosShouldBeSynchronized) {
    if (thisArduinoHasToWaitForSync()) {
      waitForSync();
    } else {
      initiateSync();
    }
  }

  pinMode(ledPinNumber, OUTPUT);

  multiTransceiver.startTimer1();
  multiTransceiver.startTimer2();
  multiTransceiver.enablePinChangeInterrupts();

  transceiver1.begin();
  transceiver2.begin();
  transceiver3.begin();
  transceiver4.begin();

  uint32_t timeToWaitBeforeInitialTransmit = 10; // ms
  delay(timeToWaitBeforeInitialTransmit);
}

template <typename T>
void transmitNextSet(T &transceiver) {
  static uint8_t i = 0;

  loadSet(i);
  flashLed();
  printPinNumberPrefix(transceiver);
  Serial.print(F("Starting transmission of: "));
  Serial.println(set);
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
  Serial.print(F("Data rate: "));
  Serial.print(multiTransceiver.baudRate);
  Serial.print(F(" baud, effective data rate: "));
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

void printGeneralInfoFromTimeToTime() {
  static unsigned long lastTime = millis(); // ms
  unsigned long elapsedTime = millis() - lastTime; // ms
  if (elapsedTime > 2000) {
    printDataRate();
    printMemoryUsage();
    lastTime = millis();
  }
}

template <typename T>
void printInformationAboutCharacter(T &transceiver, char character) {
  Serial.print(character);
  Serial.print(F(" = "));
  Serial.print(stringFromBinary(character));
  reportErrorRatio<T>(character);
  Serial.println();

  if (multiTransceiver.debugDataIsRecorded) {
    reportCollisions(transceiver);
    reportReceiveBufferOverflows(transceiver);
  }
}

template <typename T>
void reportNoise(T &transceiver) {
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
bool processNextCharacter(T &transceiver) {
  uint8_t receiveBufferStart = transceiver.debugData.receiveBufferStart;
  uint8_t receiveBufferEnd = transceiver.debugData.receiveBufferEnd;

  char character = transceiver.getNextCharacter();
  bool characterWasFound = character != 0;
  if (characterWasFound) {
    reportNoise(transceiver);
    printPinNumberPrefix(transceiver);
    if (multiTransceiver.debugDataIsRecorded) {
      Serial.print(stringFromBufferDimensions(receiveBufferStart,
                                              receiveBufferEnd));
      Serial.print(F(": "));
    }
    printInformationAboutCharacter<T>(transceiver, character);
  }
  return characterWasFound;
}

template <typename T>
void transmitNoise(T &transceiver) {
  printPinNumberPrefix(transceiver);
  Serial.print(F("Starting transmission of noise."));
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
  transmitIfPossible(transceiver2);
  transmitIfPossible(transceiver3);
  transmitIfPossible(transceiver4);
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
    bool characterWasFound2 = processNextCharacter(transceiver2);
    bool characterWasFound3 = processNextCharacter(transceiver3);
    bool characterWasFound4 = processNextCharacter(transceiver4);
    characterWasFound = (characterWasFound1 ||
                         characterWasFound2 ||
                         characterWasFound3 ||
                         characterWasFound4);
  } while(characterWasFound);
}

void loop() {
  printGeneralInfoFromTimeToTime();

  transmitWherePossible();

  uint32_t endOfMinimumDelay = millis() + durationOfMinimumDelay;
  while (millis() < endOfMinimumDelay) {
    processReceivedCharacters();
  }
}