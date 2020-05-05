// Rotel http://irdb.tk/convert/ + http://www.rotel.com/sites/default/files/product/ir/RA05SE%20HEX.pdf
#define ROTEL_TYPE NEC
#define ROTEL_CODE_LEN 32
#define ROTEL_POWER  GenNECXCode(131, 17, 0)
#define ROTEL_SRC_CD  GenNECXCode(131, 17, 1)
#define ROTEL_SRC_TUNER  GenNECXCode(131, 17, 2)
#define ROTEL_SRC_AUX1  GenNECXCode(131, 17, 3)
#define ROTEL_SRC_AUX2  GenNECXCode(131, 17, 4)
#define ROTEL_SRC_PHONO  GenNECXCode(131, 17, 10)
#define ROTEL_VOL_UP  GenNECXCode(131, 17, 22)
#define ROTEL_VOL_DOWN  GenNECXCode(131, 17, 23)
#define ROTEL_VOL_MUTE  GenNECXCode(131, 17, 24)
#define ROTEL_POWER_OFF  GenNECXCode(131, 17, 128)
#define ROTEL_POWER_ON  GenNECXCode(131, 17, 152)

// Arduino Remote
#define ARDUINO_TYPE NEC
#define ARDUINO_VOL_UP 16736925
#define ARDUINO_VOL_DOWN 16754775
#define ARDUINO_VOL_PAUSE 16712445
#define ARDUINO_POWER 16753245
#define ARDUINO_1 16724175
#define ARDUINO_2 16718055
#define ARDUINO_3 16743045

// Samsung TV remote
#define TV_TYPE SAMSUNG
#define TV_UP -522189063
#define TV_DOWN -522156423
#define TV_ENTER -522184983
#define TV_A -522176823
#define TV_B -522180393
#define TV_C -522147753
#define TV_D -522164073

struct IR {
    int codeType;
    long codeValue;
    int codeLen;
};

// Reverse the order of bits in a byte
// Example: 01000000 -> 00000010
unsigned char ReverseByte(unsigned char b)
{
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return(b);
}

// Calculate 32 bit NECx code
unsigned long GenNECXCode(unsigned char p_Device, unsigned char p_SubDevice, unsigned char p_Function)
{
  unsigned long ReverseDevice = (unsigned long)ReverseByte(p_Device);
  unsigned long ReverseSubDevice = (unsigned long)ReverseByte(p_SubDevice);
  unsigned long ReverseFunction = (unsigned long)ReverseByte(p_Function);
  return((ReverseDevice << 24) | (ReverseSubDevice << 16) | (ReverseFunction << 8) | ((~ReverseFunction) & 0xFF));
}
