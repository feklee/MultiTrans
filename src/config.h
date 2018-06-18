// Felix E. Klee <felix.klee@inka.de>

const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 1500; // ms
const bool noiseShouldBeRandomlyInserted = false;
const bool recordDebugData = false;
const uint8_t bitDurationExp = 10; // < 18

const uint8_t maxNumberOfCharsPerTransmission = 8; // characters (< 13)

// Sets of characters with max. set size 8:
static const uint8_t numberOfSets = 17;
static const char set_0[] PROGMEM = "} ^Y54\"~";
static const char set_1[] PROGMEM = "FB{T";
static const char set_2[] PROGMEM = "c";
static const char set_3[] PROGMEM = "O)z_<*W@";
static const char set_4[] PROGMEM = "QJ>G";
static const char set_5[] PROGMEM = "=An+btD|";
static const char set_6[] PROGMEM = "o%";
static const char set_7[] PROGMEM = "6RE";
static const char set_8[] PROGMEM = "'2?p!&Z$";
static const char set_9[] PROGMEM = "7iqx0adM";
static const char set_10[] PROGMEM = "HL`wkVS1";
static const char set_11[] PROGMEM = "Km[h9P-N";
static const char set_12[] PROGMEM = "8;C";
static const char set_13[] PROGMEM = ",Igl\\";
static const char set_14[] PROGMEM = "uUr3j";
static const char set_15[] PROGMEM = "Xsy(";
static const char set_16[] PROGMEM = "/:.#ve]f";
static const char * const setsOfCharacters[numberOfSets] PROGMEM = {
  set_0, set_1, set_2, set_3, set_4, set_5, set_6,
  set_7, set_8, set_9, set_10, set_11, set_12,
  set_13, set_14, set_15, set_16
};
