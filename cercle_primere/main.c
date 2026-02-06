#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "Imagefile.h"
#include "graphique.h"

#define delta_rand 9999
#define Width 0xff
#define Height 0xff

// #if 1
int main(int argc, char *argv[])
{
    puts("PROGRAMME 1");
    if (--argc < 1) {
	fprintf(stderr, "Erreur paramètre fonction main\n");
	exit(1);
    }

    char NimagePPM[20];
    sprintf(NimagePPM, "stock/test%s.ppm", argv[argc]);
    char NimageBMP[20];
    sprintf(NimageBMP, "stock/test%s.bmp", argv[argc]);

    uint8_t ***color = color_alloc(Width, Height);

    for (int i = (-Height/2); i < Height/2; i++) {
	for (int j = -Width/2; j < Width/2; j++) {
	    if ((i-(25))*(i-(25)) + (j-(-25))*(j-(-25)) <= 50*50) {
		color[i-(-Height/2)][j-(-Width/2)][0] |= 0xff000000>>(8*3);
		color[i-(-Height/2)][j-(-Width/2)][1] |= 0xff000000>>(8*2);
		color[i-(-Height/2)][j-(-Width/2)][2] |= 0xff000000>>(8*1);
	    }
	}
    }

    for (int i = (-Height/2); i < Height/2; i++) {
	for (int j = -Width/2; j < Width/2; j++) {
	    if ((i-(25))*(i-(25)) + (j-(25))*(j-(25)) <= 50*50) {
		color[i-(-Height/2)][j-(-Width/2)][0] |= 0x00ff0000>>(8*3);
		color[i-(-Height/2)][j-(-Width/2)][1] |= 0x00ff0000>>(8*2);
		color[i-(-Height/2)][j-(-Width/2)][2] |= 0x00ff0000>>(8*1);
	    }
	}
    }

    for (int i = (-Height/2); i < Height/2; i++) {
	for (int j = -Width/2; j < Width/2; j++) {
	    if ((i-(-25))*(i-(-25)) + (j-(0))*(j-(0)) <= 50*50) {
		color[i-(-Height/2)][j-(-Width/2)][0] |= 0x0000ff00>>(8*3);
		color[i-(-Height/2)][j-(-Width/2)][1] |= 0x0000ff00>>(8*2);
		color[i-(-Height/2)][j-(-Width/2)][2] |= 0x0000ff00>>(8*1);
	    }
	}
    }

    // draw_cercle(color, Width, Height, -25, 25, 50, 0xff000000);
    // draw_cercle(color, Width, Height, 25, 25, 50, 0x00ff0000);
    // draw_cercle(color, Width, Height, 0, -25, 50, 0x0000ff00);

    CreateImagePPM(NimagePPM, color, Width, Height);
    CreateImageBMP(NimageBMP, color, Width, Height);
    puts("tout c'est bien passé");

    color_free(color, Width, Height);
    return 0;
}
// #else
// int main(int argc, char *argv[])
// {
//     puts("PROGRAMME 2");
//     char Nimage[20];
//     if (--argc < 1) {
// 	fprintf(stderr, "Erreur paramètre fonction main\n");
// 	exit(1);
//     }
//     sprintf(Nimage, "stock/test%s.bmp", argv[argc]);

//     char **tt1 = mem_alloc(Height, Width);
//     char **tt2 = mem_alloc(Height, Width);
//     char **tt3 = mem_alloc(Height, Width);

//     uint8_t ***color = mem_alloc_3(Height, Width, 3);

//     cons_triangle(tt1, Width, Height, -50, -50, -50, 50, 50, 50, 0xFF);
//     cons_rect(tt2, Width, Height, 0, 0, Width, Height, 0xFF);
//     cons_rect(tt3, Width, Height, 0, 0, Width, Height, 0xFF);
//     for (int i = 0; i < Height; i++) {
// 	for (int j = 0; j < Width; j++) {
// 	    color[i][j][0] = tt1[i][j];
// 	    color[i][j][1] = 0x00;//tt2[i][j];
// 	    color[i][j][2] = 0x00;//tt3[i][j];
// 	}
//     }
//     CreateImage(Nimage, color, Width, Height);
//     puts("tout c'est bien passé");

//     mem_free_3(color, Height, Width);
//     mem_free((void **)tt1, Height);
//     mem_free((void **)tt2, Height);
//     mem_free((void **)tt3, Height);

//     return 0;
// }
// #endif
