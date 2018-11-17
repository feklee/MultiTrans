#define TEST_ALL
#define BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const uint32_t durationOfTest = 300000;
const bool noiseShouldBeRandomlyInserted = false;
const bool recordDebugData = false;
const bool verbose = false;
const uint8_t bitDurationExp = 11;
const uint8_t maxNumberOfItemsPerTransmission = 8; // TODO: increase!
const uint8_t customReceiveBufferSize = 0;
const bool dataIsBinary = true;
static const uint8_t numberOfSets = 51;
static const char * const setsOfCharacters[0] PROGMEM = {};
static const uint8_t sizeOfSet0 = 3;
static const uint8_t sizeOfSet1 = 8;
static const uint8_t sizeOfSet2 = 5;
static const uint8_t sizeOfSet3 = 1;
static const uint8_t sizeOfSet4 = 7;
static const uint8_t sizeOfSet5 = 3;
static const uint8_t sizeOfSet6 = 4;
static const uint8_t sizeOfSet7 = 1;
static const uint8_t sizeOfSet8 = 7;
static const uint8_t sizeOfSet9 = 6;
static const uint8_t sizeOfSet10 = 6;
static const uint8_t sizeOfSet11 = 8;
static const uint8_t sizeOfSet12 = 4;
static const uint8_t sizeOfSet13 = 2;
static const uint8_t sizeOfSet14 = 6;
static const uint8_t sizeOfSet15 = 8;
static const uint8_t sizeOfSet16 = 8;
static const uint8_t sizeOfSet17 = 4;
static const uint8_t sizeOfSet18 = 1;
static const uint8_t sizeOfSet19 = 1;
static const uint8_t sizeOfSet20 = 8;
static const uint8_t sizeOfSet21 = 8;
static const uint8_t sizeOfSet22 = 4;
static const uint8_t sizeOfSet23 = 2;
static const uint8_t sizeOfSet24 = 7;
static const uint8_t sizeOfSet25 = 3;
static const uint8_t sizeOfSet26 = 8;
static const uint8_t sizeOfSet27 = 5;
static const uint8_t sizeOfSet28 = 7;
static const uint8_t sizeOfSet29 = 3;
static const uint8_t sizeOfSet30 = 8;
static const uint8_t sizeOfSet31 = 5;
static const uint8_t sizeOfSet32 = 2;
static const uint8_t sizeOfSet33 = 3;
static const uint8_t sizeOfSet34 = 6;
static const uint8_t sizeOfSet35 = 8;
static const uint8_t sizeOfSet36 = 8;
static const uint8_t sizeOfSet37 = 8;
static const uint8_t sizeOfSet38 = 3;
static const uint8_t sizeOfSet39 = 3;
static const uint8_t sizeOfSet40 = 1;
static const uint8_t sizeOfSet41 = 1;
static const uint8_t sizeOfSet42 = 7;
static const uint8_t sizeOfSet43 = 3;
static const uint8_t sizeOfSet44 = 4;
static const uint8_t sizeOfSet45 = 5;
static const uint8_t sizeOfSet46 = 2;
static const uint8_t sizeOfSet47 = 8;
static const uint8_t sizeOfSet48 = 8;
static const uint8_t sizeOfSet49 = 8;
static const uint8_t sizeOfSet50 = 7;
static const byte set0[sizeOfSet0] PROGMEM =
  {250, 182, 224};
static const byte set1[sizeOfSet1] PROGMEM =
  {76, 164, 37, 184, 197, 209, 75, 114};
static const byte set2[sizeOfSet2] PROGMEM =
  {8, 189, 6, 103, 253};
static const byte set3[sizeOfSet3] PROGMEM =
  {87};
static const byte set4[sizeOfSet4] PROGMEM =
  {134, 70, 199, 223, 22, 147, 246};
static const byte set5[sizeOfSet5] PROGMEM =
  {200, 193, 82};
static const byte set6[sizeOfSet6] PROGMEM =
  {38, 137, 44, 216};
static const byte set7[sizeOfSet7] PROGMEM =
  {150};
static const byte set8[sizeOfSet8] PROGMEM =
  {252, 251, 168, 213, 108, 206, 79};
static const byte set9[sizeOfSet9] PROGMEM =
  {24, 81, 235, 176, 174, 226};
static const byte set10[sizeOfSet10] PROGMEM =
  {39, 104, 48, 145, 51, 67};
static const byte set11[sizeOfSet11] PROGMEM =
  {191, 0, 121, 29, 222, 83, 63, 249};
static const byte set12[sizeOfSet12] PROGMEM =
  {202, 77, 80, 240};
static const byte set13[sizeOfSet13] PROGMEM =
  {17, 247};
static const byte set14[sizeOfSet14] PROGMEM =
  {155, 52, 20, 54, 89, 205};
static const byte set15[sizeOfSet15] PROGMEM =
  {229, 204, 43, 178, 109, 210, 33, 255};
