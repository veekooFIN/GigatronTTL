/*                                                                                                                     
  __    _ ______  ______  __  __  _____  _____  ______  ____  ____   _   ______  _____  _____   ____  ____   _  ______  
 \  \  //|   ___||   ___||  |/ / /     \/     \|   ___||    ||    \ | | |   ___|/     \|     \ |    ||    \ | ||   ___| 
  \  \// |   ___||   ___||     \ |     ||     ||   ___||    ||     \| | |   |__ |     ||      \|    ||     \| ||   |  | 
   \__/  |______||______||__|\__\\_____/\_____/|___|   |____||__/\____| |______|\_____/|______/|____||__/\____||______| 
                                                                                                                        
                                                                                                                        */ 
/*----------------------------------------------------------------------+
 |                                                                      |
 |             ascjulia.c -- demonstrate fractal in text                |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
// Standard includes
#include <gigatron/console.h>
#include <gigatron/sys.h>

#define HEIGHT 15
#define WIDTH 26
#define SCALE 1.7
#define YSTEP 1
#define XSTEP 1
#define CX -0.8
#define CY 0.156

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

void main(void) {
  int x, y, data;
  float sx, sy;
  
  SYS_SetMode(3);
   
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      sx = (SCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (SCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = julia(sx, sy);
      console_state.cx = x;
      console_state.cy = y;
      console_state.fgbg = (((data-48)*6+1) & 0x3f) << 8;
      console_print((char*)&data, 1);
    }
  }
  SYS_SetMode(0);
}
