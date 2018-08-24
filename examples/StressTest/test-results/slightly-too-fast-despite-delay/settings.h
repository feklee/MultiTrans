// The delay improves error rate somewhat as it frees time for processing
// results. But still there are errors. This is slightly too fast.

const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 50;
const bool noiseShouldBeRandomlyInserted = false;
const uint32_t durationOfTest = 300000;
const bool verbose = false;
const bool recordDebugData = false;
const uint8_t bitDurationExp = 8;
const uint8_t maxNumberOfCharsPerTransmission = 12;
static const uint8_t numberOfSets = 13;
static const char set_0[] PROGMEM = "} ^Y54\"~FB{T";
static const char set_1[] PROGMEM = "c";
static const char set_2[] PROGMEM = "O)z_<*W@";
static const char set_3[] PROGMEM = "QJ>G=An+btD|";
static const char set_4[] PROGMEM = "o%";
static const char set_5[] PROGMEM = "6RE";
static const char set_6[] PROGMEM = "'2?p!&Z$7iqx";
static const char set_7[] PROGMEM = "0adMHL`wkVS1";
static const char set_8[] PROGMEM = "Km[h9P-N8;C";
static const char set_9[] PROGMEM = ",Igl\\";
static const char set_10[] PROGMEM = "uUr3j";
static const char set_11[] PROGMEM = "Xsy(";
static const char set_12[] PROGMEM = "/:.#ve]f";
static const char * const setsOfCharacters[numberOfSets] PROGMEM = {
  set_0, set_1, set_2, set_3, set_4, set_5, set_6,
  set_7, set_8, set_9, set_10, set_11, set_12
};
