#define TEST_ALL
#define BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const uint32_t durationOfTest = 300000;
const bool noiseShouldBeRandomlyInserted = false;
const bool verbose = false;
const bool recordDebugData = false;
const uint8_t bitDurationExp = 11;
const uint8_t maxNumberOfItemsPerTransmission = 8;
const uint8_t customReceiveBufferSize = 0;
static const uint8_t numberOfSets = 59;
static const uint8_t sizeOfSet0 = 8;
static const uint8_t sizeOfSet1 = 4;
static const uint8_t sizeOfSet2 = 2;
static const uint8_t sizeOfSet3 = 2;
static const uint8_t sizeOfSet4 = 3;
static const uint8_t sizeOfSet5 = 1;
static const uint8_t sizeOfSet6 = 7;
static const uint8_t sizeOfSet7 = 2;
static const uint8_t sizeOfSet8 = 8;
static const uint8_t sizeOfSet9 = 4;
static const uint8_t sizeOfSet10 = 6;
static const uint8_t sizeOfSet11 = 7;
static const uint8_t sizeOfSet12 = 8;
static const uint8_t sizeOfSet13 = 5;
static const uint8_t sizeOfSet14 = 5;
static const uint8_t sizeOfSet15 = 2;
static const uint8_t sizeOfSet16 = 6;
static const uint8_t sizeOfSet17 = 4;
static const uint8_t sizeOfSet18 = 4;
static const uint8_t sizeOfSet19 = 3;
static const uint8_t sizeOfSet20 = 6;
static const uint8_t sizeOfSet21 = 7;
static const uint8_t sizeOfSet22 = 3;
static const uint8_t sizeOfSet23 = 4;
static const uint8_t sizeOfSet24 = 4;
static const uint8_t sizeOfSet25 = 7;
static const uint8_t sizeOfSet26 = 4;
static const uint8_t sizeOfSet27 = 6;
static const uint8_t sizeOfSet28 = 8;
static const uint8_t sizeOfSet29 = 4;
static const uint8_t sizeOfSet30 = 7;
static const uint8_t sizeOfSet31 = 3;
static const uint8_t sizeOfSet32 = 4;
static const uint8_t sizeOfSet33 = 5;
static const uint8_t sizeOfSet34 = 1;
static const uint8_t sizeOfSet35 = 1;
static const uint8_t sizeOfSet36 = 7;
static const uint8_t sizeOfSet37 = 5;
static const uint8_t sizeOfSet38 = 8;
static const uint8_t sizeOfSet39 = 4;
static const uint8_t sizeOfSet40 = 3;
static const uint8_t sizeOfSet41 = 7;
static const uint8_t sizeOfSet42 = 2;
static const uint8_t sizeOfSet43 = 6;
static const uint8_t sizeOfSet44 = 7;
static const uint8_t sizeOfSet45 = 5;
static const uint8_t sizeOfSet46 = 1;
static const uint8_t sizeOfSet47 = 2;
static const uint8_t sizeOfSet48 = 1;
static const uint8_t sizeOfSet49 = 7;
static const uint8_t sizeOfSet50 = 3;
static const uint8_t sizeOfSet51 = 1;
static const uint8_t sizeOfSet52 = 1;
static const uint8_t sizeOfSet53 = 3;
static const uint8_t sizeOfSet54 = 3;
static const uint8_t sizeOfSet55 = 7;
static const uint8_t sizeOfSet56 = 5;
static const uint8_t sizeOfSet57 = 1;
static const uint8_t sizeOfSet58 = 2;
static const byte set0[sizeOfSet0] PROGMEM =
  {240, 238, 28, 52, 138, 152, 116, 108};
static const byte set1[sizeOfSet1] PROGMEM =
  {24, 71, 100, 97};
static const byte set2[sizeOfSet2] PROGMEM =
  {50, 146};
static const byte set3[sizeOfSet3] PROGMEM =
  {115, 122};
static const byte set4[sizeOfSet4] PROGMEM =
  {109, 248, 32};
static const byte set5[sizeOfSet5] PROGMEM =
  {196};
static const byte set6[sizeOfSet6] PROGMEM =
  {67, 98, 7, 130, 29, 59, 247};
static const byte set7[sizeOfSet7] PROGMEM =
  {200, 150};
static const byte set8[sizeOfSet8] PROGMEM =
  {249, 219, 45, 99, 214, 53, 182, 205};
static const byte set9[sizeOfSet9] PROGMEM =
  {180, 36, 136, 192};
static const byte set10[sizeOfSet10] PROGMEM =
  {137, 170, 165, 46, 125, 211};
static const byte set11[sizeOfSet11] PROGMEM =
  {149, 54, 250, 204, 184, 70, 72};
static const byte set12[sizeOfSet12] PROGMEM =
  {209, 110, 86, 1, 190, 78, 21, 37};
static const byte set13[sizeOfSet13] PROGMEM =
  {63, 126, 227, 151, 91};
static const byte set14[sizeOfSet14] PROGMEM =
  {64, 16, 213, 216, 141};
static const byte set15[sizeOfSet15] PROGMEM =
  {84, 172};
static const byte set16[sizeOfSet16] PROGMEM =
  {185, 68, 252, 132, 156, 79};
static const byte set17[sizeOfSet17] PROGMEM =
  {27, 181, 207, 127};
static const byte set18[sizeOfSet18] PROGMEM =
  {164, 105, 139, 251};
static const byte set19[sizeOfSet19] PROGMEM =
  {41, 129, 113};
static const byte set20[sizeOfSet20] PROGMEM =
  {51, 62, 145, 143, 12, 6};