static const byte set16[sizeOfSet16] PROGMEM =
  {59, 46, 111, 133, 212, 92, 23, 175};
static const byte set17[sizeOfSet17] PROGMEM =
  {65, 232, 154, 151};
static const byte set18[sizeOfSet18] PROGMEM =
  {115};
static const byte set19[sizeOfSet19] PROGMEM =
  {136};
static const byte set20[sizeOfSet20] PROGMEM =
  {125, 5, 113, 2, 128, 112, 217, 169};
static const byte set21[sizeOfSet21] PROGMEM =
  {41, 203, 231, 3, 172, 194, 21, 144};
static const byte set22[sizeOfSet22] PROGMEM =
  {227, 12, 19, 62};
static const byte set23[sizeOfSet23] PROGMEM =
  {42, 96};
static const byte set24[sizeOfSet24] PROGMEM =
  {50, 198, 237, 208, 124, 93, 170};
static const byte set25[sizeOfSet25] PROGMEM =
  {156, 245, 196};
static const byte set26[sizeOfSet26] PROGMEM =
  {242, 185, 142, 58, 90, 36, 234, 131};
static const byte set27[sizeOfSet27] PROGMEM =
  {141, 11, 219, 165, 99};
static const byte set28[sizeOfSet28] PROGMEM =
  {45, 149, 218, 180, 74, 158, 148};
static const byte set29[sizeOfSet29] PROGMEM =
  {7, 132, 166};
static const byte set30[sizeOfSet30] PROGMEM =
  {34, 14, 220, 18, 140, 68, 88, 233};
static const byte set31[sizeOfSet31] PROGMEM =
  {244, 40, 123, 221, 102};
static const byte set32[sizeOfSet32] PROGMEM =
  {78, 120};
static const byte set33[sizeOfSet33] PROGMEM =
  {152, 26, 138};
static const byte set34[sizeOfSet34] PROGMEM =
  {181, 71, 73, 214, 201, 107};
static const byte set35[sizeOfSet35] PROGMEM =
  {25, 207, 183, 10, 254, 95, 97, 167};
static const byte set36[sizeOfSet36] PROGMEM =
  {228, 195, 55, 15, 101, 1, 187, 163};
static const byte set37[sizeOfSet37] PROGMEM =
  {30, 16, 32, 157, 186, 122, 135, 27};
static const byte set38[sizeOfSet38] PROGMEM =
  {127, 179, 64};
static const byte set39[sizeOfSet39] PROGMEM =
  {13, 153, 84};
static const byte set40[sizeOfSet40] PROGMEM =
  {69};
static const byte set41[sizeOfSet41] PROGMEM =
  {60};
static const byte set42[sizeOfSet42] PROGMEM =
  {86, 146, 31, 94, 192, 173, 239};
static const byte set43[sizeOfSet43] PROGMEM =
  {241, 35, 85};
static const byte set44[sizeOfSet44] PROGMEM =
  {211, 129, 98, 72};
static const byte set45[sizeOfSet45] PROGMEM =
  {143, 188, 139, 91, 130};
static const byte set46[sizeOfSet46] PROGMEM =
  {126, 225};
static const byte set47[sizeOfSet47] PROGMEM =
  {236, 106, 56, 162, 117, 171, 28, 160};
static const byte set48[sizeOfSet48] PROGMEM =
  {49, 238, 248, 9, 4, 100, 243, 53};
static const byte set49[sizeOfSet49] PROGMEM =
  {47, 230, 215, 61, 105, 57, 161, 177};
static const byte set50[sizeOfSet50] PROGMEM =
  {159, 119, 116, 118, 110, 190, 66};
static const byte sizeOfSets[numberOfSets] =
  {
   sizeOfSet0, sizeOfSet1, sizeOfSet2, sizeOfSet3, sizeOfSet4, sizeOfSet5,
   sizeOfSet6, sizeOfSet7, sizeOfSet8, sizeOfSet9, sizeOfSet10, sizeOfSet11,
   sizeOfSet12, sizeOfSet13, sizeOfSet14, sizeOfSet15, sizeOfSet16, sizeOfSet17,
   sizeOfSet18, sizeOfSet19, sizeOfSet20, sizeOfSet21, sizeOfSet22, sizeOfSet23,
   sizeOfSet24, sizeOfSet25, sizeOfSet26, sizeOfSet27, sizeOfSet28, sizeOfSet29,
   sizeOfSet30, sizeOfSet31, sizeOfSet32, sizeOfSet33, sizeOfSet34, sizeOfSet35,
   sizeOfSet36, sizeOfSet37, sizeOfSet38, sizeOfSet39, sizeOfSet40, sizeOfSet41,
   sizeOfSet42, sizeOfSet43, sizeOfSet44, sizeOfSet45, sizeOfSet46, sizeOfSet47,
   sizeOfSet48, sizeOfSet49, sizeOfSet50
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
