#include <stdio.h>

#if defined(PROG1)
#    define LIBIMAGEFILE_IMPLEMENTATION
#    include "libImagefile.h"
#elif defined(PROG2)
#    include "libImagefile.h"
#else
#    include "Imagefile.h"
#endif

char palette[] = {' ', '`', '.', ':', ';', '!', '/', '*', '^', 'o', 'O', 'G', 'M', '%', '#', '@'};

int main(int argc, char *argv[])
{
    argc--;argv++;
    char path[40];
    if (argc < 1) {
	fprintf(stderr, "ERROR: No input file to read\n");
	return 1;
    }
    else {
	sprintf(path, "%s", argv[0]);
    }
    int Width;
    int Height;
    int nb_c;

    uint8_t ***color = ReadImage(path, &Width, &Height, &nb_c);
    if (color == NULL) exit(1);
    for (int i = 0; i < Height; i++) {
	for (int j = 0; j < Width; j++) {
	    for (int c = 0; c < nb_c; c++) {
		printf("%03d ", color[i][j][c]);
	    }
	}
	printf("\n");
    }

    return 0;
}
