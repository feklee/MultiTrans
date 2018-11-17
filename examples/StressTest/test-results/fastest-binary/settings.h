#define TEST_ALL
#define BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const uint32_t durationOfTest = 300000;
const bool noiseShouldBeRandomlyInserted = false;
const bool recordDebugData = false;
const bool verbose = false;
const uint8_t bitDurationExp = 11;
const uint8_t maxNumberOfCharsPerTransmission = 8; // TODO: increase!
const uint8_t customReceiveBufferSize = 0;
const bool dataIsBinary = true;
static const uint8_t numberOfSets = 51;
static const char * const setsOfCharacters[0] PROGMEM = {};
static const uint8_t setSize0 = 3;
static const uint8_t setSize1 = 8;
static const uint8_t setSize2 = 5;
static const uint8_t setSize3 = 1;
static const uint8_t setSize4 = 7;
static const uint8_t setSize5 = 3;
static const uint8_t setSize6 = 4;
static const uint8_t setSize7 = 1;
static const uint8_t setSize8 = 7;
static const uint8_t setSize9 = 6;
static const uint8_t setSize10 = 6;
static const uint8_t setSize11 = 8;
static const uint8_t setSize12 = 4;
static const uint8_t setSize13 = 2;
static const uint8_t setSize14 = 6;
static const uint8_t setSize15 = 8;
static const uint8_t setSize16 = 8;
static const uint8_t setSize17 = 4;
static const uint8_t setSize18 = 1;
static const uint8_t setSize19 = 1;
static const uint8_t setSize20 = 8;
static const uint8_t setSize21 = 8;
static const uint8_t setSize22 = 4;
static const uint8_t setSize23 = 2;
static const uint8_t setSize24 = 7;
static const uint8_t setSize25 = 3;
static const uint8_t setSize26 = 8;
static const uint8_t setSize27 = 5;
static const uint8_t setSize28 = 7;
static const uint8_t setSize29 = 3;
static const uint8_t setSize30 = 8;
static const uint8_t setSize31 = 5;
static const uint8_t setSize32 = 2;
static const uint8_t setSize33 = 3;
static const uint8_t setSize34 = 6;
static const uint8_t setSize35 = 8;
static const uint8_t setSize36 = 8;
static const uint8_t setSize37 = 8;
static const uint8_t setSize38 = 3;
static const uint8_t setSize39 = 3;
static const uint8_t setSize40 = 1;
static const uint8_t setSize41 = 1;
static const uint8_t setSize42 = 7;
static const uint8_t setSize43 = 3;
static const uint8_t setSize44 = 4;
static const uint8_t setSize45 = 5;
static const uint8_t setSize46 = 2;
static const uint8_t setSize47 = 8;
static const uint8_t setSize48 = 8;
static const uint8_t setSize49 = 8;
static const uint8_t setSize50 = 7;
static const byte set0[setSize0] PROGMEM =
  {250, 182, 224};
static const byte set1[setSize1] PROGMEM =
  {76, 164, 37, 184, 197, 209, 75, 114};
static const byte set2[setSize2] PROGMEM =
  {8, 189, 6, 103, 253};
static const byte set3[setSize3] PROGMEM =
  {87};
static const byte set4[setSize4] PROGMEM =
  {134, 70, 199, 223, 22, 147, 246};
static const byte set5[setSize5] PROGMEM =
  {200, 193, 82};
static const byte set6[setSize6] PROGMEM =
  {38, 137, 44, 216};
static const byte set7[setSize7] PROGMEM =
  {150};
static const byte set8[setSize8] PROGMEM =
  {252, 251, 168, 213, 108, 206, 79};
static const byte set9[setSize9] PROGMEM =
  {24, 81, 235, 176, 174, 226};
static const byte set10[setSize10] PROGMEM =
  {39, 104, 48, 145, 51, 67};
static const byte set11[setSize11] PROGMEM =
  {191, 0, 121, 29, 222, 83, 63, 249};
static const byte set12[setSize12] PROGMEM =
  {202, 77, 80, 240};
static const byte set13[setSize13] PROGMEM =
  {17, 247};
static const byte set14[setSize14] PROGMEM =
  {155, 52, 20, 54, 89, 205};
static const byte set15[setSize15] PROGMEM =
  {229, 204, 43, 178, 109, 210, 33, 255};
