/*----------------------------------------------------------------------+
 |                                                                      |
 |     gfxbrot.c -- demonstrate fractal in gfx / quick and dirty        |
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

#define HEIGHT 120
#define WIDTH 160
#define SCALE 1.4
#define YSTEP 1
#define XSTEP 1

int mandelbrot(float x, float y) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = 0;
  b = 0;  
  i = 0;
  while (i < 63)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 32) break;
    
    atemp = a2 - b2 + x;
    b = 2.0 * a * b + y;
    a = atemp;
    i++;
  }
  if(x+y < 4) return i;

  return 0;
}

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int x, y, data;
  int offset = 0;
  float sx, sy;
   
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = -0.7 + SCALE * (WIDTH/2.0 - x) / (WIDTH/2.0);
      sy = SCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0);
      data = mandelbrot(sx, sy);
      offset = ( x + y * WIDTH);
      drawPixel(x,y,data);
    }
  }
}
