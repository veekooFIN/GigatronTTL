/*                                                                                                                     
  __    _ ______  ______  __  __  _____  _____  ______  ____  ____   _   ______  _____  _____   ____  ____   _  ______  
 \  \  //|   ___||   ___||  |/ / /     \/     \|   ___||    ||    \ | | |   ___|/     \|     \ |    ||    \ | ||   ___| 
  \  \// |   ___||   ___||     \ |     ||     ||   ___||    ||     \| | |   |__ |     ||      \|    ||     \| ||   |  | 
   \__/  |______||______||__|\__\\_____/\_____/|___|   |____||__/\____| |______|\_____/|______/|____||__/\____||______| 
                                                                                                                        
                                                                                                                        */ 
/*----------------------------------------------------------------------+
 |                                                                      |
 |             ascfract.c -- demonstrate fractal in text                |
 |                                                                      |
 +----------------------------------------------------------------------*/

#include <conio.h> 
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
      gotoxy(x+1, y+1);
      textcolor(((data-48)*6+1) & 0x3f);
      putch(data);
    }
  }
  break;   
  case 2:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = (JSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (JSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = julia(sx, sy);
      gotoxy(x+1, y+1);
      textcolor(((data-48)*6+1) & 0x3f);
      putch(data);
    }
  }
  break;     
  case 3:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = -0.25 + (BSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = -0.5 + (BSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = burningship(sx, sy);
      gotoxy(x+1, y+1);
      textcolor(((data-48)*6+1) & 0x3f);
      putch(data);
    }
  }
  break; 
  default:
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = -0.7 + (MSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (MSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = mandelbrot(sx, sy);
      gotoxy(x+1, y+1);
      textcolor(((data-48)*6+1) & 0x3f);
      putch(data);
    }
  }
  }
    
  SYS_SetMode(0);
}
