/*   _____                                 _____                                                                                                                
  __|   _ |__  ______  ______  ____     __| __  |__  ____  ____      ____  __   _  ____   _  ______  ____   _   ______  _____  _____   ____  ____   _  ______   
 \  \  //    ||   ___||   ___||    \   |  |/ /     ||    ||    |    |    ||  | | ||    \ | ||   ___||    \ | | |   ___|/     \|     \ |    ||    \ | ||   ___|  
 |\  \//     ||   ___| `-.`-. |     \  |     \     ||    ||    |_  _|    ||  |_| ||     \| ||   ___||     \| | |   |__ |     ||      \|    ||     \| ||   |  |  
 |_\__/    __||______||______||__|\__\ |__|\__\  __||____||______||______||______||__/\____||______||__/\____| |______|\_____/|______/|____||__/\____||______|  
    |_____|                               |_____|                                                                                                               
                                           _                                                                                                                    
  _____   __   _  ____  ______  __  __    / |  _____   ____  _____    __  __    _                                                                               
 /     \ |  | | ||    ||   ___||  |/ /   / /  |     \ |    ||     | _|  |_\ \  //                                                                               
 |     | |  |_| ||    ||   |__ |     \  |_/   |      \|    ||     \|_    _|\ \//                                                                                
 \___/\_\|______||____||______||__|\__\       |______/|____||__|\__\ |__|  /__/                                                                                 
                                                  _                                                                                                             
   __    _ ______  ______  __  __  _____  _____   / |______  ____  ____   _                                                                                     
  \  \  //|   ___||   ___||  |/ / /     \/     \ / /|   ___||    ||    \ | |                                                                                     
   \  \// |   ___||   ___||     \ |     ||     ||_/ |   ___||    ||     \| |                                                                                     
    \__/  |______||______||__|\__\\_____/\_____/    |___|   |____||__/\____|*/ 

/*----------------------------------------------------------------------+
 |                                                                      |
 |             longfract.c -- demonstrate fractal in gfx                |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <gigatron/sys.h>
#include <gigatron/console.h>

#define WIDTH 160
#define HEIGHT 120
#define NORM_BITS 13
#define F 8192

int readint(const char *prompt)
{
  char buffer[32];
  cprintf(prompt, strlen(prompt));
  console_readline(buffer, sizeof(buffer));
  return atoi(buffer);
}
  
int longfract(long real0, long imag0, int parr) {
  long realq, imagq; 
  long real, imag;
  int i;
  long cx, cy; 

  //longjulia
  cx = (long) ((-0.8) * (float) F);
  cy = (long) ((0.156) * (float) F);

  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORM_BITS;
    imagq = (imag * imag) >> NORM_BITS;

    if ((realq + imagq) > 32768) break;
    
    switch(parr){    
    case 1:    
    //burnship
    imag = abs((real * imag) >> (NORM_BITS - 1)) + imag0;
    real = realq - imagq + real0; 
    break;    
    case 2:    
    //burnship
    imag = abs((real * imag) >> (NORM_BITS - 1)) + imag0;
    real = realq - imagq + real0;
    break;    
    case 3:    
    //longbrot
    imag = ((real * imag) >> (NORM_BITS - 1)) + imag0;
    real = realq - imagq + real0; 
    break;
    case 4:    
    //longjulia
    imag = ((real * imag) >> (NORM_BITS - 1)) + cy;
    real = realq - imagq + cx;
    break;
    }  
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
 
  cprintf("Long Integer Fractals:\n");
  cprintf("#1 Burning Ship\n"); 
  cprintf("#2 Burning Ship Zoomed\n"); 
  cprintf("#3 Mandelbrot\n"); 
  cprintf("#4 Julia\n"); 
  par=readint("\nChoose Fractal #1-4:");
  
  SYS_SetMode(3);
 
  switch(par){    
  case 1:    
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
  //longbrot
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
  } 

  switch(par){    
  case 1:    
  //burnship
  realmin = (long) ((-2.1) * (float) F);
  realmax = (long) ((1.3) * (float) F);
  imagmin = (long) ((-1.9) * (float) F);
  imagmax = (long) ((0.7) * (float) F);   
  break;    
  case 2:    
  //burnshipX
  realmin = (long) ((-1.8) * (float) F);
  realmax = (long) ((-1.7) * (float) F);
  imagmin = (long) ((-0.08) * (float) F);
  imagmax = (long) ((0.01) * (float) F);    
  break;    
  case 3:    
  //longbrot
  realmin = (long) ((-2.0) * (float) F);
  realmax = (long) ((0.7) * (float) F);
  imagmin = (long) ((-1.2) * (float) F);
  imagmax = (long) ((1.2) * (float) F);    
  break;
  case 4:    
  //longjulia
  realmin = (long) ((-2.0) * (float) F);
  realmax = (long) ((2.0) * (float) F);
  imagmin = (long) ((-1.2) * (float) F);
  imagmax = (long) ((1.2) * (float) F);    
  break;
  }     
     
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,col[15]);
    }
  } 
  
  deltareal = (realmax - realmin) / (long) WIDTH;
  deltaimag = (imagmax - imagmin) / (long) HEIGHT;

  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    
    switch(par){    
    case 1:    
    //burnship
    imag0 = imagmin;  
    break;    
    case 2:    
    //burnshipX
    imag0 = imagmin;  
    break;    
    case 3:    
    //longbrot+julia
    imag0 = imagmax;  
    break;
    case 4:    
    //longbrot+julia
    imag0 = imagmax;  
    break;
    }     
    
    for(y = 0; y < HEIGHT; y++ ) {
      data = longfract(real0, imag0, par);
      drawPixel(x,y,col[data]);
      
      switch(par){    
      case 1:    
      //burnship
      imag0 += deltaimag; 
      break;    
      case 2:    
      //burnship
      imag0 += deltaimag;
      break;    
      case 3:    
      //longbrot+julia
      imag0 -= deltaimag;
      break;
      case 4:    
      //longbrot+julia
      imag0 -= deltaimag; 
      break;
      }   
      
    }
    real0 += deltareal;
  }
  SYS_SetMode(0);
}
