#include <stdio.h>
#include <unistd.h>

#if defined(PROG1)
#    define LIBIMAGEFILE_IMPLEMENTATION
#    include "libImagefile.h"
#elif defined(PROG2)
#    include "libImagefile.h"
#else
#    include "Imagefile.h"
#endif

#define NB_FRAME 60
#define moveto(x, y) printf("\033[%d;%dH", (y), (x))

#define RESET "\e[0m"
#define PRINT_BG_COLOR(R, G, B, c) printf("\e[48;5;%dm%c"RESET, R*36 + G*6 + B + 16, c)
#define PRINT_BG_GRAYSHADE(G, c) printf("\e[48;5;%dm%c"RESET, G+232, c)
#define PRINT_CHAR_COLOR(R, G, B, c) printf("\e[38;5;%dm%c"RESET, R*36 + G*6 + B + 16, c)
#define PRINT_CHAR_GRAYSHADE(G, c) printf("\e[38;5;%dm%c"RESET, G+232, c)


char palette[] = {' ', '`', '.', ':', ';', '!', '/', '*', '^', 'o', 'O', 'G', 'M', '%', '#', '@'};
int main()
{
    int Width;
    int Height;
    int nb_c;

    char tab[NB_FRAME][30];

    for (int i = 0; i < NB_FRAME; ++i) {
    	sprintf(tab[i], "stock/output_%03d.ppm", i);
    }
    
    for (int t = 0; t < NB_FRAME; t++) {
	fprintf(stderr, "INFO: Frame = %d: %s\n", t, tab[t]);
	uint8_t ***color = ReadImage(tab[t], &Width, &Height, &nb_c);
	if (color == NULL) exit(1);
	moveto(0, 0);

	if (nb_c == 1) {
	    for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
		    // for (int c = 0; c < nb_c; c++) {
			//     int toprint = (int)((float)color[i][j][c] * ((float)(sizeof(palette))/(float)(0xff+1)));
			//     putchar(palette[toprint]);
			//     putchar(palette[toprint]);
		    // }
		    int Gprint = (int)((float)color[i][j][0] * ((24.f)/256.f));
		    PRINT_BG_GRAYSHADE(Gprint, ' ');
		    PRINT_BG_GRAYSHADE(Gprint, ' ');
		}
		putchar('\n');
	    }
	} else {
	    for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
		    int Rprint = (int)((float)color[i][j][0] * ((6.f)/256.f));
		    int Gprint = (int)((float)color[i][j][1] * ((6.f)/256.f));
		    int Bprint = (int)((float)color[i][j][2] * ((6.f)/256.f));
		    PRINT_BG_COLOR(Rprint, Gprint, Bprint, ' ');
		    PRINT_BG_COLOR(Rprint, Gprint, Bprint, ' ');
		}
		putchar('\n');
	    }
	}
	
	// for (int i = 0; i < Height; i++) {
	//     for (int j = 0; j < Width; j++) {
	// 	for (int c = 0; c < nb_c; c++) {
	// 	    printf("%c ", palette[color[i][j][c]/(sizeof(palette))]);
	// 	}
	//     }
	//     printf("\n");
	// }
	usleep(50000);
    }
    return 0;
}
