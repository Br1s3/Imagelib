#include <stdlib.h>
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


// #include <time.h>
#define delta_rand 9999

#define HEIGHT (5*9)
#define WIDTH (5*16)

int main(int argc, char *argv[])
{
    int choice_format = 1;
    int choice_program = 1;
    int res = -1;
    char format[5];
    argc--;argv++;
    
    if (argc > 0) res = atoi(argv[0]);
    switch (res)
    {
	case 0:
	    printf("WARNING: Wrong argument. Default format: PPM\n");
	    break;
	case 1:
	    printf("INFO: Format chosen PPM 24b color\n");
	    choice_format = 1;
	    break;
	case 2:
	    printf("INFO: Format chosen PPM 8b color\n");
	    choice_format = 2;
	    break;
	case 3:
	    printf("INFO: Format chosen BMP 24b color\n");
	    choice_format = 3;
	    break;
	default:
	    printf("INFO: No format chosen. Default: PPM\n");
	    break;
    }

    res = -1;
    if (argc == 2) res = atoi(argv[1]);
    switch (res)
    {
	case 0:
	    printf("WARNING: Wrong argument. Default program: 1\n");
	    break;
	case 1:
	    printf("INFO: Program Chosen 1\n");
	    choice_program = 1;
	    break;
	case 2:
	    printf("INFO: Program Chosen 2\n");
	    choice_program = 2;
	    break;
	default:
	    printf("INFO: No format chosen. Default: 1\n");
	    break;
    }


    if (choice_format == 1 || choice_format == 2)
        strcpy(format, ".ppm");
    else
        strcpy(format, ".bmp");

    uint8_t ***color = b24_color_alloc(WIDTH, HEIGHT);

    #define NB_FRAME 60
    char tab[NB_FRAME][21];

    for (int i = 0; i < NB_FRAME; ++i) {
    	sprintf(tab[i], "stock/output_%03d%s", i, format);
    }
    
    if (choice_program == 1) {

	for (int z = 0; z < NB_FRAME; ++z) {
    	    for (int i = 0; i < HEIGHT; ++i) {
    		for (int j = 0; j < WIDTH; ++j) {
    		    if (((j+z)/5 + (i+z)/5)%2) {
    			color[i][j][0] = 0xff;
    			color[i][j][1] = 0x00;
    			color[i][j][2] = 0x00;
    		    } else {
    			color[i][j][0] = 0x00;
    			color[i][j][1] = 0x00;
    			color[i][j][2] = 0x00;
    		    }		
    		}
    	    }
	    if (choice_format == 1)
                CreateImagePPM24b(tab[z], color, WIDTH, HEIGHT);
	    else if (choice_format == 2) {
		uint8_t ***convert24b_to_8b = b8_color_alloc(WIDTH, HEIGHT);
		for (int i = 0; i < HEIGHT; i++) {
		    for (int j = 0; j < WIDTH; j++) {
			convert24b_to_8b[i][j][0] = color[i][j][0] | color[i][j][1] | color[i][j][2];
		    }
		}
		CreateImagePPM8b(tab[z], convert24b_to_8b, WIDTH, HEIGHT);
		b8_color_free(convert24b_to_8b, WIDTH, HEIGHT);
	    }
	    else
                CreateImageBMP24b(tab[z], color, WIDTH, HEIGHT);

	}
	b24_color_free(color, WIDTH, HEIGHT);
	printf("Tous les fichier ont été générés au format: %s\n", format);
	
    } else {
	
	for (int z = 0; z < NB_FRAME; ++z) {
	    for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
		    color[i][j][0] = (int)(((float)(rand() % delta_rand)/delta_rand)*256);
		    color[i][j][1] = 0;
		    color[i][j][2] = 256-(int)(((float)(rand() % delta_rand)/delta_rand)*256);
		}
	    }
	    if (choice_format == 1)
                CreateImagePPM24b(tab[z], color, WIDTH, HEIGHT);
	    else if (choice_format == 2)
		CreateImagePPM8b(tab[z], color, WIDTH, HEIGHT);
	    else
                CreateImageBMP24b(tab[z], color, WIDTH, HEIGHT);
	}
	b24_color_free(color, WIDTH, HEIGHT);
	printf("Tous les fichier ont été générés au format: %s\n", format);

    }
    return 0;
}
