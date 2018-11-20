#define TEST_ALL
#define BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const uint32_t durationOfTest = 300000;
const bool noiseShouldBeRandomlyInserted = false;
const bool recordDebugData = false;
const bool verbose = false;
const uint8_t bitDurationExp = 11;
const uint8_t maxNumberOfItemsPerTransmission = 13;
const uint8_t customReceiveBufferSize = 0;
const bool dataIsBinary = true;
static const uint8_t numberOfSets = 40;
static const uint8_t sizeOfSet0 = 1;
static const uint8_t sizeOfSet1 = 8;
static const uint8_t sizeOfSet2 = 7;
static const uint8_t sizeOfSet3 = 4;
static const uint8_t sizeOfSet4 = 7;
static const uint8_t sizeOfSet5 = 12;
static const uint8_t sizeOfSet6 = 3;
static const uint8_t sizeOfSet7 = 9;
static const uint8_t sizeOfSet8 = 10;
static const uint8_t sizeOfSet9 = 2;
static const uint8_t sizeOfSet10 = 12;
static const uint8_t sizeOfSet11 = 7;
static const uint8_t sizeOfSet12 = 3;
static const uint8_t sizeOfSet13 = 12;
static const uint8_t sizeOfSet14 = 13;
static const uint8_t sizeOfSet15 = 8;
static const uint8_t sizeOfSet16 = 4;
static const uint8_t sizeOfSet17 = 13;
static const uint8_t sizeOfSet18 = 13;
static const uint8_t sizeOfSet19 = 1;
static const uint8_t sizeOfSet20 = 3;
static const uint8_t sizeOfSet21 = 1;
static const uint8_t sizeOfSet22 = 7;
static const uint8_t sizeOfSet23 = 12;
static const uint8_t sizeOfSet24 = 6;
static const uint8_t sizeOfSet25 = 10;
static const uint8_t sizeOfSet26 = 3;
static const uint8_t sizeOfSet27 = 3;
static const uint8_t sizeOfSet28 = 3;
static const uint8_t sizeOfSet29 = 2;
static const uint8_t sizeOfSet30 = 10;
static const uint8_t sizeOfSet31 = 9;
static const uint8_t sizeOfSet32 = 3;
static const uint8_t sizeOfSet33 = 4;
static const uint8_t sizeOfSet34 = 3;
static const uint8_t sizeOfSet35 = 12;
static const uint8_t sizeOfSet36 = 3;
static const uint8_t sizeOfSet37 = 3;
static const uint8_t sizeOfSet38 = 8;
static const uint8_t sizeOfSet39 = 2;
static const byte set0[sizeOfSet0] PROGMEM =
  {68};
static const byte set1[sizeOfSet1] PROGMEM =
  {195, 243, 24, 79, 242, 167, 89, 7};
static const byte set2[sizeOfSet2] PROGMEM =
  {170, 94, 142, 32, 14, 188, 66};
static const byte set3[sizeOfSet3] PROGMEM =
  {184, 190, 88, 145};
static const byte set4[sizeOfSet4] PROGMEM =
  {70, 13, 173, 73, 92, 103, 250};
static const byte set5[sizeOfSet5] PROGMEM =
  {217, 178, 141, 129, 156, 26, 95, 177, 17, 60, 107, 228};
static const byte set6[sizeOfSet6] PROGMEM =
  {226, 185, 121};
static const byte set7[sizeOfSet7] PROGMEM =
  {238, 211, 18, 48, 176, 253, 199, 186, 179};
static const byte set8[sizeOfSet8] PROGMEM =
  {194, 182, 137, 58, 219, 127, 46, 54, 240, 4};
static const byte set9[sizeOfSet9] PROGMEM =
  {36, 161};
static const byte set10[sizeOfSet10] PROGMEM =
  {187, 152, 123, 154, 25, 49, 147, 183, 112, 191, 81, 133};
static const byte set11[sizeOfSet11] PROGMEM =
  {168, 106, 9, 252, 254, 207, 40};
static const byte set12[sizeOfSet12] PROGMEM =
  {128, 83, 85};
static const byte set13[sizeOfSet13] PROGMEM =
  {126, 224, 198, 67, 87, 225, 153, 16, 45, 192, 97, 158};
