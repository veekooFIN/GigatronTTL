/*                                                                                                                     
  __    _ ______  ______  __  __  _____  _____  ______  ____  ____   _   ______  _____  _____   ____  ____   _  ______  
 \  \  //|   ___||   ___||  |/ / /     \/     \|   ___||    ||    \ | | |   ___|/     \|     \ |    ||    \ | ||   ___| 
  \  \// |   ___||   ___||     \ |     ||     ||   ___||    ||     \| | |   |__ |     ||      \|    ||     \| ||   |  | 
   \__/  |______||______||__|\__\\_____/\_____/|___|   |____||__/\____| |______|\_____/|______/|____||__/\____||______| 
                                                                                                                        
                                                                                                                        */ 
/*----------------------------------------------------------------------+
 |                                                                      |
 |             longfract.c -- demonstrate fractal in gfx                |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
#include <string.h>
#include <stdlib.h>
#include <gigatron/sys.h>
#include <gigatron/console.h>

#define NORMBITS 13
#define K 8192
#define JCX -0.8
#define JCY 0.156

static long cx;
static long cy;

int readint(const char *prompt)
{
  char buffer[32];
  cprintf(prompt, strlen(prompt));
  console_readline(buffer, sizeof(buffer));
  return atoi(buffer);
}
  
int mandelbrot(long real0, long imag0) {
  long realq, imagq; 
  long real, imag;
  int i;

  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORMBITS;
    imagq = (imag * imag) >> NORMBITS;

    if ((realq + imagq) > 32768) break;
       
    imag = ((real * imag) >> (NORMBITS - 1)) + imag0;
    real = realq - imagq + real0; 
    }  
  return i;
}

int julia(long real0, long imag0) {
  long realq, imagq; 
  long real, imag;
  int i;
  
  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORMBITS;
    imagq = (imag * imag) >> NORMBITS;

    if ((realq + imagq) > 32768) break;
       
    imag = ((real * imag) >> (NORMBITS - 1)) + cy;
    real = realq - imagq + cx;
  }
  return i;
}

int burnship(long real0, long imag0) {
  long realq, imagq; 
  long real, imag;
  int i;

  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORMBITS;
    imagq = (imag * imag) >> NORMBITS;

    if ((realq + imagq) > 32768) break;
    
    imag = abs((real * imag) >> (NORMBITS - 1)) + imag0;
    real = realq - imagq + real0; 
  }
  return i;
}

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int par;
  int x, y, data;
  int col[16];
  long realmin, imagmin, realmax, imagmax;
  long deltareal, deltaimag, real0, imag0;
  int WIDTH; //20 //160
  int HEIGHT; //15 //120
    
 
  cprintf("Long Integer Fractals:\n");
  cprintf("#1 Mandelbrot\n"); 
  cprintf("#2 Julia\n");
  cprintf("#3 Burning Ship\n"); 
  cprintf("#4 Burning Ship Zoomed\n\n");  
  par=readint("Choose Fractal #1-4:");
  WIDTH=readint("Screen Size X #20-160:");
  HEIGHT=readint("Screen Size Y #15-120:");
  
  SYS_SetMode(3);
 
switch(par){       
  case 1:    
  //mandelbrot
  col[0] = 0x01;
  col[1] = 0x02;
  col[2] = 0x03;
  col[3] = 0x07;
  col[4] = 0x0b;
  col[5] = 0x0f;
  col[6] = 0x0e;
  col[7] = 0x0d;
  col[8] = 0x0c;
  col[9] = 0x3c;
  col[10] = 0x38;
  col[11] = 0x34;
  col[12] = 0x30;
  col[13] = 0x20;
  col[14] = 0x10;
  col[15] = 0x00;  
  break;
  case 2:    
  //burnship+julia 
  col[14] = 0x01;
  col[13] = 0x02;
  col[12] = 0x03;
  col[11] = 0x07;
  col[10] = 0x0b;
  col[9] = 0x0f;
  col[8] = 0x0e;
  col[7] = 0x0d;
  col[6] = 0x0c;
  col[5] = 0x3c;
  col[4] = 0x38;
  col[3] = 0x34;
  col[2] = 0x30;
  col[1] = 0x20;
  col[0] = 0x10;
  col[15] = 0x00; 
  break;
  case 3:    
  //burnship+julia 
  col[14] = 0x01;
  col[13] = 0x02;
  col[12] = 0x03;
  col[11] = 0x07;
  col[10] = 0x0b;
  col[9] = 0x0f;
  col[8] = 0x0e;
  col[7] = 0x0d;
  col[6] = 0x0c;
  col[5] = 0x3c;
  col[4] = 0x38;
  col[3] = 0x34;
  col[2] = 0x30;
  col[1] = 0x20;
  col[0] = 0x10;
  col[15] = 0x00; 
  break;    
  case 4:    
  //burnship+julia 
  col[14] = 0x01;
  col[13] = 0x02;
  col[12] = 0x03;
  col[11] = 0x07;
  col[10] = 0x0b;
  col[9] = 0x0f;
  col[8] = 0x0e;
  col[7] = 0x0d;
  col[6] = 0x0c;
  col[5] = 0x3c;
  col[4] = 0x38;
  col[3] = 0x34;
  col[2] = 0x30;
  col[1] = 0x20;
  col[0] = 0x10;
  col[15] = 0x00;    
  break; 
  default:    
  //mandelbrot
  col[0] = 0x01;
  col[1] = 0x02;
  col[2] = 0x03;
  col[3] = 0x07;
  col[4] = 0x0b;
  col[5] = 0x0f;
  col[6] = 0x0e;
  col[7] = 0x0d;
  col[8] = 0x0c;
  col[9] = 0x3c;
  col[10] = 0x38;
  col[11] = 0x34;
  col[12] = 0x30;
  col[13] = 0x20;
  col[14] = 0x10;
  col[15] = 0x00;    
  }

  switch(par){       
  case 1:    
  //mandelbrot
  realmin = (long) ((-2.0) * (float) K);
  realmax = (long) ((0.7) * (float) K);
  imagmin = (long) ((-1.2) * (float) K);
  imagmax = (long) ((1.2) * (float) K);    
  break;
  case 2:    
  //julia
  cx = (long) ((JCX) * (float) K);
  cy = (long) ((JCY) * (float) K);
  realmin = (long) ((-2.0) * (float) K);
  realmax = (long) ((2.0) * (float) K);
  imagmin = (long) ((-1.2) * (float) K);
  imagmax = (long) ((1.2) * (float) K);    
  break;
  case 3:    
  //burnship
  realmin = (long) ((-2.1) * (float) K);
  realmax = (long) ((1.3) * (float) K);
  imagmin = (long) ((-1.9) * (float) K);
  imagmax = (long) ((0.7) * (float) K);   
  break;    
  case 4:    
  //burnshipX
  realmin = (long) ((-1.8) * (float) K);
  realmax = (long) ((-1.7) * (float) K);
  imagmin = (long) ((-0.08) * (float) K);
  imagmax = (long) ((0.01) * (float) K);    
  break; 
  default:    
  //mandelbrot
  realmin = (long) ((-2.0) * (float) K);
  realmax = (long) ((0.7) * (float) K);
  imagmin = (long) ((-1.2) * (float) K);
  imagmax = (long) ((1.2) * (float) K);    
  }     
     
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,col[15]);
    }
  } 
  
  deltareal = (realmax - realmin) / (long) WIDTH;
  deltaimag = (imagmax - imagmin) / (long) HEIGHT;

  switch(par){
  case 1:
  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmax;
    for(y = 0; y < HEIGHT; y++ ) {
      data = mandelbrot(real0, imag0);
      drawPixel(x,y,col[data]);
      imag0 -= deltaimag;
    }
    real0 += deltareal;
  }
  break;   
  case 2:
  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmax;
    for(y = 0; y < HEIGHT; y++ ) {
      data = julia(real0, imag0);
      drawPixel(x,y,col[data]);
      imag0 -= deltaimag;
    }
    real0 += deltareal;
  }
  break;     
  case 3:
  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmin;
    for(y = 0; y < HEIGHT; y++ ) {
      data = burnship(real0, imag0);
      drawPixel(x,y,col[data]);
      imag0 += deltaimag;
    }
    real0 += deltareal;
  }
  break; 
  case 4:  
  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmin;
    for(y = 0; y < HEIGHT; y++ ) {
      data = burnship(real0, imag0);
      drawPixel(x,y,col[data]);
      imag0 += deltaimag;
    }
    real0 += deltareal;
  }
  break;
  default:
  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmax;
    for(y = 0; y < HEIGHT; y++ ) {
      data = mandelbrot(real0, imag0);
      drawPixel(x,y,col[data]);
      imag0 -= deltaimag;
    }
    real0 += deltareal;
  }
  }
    
  SYS_SetMode(0);
}
