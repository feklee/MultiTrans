#define TEST_ALL
#define BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const bool noiseShouldBeRandomlyInserted = false;
const uint32_t durationOfTest = 300000;
const bool verbose = true;
const bool recordDebugData = true;
const uint8_t bitDurationExp = 18;
const uint8_t maxNumberOfCharsPerTransmission = 8;
const uint8_t customReceiveBufferSize = 0;
static const uint8_t numberOfSets = 57;
static const uint8_t sizeOfSet0 = 7;
static const uint8_t sizeOfSet1 = 4;
static const uint8_t sizeOfSet2 = 4;
static const uint8_t sizeOfSet3 = 2;
static const uint8_t sizeOfSet4 = 5;
static const uint8_t sizeOfSet5 = 6;
static const uint8_t sizeOfSet6 = 7;
static const uint8_t sizeOfSet7 = 5;
static const uint8_t sizeOfSet8 = 3;
static const uint8_t sizeOfSet9 = 2;
static const uint8_t sizeOfSet10 = 5;
static const uint8_t sizeOfSet11 = 3;
static const uint8_t sizeOfSet12 = 2;
static const uint8_t sizeOfSet13 = 5;
static const uint8_t sizeOfSet14 = 1;
static const uint8_t sizeOfSet15 = 1;
static const uint8_t sizeOfSet16 = 2;
static const uint8_t sizeOfSet17 = 3;
static const uint8_t sizeOfSet18 = 8;
static const uint8_t sizeOfSet19 = 2;
static const uint8_t sizeOfSet20 = 7;
static const uint8_t sizeOfSet21 = 8;
static const uint8_t sizeOfSet22 = 2;
static const uint8_t sizeOfSet23 = 5;
static const uint8_t sizeOfSet24 = 7;
static const uint8_t sizeOfSet25 = 4;
static const uint8_t sizeOfSet26 = 4;
static const uint8_t sizeOfSet27 = 2;
static const uint8_t sizeOfSet28 = 2;
static const uint8_t sizeOfSet29 = 7;
static const uint8_t sizeOfSet30 = 8;
static const uint8_t sizeOfSet31 = 6;
static const uint8_t sizeOfSet32 = 6;
static const uint8_t sizeOfSet33 = 8;
static const uint8_t sizeOfSet34 = 7;
static const uint8_t sizeOfSet35 = 7;
static const uint8_t sizeOfSet36 = 7;
static const uint8_t sizeOfSet37 = 3;
static const uint8_t sizeOfSet38 = 5;
static const uint8_t sizeOfSet39 = 1;
static const uint8_t sizeOfSet40 = 1;
static const uint8_t sizeOfSet41 = 4;
static const uint8_t sizeOfSet42 = 2;
static const uint8_t sizeOfSet43 = 6;
static const uint8_t sizeOfSet44 = 6;
static const uint8_t sizeOfSet45 = 7;
static const uint8_t sizeOfSet46 = 2;
static const uint8_t sizeOfSet47 = 5;
static const uint8_t sizeOfSet48 = 8;
static const uint8_t sizeOfSet49 = 6;
static const uint8_t sizeOfSet50 = 4;
static const uint8_t sizeOfSet51 = 4;
static const uint8_t sizeOfSet52 = 7;
static const uint8_t sizeOfSet53 = 3;
static const uint8_t sizeOfSet54 = 4;
static const uint8_t sizeOfSet55 = 2;
static const uint8_t sizeOfSet56 = 2;
static const byte set0[sizeOfSet0] PROGMEM =
  {3, 188, 21, 225, 138, 251, 197};
static const byte set1[sizeOfSet1] PROGMEM =
  {236, 34, 106, 80};
static const byte set2[sizeOfSet2] PROGMEM =
  {56, 17, 244, 166};
static const byte set3[sizeOfSet3] PROGMEM =
  {219, 145};
static const byte set4[sizeOfSet4] PROGMEM =
  {70, 57, 37, 231, 110};
static const byte set5[sizeOfSet5] PROGMEM =
  {66, 160, 1, 46, 189, 32};
static const byte set6[sizeOfSet6] PROGMEM =
  {146, 132, 67, 0, 76, 196, 27};
static const byte set7[sizeOfSet7] PROGMEM =
  {142, 151, 87, 113, 199};
static const byte set8[sizeOfSet8] PROGMEM =
  {111, 92, 182};
static const byte set9[sizeOfSet9] PROGMEM =
  {204, 25};
static const byte set10[sizeOfSet10] PROGMEM =
  {217, 242, 147, 155, 161};
static const byte set11[sizeOfSet11] PROGMEM =
  {172, 10, 86};
static const byte set12[sizeOfSet12] PROGMEM =
  {114, 133};
static const byte set13[sizeOfSet13] PROGMEM =
  {60, 164, 227, 224, 48};
