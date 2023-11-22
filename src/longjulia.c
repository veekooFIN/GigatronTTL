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
 |             longjulia.c -- demonstrate fractal in gfx                |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
// Standard includes
#include <stdlib.h>
#include <gigatron/sys.h>

#define WIDTH 160
#define HEIGHT 120
#define NORMBITS 13
#define K 8192

int julia(long real0, long imag0) {
  long realq, imagq; 
  long real, imag;
  int i;
  long cx, cy; 
 
  cx = (long) ((-0.8) * (float) K);
  cy = (long) ((0.156) * (float) K);
  
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

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int x, y, data;
  int col[16];
  long realmin, imagmin, realmax, imagmax;
  long deltareal, deltaimag, real0, imag0;  
  
  SYS_SetMode(3);
  
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
  
  realmin = (long) ((-2.0) * (float) K);
  realmax = (long) ((2.0) * (float) K);
  imagmin = (long) ((-1.2) * (float) K);
  imagmax = (long) ((1.2) * (float) K); 
   
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,col[15]);
    }
  } 
  
  deltareal = (realmax - realmin) / (long) WIDTH;
  deltaimag = (imagmax - imagmin) / (long) HEIGHT;

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
  SYS_SetMode(0);
}
