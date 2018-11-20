#undef TEST_ALL
#define BINARY_TRANSMISSION
const bool arduinosShouldBeSynchronized = true;
const uint32_t durationOfMinimumDelay = 0;
const uint32_t durationOfTest = 300000;
const bool noiseShouldBeRandomlyInserted = false;
const bool recordDebugData = false;
const bool verbose = false;
const uint8_t bitDurationExp = 9;
const uint8_t maxNumberOfItemsPerTransmission = 12;
const uint8_t customReceiveBufferSize = 0;
static const uint8_t numberOfSets = 36;
static const uint8_t sizeOfSet0 = 12;
static const uint8_t sizeOfSet1 = 12;
static const uint8_t sizeOfSet2 = 1;
static const uint8_t sizeOfSet3 = 4;
static const uint8_t sizeOfSet4 = 10;
static const uint8_t sizeOfSet5 = 4;
static const uint8_t sizeOfSet6 = 5;
static const uint8_t sizeOfSet7 = 10;
static const uint8_t sizeOfSet8 = 7;
static const uint8_t sizeOfSet9 = 12;
static const uint8_t sizeOfSet10 = 9;
static const uint8_t sizeOfSet11 = 1;
static const uint8_t sizeOfSet12 = 11;
static const uint8_t sizeOfSet13 = 4;
static const uint8_t sizeOfSet14 = 1;
static const uint8_t sizeOfSet15 = 11;
static const uint8_t sizeOfSet16 = 12;
static const uint8_t sizeOfSet17 = 5;
static const uint8_t sizeOfSet18 = 7;
static const uint8_t sizeOfSet19 = 3;
static const uint8_t sizeOfSet20 = 4;
static const uint8_t sizeOfSet21 = 9;
static const uint8_t sizeOfSet22 = 11;
static const uint8_t sizeOfSet23 = 8;
static const uint8_t sizeOfSet24 = 10;
static const uint8_t sizeOfSet25 = 5;
static const uint8_t sizeOfSet26 = 1;
static const uint8_t sizeOfSet27 = 1;
static const uint8_t sizeOfSet28 = 12;
static const uint8_t sizeOfSet29 = 4;
static const uint8_t sizeOfSet30 = 10;
static const uint8_t sizeOfSet31 = 10;
static const uint8_t sizeOfSet32 = 10;
static const uint8_t sizeOfSet33 = 9;
static const uint8_t sizeOfSet34 = 7;
static const uint8_t sizeOfSet35 = 4;
static const byte set0[sizeOfSet0] PROGMEM =
  {240, 61, 17, 226, 165, 81, 24, 219, 50, 168, 149, 69};
static const byte set1[sizeOfSet1] PROGMEM =
  {105, 54, 98, 133, 134, 39, 236, 176, 74, 47, 106, 163};
static const byte set2[sizeOfSet2] PROGMEM =
  {123};
static const byte set3[sizeOfSet3] PROGMEM =
  {206, 145, 167, 253};
static const byte set4[sizeOfSet4] PROGMEM =
  {14, 161, 30, 49, 118, 58, 9, 12, 23, 205};
static const byte set5[sizeOfSet5] PROGMEM =
  {215, 124, 113, 56};
static const byte set6[sizeOfSet6] PROGMEM =
  {46, 96, 213, 184, 130};
static const byte set7[sizeOfSet7] PROGMEM =
  {135, 107, 92, 13, 29, 77, 151, 34, 35, 198};
static const byte set8[sizeOfSet8] PROGMEM =
  {142, 108, 42, 169, 22, 251, 228};
static const byte set9[sizeOfSet9] PROGMEM =
  {67, 246, 220, 174, 73, 203, 159, 75, 160, 55, 175, 129};
static const byte set10[sizeOfSet10] PROGMEM =
  {53, 85, 48, 60, 45, 147, 126, 186, 154};
static const byte set11[sizeOfSet11] PROGMEM =
  {104};