static const byte set14[sizeOfSet14] PROGMEM =
  {192};
static const byte set15[sizeOfSet15] PROGMEM =
  {165};
static const byte set16[sizeOfSet16] PROGMEM =
  {120, 62};
static const byte set17[sizeOfSet17] PROGMEM =
  {193, 254, 28};
static const byte set18[sizeOfSet18] PROGMEM =
  {178, 246, 45, 239, 232, 30, 241, 39};
static const byte set19[sizeOfSet19] PROGMEM =
  {240, 154};
static const byte set20[sizeOfSet20] PROGMEM =
  {41, 13, 29, 15, 209, 184, 14};
static const byte set21[sizeOfSet21] PROGMEM =
  {213, 218, 90, 99, 158, 171, 112, 247};
static const byte set22[sizeOfSet22] PROGMEM =
  {134, 222};
static const byte set23[sizeOfSet23] PROGMEM =
  {170, 102, 235, 186, 200};
static const byte set24[sizeOfSet24] PROGMEM =
  {75, 47, 81, 234, 252, 98, 44};
static const byte set25[sizeOfSet25] PROGMEM =
  {237, 201, 212, 122};
static const byte set26[sizeOfSet26] PROGMEM =
  {149, 89, 183, 126};
static const byte set27[sizeOfSet27] PROGMEM =
  {54, 216};
static const byte set28[sizeOfSet28] PROGMEM =
  {16, 245};
static const byte set29[sizeOfSet29] PROGMEM =
  {107, 68, 153, 42, 26, 148, 65};
static const byte set30[sizeOfSet30] PROGMEM =
  {121, 6, 221, 2, 12, 40, 117, 93};
static const byte set31[sizeOfSet31] PROGMEM =
  {195, 50, 179, 83, 228, 187};
static const byte set32[sizeOfSet32] PROGMEM =
  {97, 198, 4, 211, 88, 69};
static const byte set33[sizeOfSet33] PROGMEM =
  {101, 249, 128, 51, 55, 214, 124, 159};
static const byte set34[sizeOfSet34] PROGMEM =
  {82, 131, 19, 194, 85, 125, 202};
static const byte set35[sizeOfSet35] PROGMEM =
  {162, 109, 115, 11, 167, 205, 176};
static const byte set36[sizeOfSet36] PROGMEM =
  {137, 43, 74, 119, 77, 238, 229};
static const byte set37[sizeOfSet37] PROGMEM =
  {23, 72, 243};
static const byte set38[sizeOfSet38] PROGMEM =
  {118, 223, 35, 127, 174};
static const byte set39[sizeOfSet39] PROGMEM =
  {180};
static const byte set40[sizeOfSet40] PROGMEM =
  {58};
static const byte set41[sizeOfSet41] PROGMEM =
  {49, 253, 24, 52};
static const byte set42[sizeOfSet42] PROGMEM =
  {36, 108};
static const byte set43[sizeOfSet43] PROGMEM =
  {91, 255, 103, 136, 168, 22};
static const byte set44[sizeOfSet44] PROGMEM =
  {104, 73, 203, 220, 169, 64};
static const byte set45[sizeOfSet45] PROGMEM =
  {141, 230, 71, 210, 181, 140, 163};
static const byte set46[sizeOfSet46] PROGMEM =
  {61, 5};
static const byte set47[sizeOfSet47] PROGMEM =
  {191, 248, 177, 84, 59};
static const byte set48[sizeOfSet48] PROGMEM =
  {135, 53, 215, 9, 116, 18, 105, 123};
static const byte set49[sizeOfSet49] PROGMEM =
  {144, 7, 208, 250, 96, 100};
static const byte set50[sizeOfSet50] PROGMEM =
  {207, 31, 226, 33};
static const byte set51[sizeOfSet51] PROGMEM =
  {20, 150, 94, 152};
static const byte set52[sizeOfSet52] PROGMEM =
  {156, 63, 130, 78, 173, 206, 8};
static const byte set53[sizeOfSet53] PROGMEM =
  {79, 143, 95};
static const byte set54[sizeOfSet54] PROGMEM =
  {157, 129, 190, 185};
static const byte set55[sizeOfSet55] PROGMEM =
  {139, 38};
static const byte set56[sizeOfSet56] PROGMEM =
  {175, 233};
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
   sizeOfSet54, sizeOfSet55, sizeOfSet56
  };
static const byte * const
sets[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11,
   set12, set13, set14, set15, set16, set17, set18, set19, set20, set21, set22,
   set23, set24, set25, set26, set27, set28, set29, set30, set31, set32, set33,
   set34, set35, set36, set37, set38, set39, set40, set41, set42, set43, set44,
   set45, set46, set47, set48, set49, set50, set51, set52, set53, set54, set55,
   set56
  };
