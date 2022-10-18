/*----------------------------------------------------------------------+
 |                                                                      |
 |     burnship.c -- demonstrate fractal in gfx / quick and dirty       |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
// Standard includes
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <gigatron/console.h>
#include <gigatron/sys.h>

#define WIDTH 160
#define HEIGHT 120
#define NORM_BITS 13
#define F 8192

int burnship(long real0, long imag0) {
  long realq, imagq; 
  long real, imag;
  int i;

  real = real0;
  imag = imag0;
  for (i = 0; i < 63; i++)
  {
    realq = (real * real) >> NORM_BITS;
    imagq = (imag * imag) >> NORM_BITS;

    if ((realq + imagq) > 32768) break;

    imag = abs((real * imag) >> (NORM_BITS - 1)) + imag0;
    real = realq - imagq + real0;
  }
  return i;
}

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int x, y, data, col;
  long realmin, imagmin, realmax, imagmax;
  long deltareal, deltaimag, real0, imag0;  
  
  realmin = (long) ((-2.5) * (float) F);
  realmax = (long) ((1.0) * (float) F);
  imagmin = (long) ((-1.0) * (float) F);
  imagmax = (long) ((1.0) * (float) F); 
   
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,0);
    }
  } 
  
  deltareal = (realmax - realmin) / (long) WIDTH;
  deltaimag = (imagmax - imagmin) / (long) HEIGHT;

  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmax;
    for(y = 0; y < HEIGHT; y++ ) {
      data = burnship(real0, imag0);
      col = 63 - data;
      drawPixel(x,y,col);
      imag0 -= deltaimag;
    }
    real0 += deltareal;
  }
}