static const byte set12[sizeOfSet12] PROGMEM =
  {121, 19, 43, 63, 243, 116, 95, 136, 197, 15, 51};
static const byte set13[sizeOfSet13] PROGMEM =
  {101, 241, 40, 137};
static const byte set14[sizeOfSet14] PROGMEM =
  {204};
static const byte set15[sizeOfSet15] PROGMEM =
  {5, 141, 103, 146, 2, 195, 110, 218, 72, 232, 65};
static const byte set16[sizeOfSet16] PROGMEM =
  {209, 71, 64, 68, 111, 109, 144, 252, 185, 164, 76, 191};
static const byte set17[sizeOfSet17] PROGMEM =
  {41, 158, 119, 189, 125};
static const byte set18[sizeOfSet18] PROGMEM =
  {235, 201, 97, 10, 242, 237, 143};
static const byte set19[sizeOfSet19] PROGMEM =
  {32, 196, 16};
static const byte set20[sizeOfSet20] PROGMEM =
  {233, 37, 52, 202};
static const byte set21[sizeOfSet21] PROGMEM =
  {33, 223, 44, 102, 140, 255, 18, 120, 179};
static const byte set22[sizeOfSet22] PROGMEM =
  {100, 166, 225, 188, 99, 20, 78, 250, 4, 170, 89};
static const byte set23[sizeOfSet23] PROGMEM =
  {249, 38, 190, 155, 156, 80, 183, 222};
static const byte set24[sizeOfSet24] PROGMEM =
  {128, 194, 59, 21, 79, 8, 152, 254, 181, 200};
static const byte set25[sizeOfSet25] PROGMEM =
  {70, 180, 66, 208, 25};
static const byte set26[sizeOfSet26] PROGMEM =
  {231};
static const byte set27[sizeOfSet27] PROGMEM =
  {84};
static const byte set28[sizeOfSet28] PROGMEM =
  {148, 132, 177, 173, 212, 127, 247, 131, 178, 6, 57, 238};
static const byte set29[sizeOfSet29] PROGMEM =
  {210, 26, 139, 207};
static const byte set30[sizeOfSet30] PROGMEM =
  {193, 86, 230, 171, 153, 27, 245, 7, 248, 211};
static const byte set31[sizeOfSet31] PROGMEM =
  {114, 90, 138, 94, 227, 0, 229, 172, 157, 244};
static const byte set32[sizeOfSet32] PROGMEM =
  {93, 187, 11, 83, 122, 31, 217, 87, 115, 3};
static const byte set33[sizeOfSet33] PROGMEM =
  {192, 199, 62, 239, 82, 221, 234, 224, 91};
static const byte set34[sizeOfSet34] PROGMEM =
  {162, 117, 88, 36, 1, 214, 112};
static const byte set35[sizeOfSet35] PROGMEM =
  {150, 182, 28, 216};
static const byte sizesOfSets[numberOfSets] =
  {
   sizeOfSet0, sizeOfSet1, sizeOfSet2, sizeOfSet3, sizeOfSet4, sizeOfSet5,
   sizeOfSet6, sizeOfSet7, sizeOfSet8, sizeOfSet9, sizeOfSet10, sizeOfSet11,
   sizeOfSet12, sizeOfSet13, sizeOfSet14, sizeOfSet15, sizeOfSet16, sizeOfSet17,
   sizeOfSet18, sizeOfSet19, sizeOfSet20, sizeOfSet21, sizeOfSet22, sizeOfSet23,
   sizeOfSet24, sizeOfSet25, sizeOfSet26, sizeOfSet27, sizeOfSet28, sizeOfSet29,
   sizeOfSet30, sizeOfSet31, sizeOfSet32, sizeOfSet33, sizeOfSet34, sizeOfSet35
  };
static const byte * const
sets[numberOfSets] PROGMEM =
  {
   set0, set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11,
   set12, set13, set14, set15, set16, set17, set18, set19, set20, set21, set22,
   set23, set24, set25, set26, set27, set28, set29, set30, set31, set32, set33,
   set34, set35
  };
