#include <stdio.h>
#include <string.h>

#if defined(PROG1)
#    define LIBIMAGEFILE_IMPLEMENTATION
#    include "libImagefile.h"
#elif defined(PROG2)
#    include "libImagefile.h"
#else
#    include "Imagefile.h"
#endif

#define WIDTH (4*16)
#define HEIGHT (7*9)

char palette[] = {' ', '`', '.', ':', ';', '!', '/', '*', '^', 'o', 'O', 'M', '0', '%', '#', '@'};


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

void ImageSample8b(const char *namefile, int w, int h)
{
    uint8_t ***colored = b24_color_alloc(w, h);
    uint8_t ***color = b8_color_alloc(w, h);
    
    draw_cercle(colored, w, h, -10, 10, 20, 0b00011111<<8);
    draw_cercle(colored, w, h, 10, 10, 20, 0b01100000<<8);
    draw_cercle(colored, w, h, 0, -10, 20, 0b10000000<<8);

    for (int i = 0; i < h; i++) {
	for (int j = 0; j < w; j++) {
	    color[i][j][0] = colored[i][j][0] | colored[i][j][1] | colored[i][j][2];
	}
    }

    CreateImagePPM8b(namefile, color, w, h);
	
    b8_color_free(color, w, h);
    b24_color_free(colored, w, h);
}

int main()
{
    const char path[] = "stock/RGBAdditiveCircle8b.ppm";
    ImageSample8b(path, WIDTH, HEIGHT);
 
    int Width;
    int Height;
    int nb_c;

    uint8_t ***color = ReadImage(path, &Width, &Height, &nb_c);
    if (color == NULL) exit(1);
    for (int i = 0; i < Height; i++) {
	for (int j = 0; j < Width; j++) {
	    for (int c = 0; c < nb_c; c++) {
		printf("%c ", palette[color[i][j][c]/(sizeof(palette))]);
		// printf("%03d ", color[i][j][c]);
	    }
	}
	printf("\n");
    }

    return 0;
}