static const byte set16[setSize16] PROGMEM =
  {59, 46, 111, 133, 212, 92, 23, 175};
static const byte set17[setSize17] PROGMEM =
  {65, 232, 154, 151};
static const byte set18[setSize18] PROGMEM =
  {115};
static const byte set19[setSize19] PROGMEM =
  {136};
static const byte set20[setSize20] PROGMEM =
  {125, 5, 113, 2, 128, 112, 217, 169};
static const byte set21[setSize21] PROGMEM =
  {41, 203, 231, 3, 172, 194, 21, 144};
static const byte set22[setSize22] PROGMEM =
  {227, 12, 19, 62};
static const byte set23[setSize23] PROGMEM =
  {42, 96};
static const byte set24[setSize24] PROGMEM =
  {50, 198, 237, 208, 124, 93, 170};
static const byte set25[setSize25] PROGMEM =
  {156, 245, 196};
static const byte set26[setSize26] PROGMEM =
  {242, 185, 142, 58, 90, 36, 234, 131};
static const byte set27[setSize27] PROGMEM =
  {141, 11, 219, 165, 99};
static const byte set28[setSize28] PROGMEM =
  {45, 149, 218, 180, 74, 158, 148};
static const byte set29[setSize29] PROGMEM =
  {7, 132, 166};
static const byte set30[setSize30] PROGMEM =
  {34, 14, 220, 18, 140, 68, 88, 233};
static const byte set31[setSize31] PROGMEM =
  {244, 40, 123, 221, 102};
static const byte set32[setSize32] PROGMEM =
  {78, 120};
static const byte set33[setSize33] PROGMEM =
  {152, 26, 138};
static const byte set34[setSize34] PROGMEM =
  {181, 71, 73, 214, 201, 107};
static const byte set35[setSize35] PROGMEM =
  {25, 207, 183, 10, 254, 95, 97, 167};
static const byte set36[setSize36] PROGMEM =
  {228, 195, 55, 15, 101, 1, 187, 163};
static const byte set37[setSize37] PROGMEM =
  {30, 16, 32, 157, 186, 122, 135, 27};
static const byte set38[setSize38] PROGMEM =
  {127, 179, 64};
static const byte set39[setSize39] PROGMEM =
  {13, 153, 84};
static const byte set40[setSize40] PROGMEM =
  {69};
static const byte set41[setSize41] PROGMEM =
  {60};
static const byte set42[setSize42] PROGMEM =
  {86, 146, 31, 94, 192, 173, 239};
static const byte set43[setSize43] PROGMEM =
  {241, 35, 85};
static const byte set44[setSize44] PROGMEM =
  {211, 129, 98, 72};
static const byte set45[setSize45] PROGMEM =
  {143, 188, 139, 91, 130};
static const byte set46[setSize46] PROGMEM =
  {126, 225};
static const byte set47[setSize47] PROGMEM =
  {236, 106, 56, 162, 117, 171, 28, 160};
static const byte set48[setSize48] PROGMEM =
  {49, 238, 248, 9, 4, 100, 243, 53};
static const byte set49[setSize49] PROGMEM =
  {47, 230, 215, 61, 105, 57, 161, 177};
static const byte set50[setSize50] PROGMEM =
  {159, 119, 116, 118, 110, 190, 66};
static const byte setSizes[numberOfSets] =
  {
   setSize0, setSize1, setSize2, setSize3, setSize4, setSize5, setSize6,
   setSize7, setSize8, setSize9, setSize10, setSize11, setSize12, setSize13,
   setSize14, setSize15, setSize16, setSize17, setSize18, setSize19, setSize20,
   setSize21, setSize22, setSize23, setSize24, setSize25, setSize26, setSize27,
   setSize28, setSize29, setSize30, setSize31, setSize32, setSize33, setSize34,
   setSize35, setSize36, setSize37, setSize38, setSize39, setSize40, setSize41,
   setSize42, setSize43, setSize44, setSize45, setSize46, setSize47, setSize48,
   setSize49, setSize50
  };
static const byte * const
setsOfBytes[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11,
   set12, set13, set14, set15, set16, set17, set18, set19, set20, set21, set22,
   set23, set24, set25, set26, set27, set28, set29, set30, set31, set32, set33,
   set34, set35, set36, set37, set38, set39, set40, set41, set42, set43, set44,
   set45, set46, set47, set48, set49, set50
  };
