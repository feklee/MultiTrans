#define TEST_ALL
#undef BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const bool noiseShouldBeRandomlyInserted = true;
const uint32_t durationOfTest = 300000;
const bool verbose = false;
const bool recordDebugData = false;
const uint8_t bitDurationExp = 11;
const uint8_t maxNumberOfItemsPerTransmission = 8;
const uint8_t customReceiveBufferSize = 0;
static const uint8_t numberOfSets = 17;
static const char set0[] PROGMEM = "} ^Y54\"~";
static const char set1[] PROGMEM = "FB{T";
static const char set2[] PROGMEM = "c";
static const char set3[] PROGMEM = "O)z_<*W@";
static const char set4[] PROGMEM = "QJ>G";
static const char set5[] PROGMEM = "=An+btD|";
static const char set6[] PROGMEM = "o%";
static const char set7[] PROGMEM = "6RE";
static const char set8[] PROGMEM = "'2?p!&Z$";
static const char set9[] PROGMEM = "7iqx0adM";
static const char set10[] PROGMEM = "HL`wkVS1";
static const char set11[] PROGMEM = "Km[h9P-N";
static const char set12[] PROGMEM = "8;C";
static const char set13[] PROGMEM = ",Igl\\";
static const char set14[] PROGMEM = "uUr3j";
static const char set15[] PROGMEM = "Xsy(";
static const char set16[] PROGMEM = "/:.#ve]f";
static const char * const sets[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6,
   set7, set8, set9, set10, set11, set12,
   set13, set14, set15, set16
  };