static const byte set21[sizeOfSet21] PROGMEM =
  {135, 188, 30, 241, 168, 111, 223};
static const byte set22[sizeOfSet22] PROGMEM =
  {34, 166, 231};
static const byte set23[sizeOfSet23] PROGMEM =
  {131, 26, 58, 179};
static const byte set24[sizeOfSet24] PROGMEM =
  {4, 8, 212, 128};
static const byte set25[sizeOfSet25] PROGMEM =
  {20, 65, 22, 43, 206, 133, 134};
static const byte set26[sizeOfSet26] PROGMEM =
  {158, 121, 118, 119};
static const byte set27[sizeOfSet27] PROGMEM =
  {189, 23, 95, 49, 187, 254};
static const byte set28[sizeOfSet28] PROGMEM =
  {178, 55, 104, 229, 147, 25, 2, 195};
static const byte set29[sizeOfSet29] PROGMEM =
  {173, 218, 75, 171};
static const byte set30[sizeOfSet30] PROGMEM =
  {232, 244, 239, 83, 61, 123, 140};
static const byte set31[sizeOfSet31] PROGMEM =
  {96, 157, 235};
static const byte set32[sizeOfSet32] PROGMEM =
  {215, 3, 81, 69};
static const byte set33[sizeOfSet33] PROGMEM =
  {255, 112, 233, 217, 42};
static const byte set34[sizeOfSet34] PROGMEM =
  {9};
static const byte set35[sizeOfSet35] PROGMEM =
  {106};
static const byte set36[sizeOfSet36] PROGMEM =
  {224, 237, 76, 101, 5, 221, 14};
static const byte set37[sizeOfSet37] PROGMEM =
  {193, 228, 38, 154, 201};
static const byte set38[sizeOfSet38] PROGMEM =
  {177, 80, 243, 230, 142, 160, 102, 114};
static const byte set39[sizeOfSet39] PROGMEM =
  {56, 120, 40, 246};
static const byte set40[sizeOfSet40] PROGMEM =
  {226, 82, 210};
static const byte set41[sizeOfSet41] PROGMEM =
  {202, 73, 163, 242, 245, 203, 66};
static const byte set42[sizeOfSet42] PROGMEM =
  {17, 144};
static const byte set43[sizeOfSet43] PROGMEM =
  {162, 35, 161, 159, 60, 191};
static const byte set44[sizeOfSet44] PROGMEM =
  {183, 186, 153, 33, 253, 199, 220};
static const byte set45[sizeOfSet45] PROGMEM =
  {74, 44, 77, 90, 198};
static const byte set46[sizeOfSet46] PROGMEM =
  {155};
static const byte set47[sizeOfSet47] PROGMEM =
  {87, 236};
static const byte set48[sizeOfSet48] PROGMEM =
  {167};
static const byte set49[sizeOfSet49] PROGMEM =
  {10, 92, 88, 107, 222, 124, 194};
static const byte set50[sizeOfSet50] PROGMEM =
  {174, 208, 103};
static const byte set51[sizeOfSet51] PROGMEM =
  {148};
static const byte set52[sizeOfSet52] PROGMEM =
  {47};
static const byte set53[sizeOfSet53] PROGMEM =
  {117, 197, 15};
static const byte set54[sizeOfSet54] PROGMEM =
  {234, 94, 57};
static const byte set55[sizeOfSet55] PROGMEM =
  {225, 11, 31, 19, 39, 18, 85};
static const byte set56[sizeOfSet56] PROGMEM =
  {169, 0, 176, 13, 93};
static const byte set57[sizeOfSet57] PROGMEM =
  {175};
static const byte set58[sizeOfSet58] PROGMEM =
  {48, 89};
static const byte sizesOfSets[numberOfSets] =
  {
   sizeOfSet0, sizeOfSet1, sizeOfSet2, sizeOfSet3, sizeOfSet4, sizeOfSet5,
   sizeOfSet6, sizeOfSet7, sizeOfSet8, sizeOfSet9, sizeOfSet10, sizeOfSet11,
   sizeOfSet12, sizeOfSet13, sizeOfSet14, sizeOfSet15, sizeOfSet16, sizeOfSet17,
   sizeOfSet18, sizeOfSet19, sizeOfSet20, sizeOfSet21, sizeOfSet22, sizeOfSet23,
   sizeOfSet24, sizeOfSet25, sizeOfSet26, sizeOfSet27, sizeOfSet28, sizeOfSet29,
   sizeOfSet30, sizeOfSet31, sizeOfSet32, sizeOfSet33, sizeOfSet34, sizeOfSet35,
   sizeOfSet36, sizeOfSet37, sizeOfSet38, sizeOfSet39, sizeOfSet40, sizeOfSet41,
   sizeOfSet42, sizeOfSet43, sizeOfSet44, sizeOfSet45, sizeOfSet46, sizeOfSet47,
   sizeOfSet48, sizeOfSet49, sizeOfSet50, sizeOfSet51, sizeOfSet52, sizeOfSet53,
   sizeOfSet54, sizeOfSet55, sizeOfSet56, sizeOfSet57, sizeOfSet58
  };
static const byte * const
sets[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11,
   set12, set13, set14, set15, set16, set17, set18, set19, set20, set21, set22,
   set23, set24, set25, set26, set27, set28, set29, set30, set31, set32, set33,
   set34, set35, set36, set37, set38, set39, set40, set41, set42, set43, set44,
   set45, set46, set47, set48, set49, set50, set51, set52, set53, set54, set55,
   set56, set57, set58
  };
