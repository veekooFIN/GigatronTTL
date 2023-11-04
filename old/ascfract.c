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
 |             ascfract.c -- demonstrate fractal in text                |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <gigatron/sys.h>
#include <gigatron/console.h>

#define HEIGHT 15
#define WIDTH 26
#define MSCALE 1.6
#define JSCALE 1.7
#define BSCALE 1.7
#define YSTEP 1
#define XSTEP 1
#define CX -0.8
#define CY 0.156

static int ite;

int readint(const char *prompt)
{
  char buffer[32];
  cprintf(prompt, strlen(prompt));
  console_readline(buffer, sizeof(buffer));
  return atoi(buffer);
}
  
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
  i = 48;
  while (i < 58)
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

int julia(float x, float y) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = x;
  b = y;  
  i = 48;
  while (i < 58)
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

int burningship(float x, float y) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = 0;
  b = 0;  
  i = 48;
  while (i < 58)
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
  int x, y, data, par;
  float sx, sy;
 
  cprintf("Ascii Fractals:\n");
  cprintf("#1 Mandelbrot\n"); 
  cprintf("#2 Julia\n");
  cprintf("#3 Burning Ship\n"); 
  par=readint("Choose Fractal #1-3:");
  
  SYS_SetMode(3);
  
  switch(par){
  case 1:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = -0.7 + (MSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (MSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = mandelbrot(sx, sy);
      console_state.cx = x;
      console_state.cy = y;
      console_state.fgbg = (((data-48)*6+1) & 0x3f) << 8;
      console_print((char*)&data, 1);
    }
  }
  break;   
  case 2:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = (JSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (JSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = julia(sx, sy);
      console_state.cx = x;
      console_state.cy = y;
      console_state.fgbg = (((data-48)*6+1) & 0x3f) << 8;
      console_print((char*)&data, 1);
    }
  }
  break;     
  case 3:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = (BSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = -0.5 + (BSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = burningship(sx, sy);
      console_state.cx = x;
      console_state.cy = y;
      console_state.fgbg = (((data-48)*6+1) & 0x3f) << 8;
      console_print((char*)&data, 1);
    }
  }
  break; 
  default:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = -0.7 + (MSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (MSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = mandelbrot(sx, sy);
      console_state.cx = x;
      console_state.cy = y;
      console_state.fgbg = (((data-48)*6+1) & 0x3f) << 8;
      console_print((char*)&data, 1);
    }
  }
  }
    
  SYS_SetMode(0);
}
