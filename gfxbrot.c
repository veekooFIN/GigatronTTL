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
  while (i < 15)
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

  return 15;
}

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int x, y, data;
  int col[16];
  float sx, sy;
  
  col[0] = &h01;
  col[1] = &h02;
  col[2] = &h03;
  col[3] = &h07;
  col[4] = &h0b;
  col[5] = &h0f;
  col[6] = &h0e;
  col[7] = &h0d;
  col[8] = &h0c;
  col[9] = &h3c;
  col[10] = &h38;
  col[11] = &h34;
  col[12] = &h30;
  col[13] = &h20;
  col[14] = &h10;
  col[15] = &h00;
   
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = (-0.7 + SCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1.0);
      sy = SCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0);
      data = mandelbrot(sx, sy);
      drawPixel(x,y,col[data]);
    }
  }
}
