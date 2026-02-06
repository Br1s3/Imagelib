#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#if defined(PROG1)
#    define LIBIMAGEFILE_IMPLEMENTATION
#    include "libImagefile.h"
#elif defined(PROG2)
#    include "libImagefile.h"
#else
#    include "Imagefile.h"
#endif

#define Width 0xff
#define Height 0xff

void draw_cercle(uint8_t ***pixels, short width, short height, int x, int y, int radius, const uint32_t fd)
{
   short i, j;
   for (i = -height/2; i < height/2; i++) {
      for (j = -width/2; j < width/2; j++) {
	  if ((i-y)*(i-y) + (j-x)*(j-x) <= radius*radius) {
	      pixels[i + height/2][j + width/2][0] |= fd>>(8*3);
	      pixels[i + height/2][j + width/2][1] |= fd>>(8*2);
	      pixels[i + height/2][j + width/2][2] |= fd>>(8*1);
	  }
      }
   }
}


int main()
{
    const char NimagePPM[] = "stock/RGBAdditiveCircle24b.ppm";
    const char NimageBMP[] = "stock/RGBAdditiveCircle24b.bmp";

    uint8_t ***color = b24_color_alloc(Width, Height);
    draw_cercle(color, Width, Height, -25, 25, 50, 0xff000000);
    draw_cercle(color, Width, Height, 25, 25, 50, 0x00ff0000);
    draw_cercle(color, Width, Height, 0, -25, 50, 0x0000ff00);

    CreateImagePPM24b(NimagePPM, color, Width, Height);
    CreateImageBMP24b(NimageBMP, color, Width, Height);
    puts("tout c'est bien passé");

    b24_color_free(color, Width, Height);
    return 0;
}
