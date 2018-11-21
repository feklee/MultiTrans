// Communication just between (*) and (B) via pin 2:
//
// needs less memory, can be faster

#undef TEST_ALL
#undef BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const bool noiseShouldBeRandomlyInserted = false;
const uint32_t durationOfTest = 300000;
const bool verbose = false;
const bool recordDebugData = false;
const uint8_t bitDurationExp = 9;
const uint8_t maxNumberOfItemsPerTransmission = 12;
const uint8_t customReceiveBufferSize = 0;
static const uint8_t numberOfSets = 13;
static const char set0[] PROGMEM = "} ^Y54\"~FB{T";
static const char set1[] PROGMEM = "c";
static const char set2[] PROGMEM = "O)z_<*W@";
static const char set3[] PROGMEM = "QJ>G=An+btD|";
static const char set4[] PROGMEM = "o%";
static const char set5[] PROGMEM = "6RE";
static const char set6[] PROGMEM = "'2?p!&Z$7iqx";
static const char set7[] PROGMEM = "0adMHL`wkVS1";
static const char set8[] PROGMEM = "Km[h9P-N8;C";
static const char set9[] PROGMEM = ",Igl\\";
static const char set10[] PROGMEM = "uUr3j";
static const char set11[] PROGMEM = "Xsy(";
static const char set12[] PROGMEM = "/:.#ve]f";
static const char * const sets[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6,
   set7, set8, set9, set10, set11, set12
  };
