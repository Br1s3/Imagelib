#include <stdio.h>

#if defined(PROG1)
#    define LIBIMAGEFILE_IMPLEMENTATION
#    include "libImagefile.h"
#elif defined(PROG2)
#    include "libImagefile.h"
#else
#    include "Imagefile.h"
#endif

#define RESET "\e[0m"

#define PRINT_BG_COLOR(R, G, B, c) printf("\e[48;5;%dm%c"RESET, R*36 + G*6 + B + 16, c)
#define PRINT_BG_GRAYSHADE(G, c) printf("\e[48;5;%dm%c"RESET, G+232, c)
#define PRINT_CHAR_COLOR(R, G, B, c) printf("\e[38;5;%dm%c"RESET, R*36 + G*6 + B + 16, c)
#define PRINT_CHAR_GRAYSHADE(G, c) printf("\e[38;5;%dm%c"RESET, G+232, c)

// char palette[] = {' ', '`', '.', ':', ';', '!', '/', '*', '^', 'o', 'O', 'G', 'M', '%', '#', '@'};

char palette[] = {' ', '`', '.', ',', ':', ';', '!', 'i', 'l', 'I', '|', '/', '\\', 'r', 'c', 'v', 'x', 'z', 'u', 'n', 'o', 'e', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm', 'A', 'U', 'J', 'C', 'L', 'Q', 'O', 'Z', 'X', '0', '#', 'M', 'W', '&', '8', '%', 'B', '@'};


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
    if (color == NULL) return -1;

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

    return 0;
}

//https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124