static const byte set14[sizeOfSet14] PROGMEM =
  {71, 23, 11, 233, 193, 164, 160, 93, 21, 222, 113, 6, 218};
static const byte set15[sizeOfSet15] PROGMEM =
  {78, 31, 51, 2, 28, 210, 255, 239};
static const byte set16[sizeOfSet16] PROGMEM =
  {249, 150, 29, 96};
static const byte set17[sizeOfSet17] PROGMEM =
  {120, 144, 148, 47, 245, 237, 98, 216, 205, 38, 215, 1, 165};
static const byte set18[sizeOfSet20] PROGMEM =
  {80, 132, 44, 172, 234, 43, 143, 169, 115, 139, 247, 189, 209};
static const byte set19[sizeOfSet19] PROGMEM =
  {62};
static const byte set20[sizeOfSet18] PROGMEM =
  {146, 236, 56};
static const byte set21[sizeOfSet21] PROGMEM =
  {212};
static const byte set22[sizeOfSet22] PROGMEM =
  {214, 117, 163, 90, 208, 15, 108};
static const byte set23[sizeOfSet23] PROGMEM =
  {35, 102, 119, 138, 197, 174, 20, 30, 116, 100, 151, 33};
static const byte set24[sizeOfSet24] PROGMEM =
  {86, 180, 109, 37, 77, 251};
static const byte set25[sizeOfSet25] PROGMEM =
  {0, 114, 52, 235, 213, 159, 140, 39, 91, 131};
static const byte set26[sizeOfSet26] PROGMEM =
  {84, 166, 155};
static const byte set27[sizeOfSet27] PROGMEM =
  {232, 5, 8};
static const byte set28[sizeOfSet28] PROGMEM =
  {3, 241, 229};
static const byte set29[sizeOfSet29] PROGMEM =
  {99, 206};
static const byte set30[sizeOfSet30] PROGMEM =
  {231, 125, 203, 55, 105, 27, 134, 104, 246, 111};
static const byte set31[sizeOfSet31] PROGMEM =
  {53, 122, 65, 244, 59, 41, 64, 118, 130};
static const byte set32[sizeOfSet32] PROGMEM =
  {196, 101, 181};
static const byte set33[sizeOfSet33] PROGMEM =
  {136, 227, 223, 200};
static const byte set34[sizeOfSet34] PROGMEM =
  {202, 19, 157};
static const byte set35[sizeOfSet35] PROGMEM =
  {248, 162, 61, 72, 135, 42, 221, 204, 12, 75, 124, 82};
static const byte set36[sizeOfSet36] PROGMEM =
  {76, 220, 149};
static const byte set37[sizeOfSet37] PROGMEM =
  {34, 22, 74};
static const byte set38[sizeOfSet38] PROGMEM =
  {110, 69, 50, 57, 230, 175, 201, 63};
static const byte set39[sizeOfSet39] PROGMEM =
  {10, 171};
static const byte sizesOfSets[numberOfSets] =
  {
   sizeOfSet0, sizeOfSet1, sizeOfSet2, sizeOfSet3, sizeOfSet4, sizeOfSet5,
   sizeOfSet6, sizeOfSet7, sizeOfSet8, sizeOfSet9, sizeOfSet10, sizeOfSet11,
   sizeOfSet12, sizeOfSet13, sizeOfSet14, sizeOfSet15, sizeOfSet16, sizeOfSet17,
   sizeOfSet18, sizeOfSet19, sizeOfSet20, sizeOfSet21, sizeOfSet22, sizeOfSet23,
   sizeOfSet24, sizeOfSet25, sizeOfSet26, sizeOfSet27, sizeOfSet28, sizeOfSet29,
   sizeOfSet30, sizeOfSet31, sizeOfSet32, sizeOfSet33, sizeOfSet34, sizeOfSet35,
   sizeOfSet36, sizeOfSet37, sizeOfSet38, sizeOfSet39
  };
static const byte * const
setsOfBytes[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11,
   set12, set13, set14, set15, set16, set17, set18, set19, set20, set21, set22,
   set23, set24, set25, set26, set27, set28, set29, set30, set31, set32, set33,
   set34, set35, set36, set37, set38, set39
  };
