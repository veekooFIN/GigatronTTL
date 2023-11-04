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
 |             intfract.c -- demonstrate fractal in gfx                 |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
#include <string.h>
#include <stdlib.h>
#include <gigatron/sys.h>
#include <gigatron/console.h>

#define NORM_BITS 5
#define F 32

int readint(const char *prompt)
{
  char buffer[32];
  cprintf(prompt, strlen(prompt));
  console_readline(buffer, sizeof(buffer));
  return atoi(buffer);
}
  
int mandelbrot(int real0, int imag0) {
  int realq, imagq; 
  int real, imag;
  int i;

  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORM_BITS;
    imagq = (imag * imag) >> NORM_BITS;

    if ((realq + imagq) > 128) break;
       
    imag = ((real * imag) >> (NORM_BITS - 1)) + imag0;
    real = realq - imagq + real0; 
    }  
  return i;
}

int julia(int real0, int imag0) {
  int realq, imagq; 
  int real, imag;
  int i;
  int cx, cy; 

  //intjulia
  cx = (int) ((-0.8) * (float) F);
  cy = (int) ((0.156) * (float) F);

  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORM_BITS;
    imagq = (imag * imag) >> NORM_BITS;

    if ((realq + imagq) > 128) break;
       
    imag = ((real * imag) >> (NORM_BITS - 1)) + cy;
    real = realq - imagq + cx;
  }
  return i;
}

int burnship(int real0, int imag0) {
  int realq, imagq; 
  int real, imag;
  int i;

  real = real0;
  imag = imag0;
  for (i = 0; i < 15; i++)
  {
    realq = (real * real) >> NORM_BITS;
    imagq = (imag * imag) >> NORM_BITS;

    if ((realq + imagq) > 128) break;
    
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
  int par;
  int x, y, data;
  int col[16];
  int realmin, imagmin, realmax, imagmax;
  int deltareal, deltaimag, real0, imag0;
  int WIDTH; //20 //160
  int HEIGHT; //15 //120
    
 
  cprintf("Integer Fractals:\n");
  cprintf("#1 Mandelbrot\n"); 
  cprintf("#2 Julia\n");
  cprintf("#3 Burning Ship\n"); 
  //cprintf("#4 Burning Ship Zoomed\n\n");  
  par=readint("Choose Fractal #1-3:");
  WIDTH=readint("Screen Size X #20-80:");
  HEIGHT=readint("Screen Size Y #15-60:");
  
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
  realmin = (int) ((-2.0) * (float) F);
  realmax = (int) ((0.7) * (float) F);
  imagmin = (int) ((-1.2) * (float) F);
  imagmax = (int) ((1.2) * (float) F);     
  break;
  case 2:    
  //julia
  realmin = (int) ((-2.0) * (float) F);
  realmax = (int) ((2.0) * (float) F);
  imagmin = (int) ((-1.2) * (float) F);
  imagmax = (int) ((1.2) * (float) F);    
  break;
  case 3:    
  //burnship
  realmin = (int) ((-2.1) * (float) F);
  realmax = (int) ((1.3) * (float) F);
  imagmin = (int) ((-1.9) * (float) F);
  imagmax = (int) ((0.7) * (float) F);   
  break;    
  case 4:    
  //burnshipX
  realmin = (int) ((-1.8) * (float) F);
  realmax = (int) ((-1.7) * (float) F);
  imagmin = (int) ((-0.08) * (float) F);
  imagmax = (int) ((0.01) * (float) F);    
  break; 
  default:    
  //mandelbrot
  realmin = (int) ((-2.0) * (float) F);
  realmax = (int) ((0.7) * (float) F);
  imagmin = (int) ((-1.2) * (float) F);
  imagmax = (int) ((1.2) * (float) F);    
  }     
     
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,col[14]);
    }
  } 
  
  deltareal = (realmax - realmin) / (int) WIDTH;
  deltaimag = (imagmax - imagmin) / (int) HEIGHT;

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
