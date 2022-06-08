#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

void loadBMP(char *fileName, char *destName);

struct BIT_Header
{
  char bfName[2];          // 2 Bytes - 'BM' file format
  unsigned int bfSize;     // 4 Bytes - The size of the file
  unsigned int bfReserved; // 4 Bytes - reserved for application(unused)
  unsigned int bfOffset;   // 4 Bytes - the offset which tells at which byte the image starts
} bit_header;

struct DIB_Header
{
  unsigned int dbSize;            // 4 Bytes for size of the DIB header
  unsigned int dbWidth;           // 4 Bytes for image width:
  unsigned int dbHeight;          // 4 Bytes for image height
  unsigned short int dbBitPlane;  // 2 Bytes for number of color planes
  unsigned short int dbNofPixels; // 2 Bytes for number of bits per pixels
  unsigned char *garbage;         // the remaining bytes are not important
} dib_header;

struct Pixels
{
  int red;   // value for red pixels
  int green; // value for green pixels
  int blue;  // value for blue pixels
  int alpha; // value for alpha pixels (in case it's 32 bytes)
} pixel;
