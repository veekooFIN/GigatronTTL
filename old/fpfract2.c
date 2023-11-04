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
 |             fpfract2.c -- demonstrate fractal in gfx                 |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <gigatron/sys.h>
#include <gigatron/console.h>

#define CX -0.8
#define CY 0.156

int readint(const char *prompt)
{
  char buffer[32];
  cprintf(prompt, strlen(prompt));
  console_readline(buffer, sizeof(buffer));
  return atoi(buffer);
}
  
int mandelbrot(float x, float y, int ITE) {
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
  while (i < ITE)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 4) break;
    
    atemp = a2 - b2 + x;
    b = 2.0 * a * b + y;
    a = atemp;
    i++;
  }
  return i;
}

int julia(float x, float y, int ITE) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = x;
  b = y;  
  i = 0;
  while (i < ITE)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 4) break;
    
    atemp = a2 - b2 + CX;
    b = 2.0 * a * b + CY;
    a = atemp;
    i++;
  }
  return i;
}

int burnship(float x, float y, int ITE) {
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
  while (i < ITE)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 4) break;
    
    atemp = a2 - b2 + x;
    b = fabs(2.0 * a * b) + y;
    a = atemp;
    i++;
  }
  return i;
}

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int par, IT;
  int x, y, data;
  int col;
  float realmin, imagmin, realmax, imagmax;
  float deltareal, deltaimag, real0, imag0;
  int WIDTH; //26 //160
  int HEIGHT; //15 //120
    
  cprintf("Floating Point Fractals:\n");
  cprintf("#1 Mandelbrot\n"); 
  cprintf("#2 Julia\n");
  cprintf("#3 Burning Ship\n"); 
  cprintf("#4 Burning Ship Zoomed\n\n");  
  par=readint("Choose Fractal #1-4:");
  WIDTH=readint("Screen Size X #20-160:");
  HEIGHT=readint("Screen Size Y #15-120:");
  IT=readint("Iteration Count #7-63:");
  
  SYS_SetMode(3);
 
  switch(par){       
  case 1:    
  //mandelbrot
  realmin = -2.0f;
  realmax = 0.7f;
  imagmin = -1.2f;
  imagmax = 1.2f;    
  break;
  case 2:    
  //julia
  realmin = -2.0f;
  realmax = 2.0f;
  imagmin = -1.2f;
  imagmax = 1.2f;    
  break;
  case 3:    
  //burnship
  realmin = -2.1f;
  realmax = 1.3f;
  imagmin = -1.9f;
  imagmax = 0.7f;   
  break;    
  case 4:    
  //burnshipX
  realmin = -1.8f;
  realmax = -1.7f;
  imagmin = -0.08f;
  imagmax = 0.01f;    
  break; 
  default:    
  //mandelbrot
  realmin = -2.0f;
  realmax = 0.7f;
  imagmin = -1.2f;
  imagmax = 1.2f;    
  }     
     
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,0);
    }
  } 
  
  deltareal = (realmax - realmin) / (float) WIDTH;
  deltaimag = (imagmax - imagmin) / (float) HEIGHT;

  switch(par){
  case 1:
  real0 = realmin; 
  for(x = 0; x < WIDTH; x++ ) {
    imag0 = imagmax;
    for(y = 0; y < HEIGHT; y++ ) {
      data = mandelbrot(real0, imag0, IT);
      col = IT - data;
      drawPixel(x,y,col);
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
      data = julia(real0, imag0, IT);
      col = IT - data;
      drawPixel(x,y,col);
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
      data = burnship(real0, imag0, IT);
      col = IT - data;
      drawPixel(x,y,col);
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
      data = burnship(real0, imag0, IT);
      col = IT - data;
      drawPixel(x,y,col);
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
      data = mandelbrot(real0, imag0, IT);
      col = IT - data;
      drawPixel(x,y,col);
      imag0 -= deltaimag;
    }
    real0 += deltareal;
  }
  }
    
  SYS_SetMode(0);
}
