#include <stdio.h>

#define LIBIMAGEFILE_IMPLEMENTATION
#include "libImagefile.h"

#define LIBGRAPH_IMPLEMENTATION
#include "libgraph.h"

#define WIDTH (4*16)
#define HEIGHT (7*9)

char palette[] = {' ', '`', '.', ':', ';', '!', '/', '*', '^', 'o', 'O', 'M', '0', '%', '#', '@'};


void ImageSample24b(const char *namefile, int w, int h)
{
    uint8_t ***color = b24_color_alloc(w, h);
    
    // for (int i = 0; i < h; i++) {
    // 	for (int j = 0; j < w; j++) {
    // 	    if ((i%2) ^ (j%2)) {
    // 	        color[i][j][0] = 0xff;
    // 	        color[i][j][1] = 0x00;
    // 	        color[i][j][2] = 0x00;
    // 	    }
    // 	    else {
    // 	        color[i][j][0] = 0xff;
    // 	        color[i][j][1] = 0xff;
    // 	        color[i][j][2] = 0xff;
    // 	    }
    // 	}
    // }
    
    draw_cercle(color, w, h, -10, 10, 20, 0xff0000, 3);
    draw_cercle(color, w, h, 10, 10, 20 ,  0x00ff00, 3);
    draw_cercle(color, w, h, 0, -10, 20 , 0x0000ff, 3);
    
    CreateImagePPM24b(namefile, color, w, h);
    // CreateImageBMP24b(namefile, color, w, h);
    
    b24_color_free(color, w, h);
}

void ImageSample8b(const char *namefile, int w, int h)
{
    uint8_t ***colored = b24_color_alloc(w, h);
    uint8_t ***color = b8_color_alloc(w, h);
    
    // for (int i = 0; i < h; i++) {
    // 	for (int j = 0; j < w; j++) {
    // 	    int grid = 10;
    // 	    if (((i/grid)%2) ^ ((j/grid)%2)) {
    // 	        *color[i][j] = 0x0f;
    // 	    }
    // 	    else {
    // 		*color[i][j] = 0xff;
    // 	    }
    // 	}
    // }    

    for (int i = 0; i < h; i++) {
	for (int j = 0; j < w; j++) {
	    *color[i][j] = 0x00;
	}
    }    
    
    draw_cercle(colored, w, h, -10, 10, 20, 0b00011111, 3);
    draw_cercle(colored, w, h, 10, 10, 20,  0b01100000, 3);
    draw_cercle(colored, w, h, 0, -10, 20,  0b10000000, 3);

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
    const char *path = "test.ppm";
    // ImageSample24b(path, WIDTH, HEIGHT);
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
