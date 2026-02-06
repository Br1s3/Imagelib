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
	for (int i = 0; i < Height; i++) {
	    for (int j = 0; j < Width; j++) {
		for (int c = 0; c < nb_c; c++) {
		    printf("%c ", palette[color[i][j][c]/(sizeof(palette))]);
		}
	    }
	    printf("\n");
	}
	moveto(0, 0);
	usleep(50000);
    }
    return 0;
}
