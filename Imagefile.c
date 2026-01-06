#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "Imagefile.h"


uint8_t ***color_alloc(int w, int h)
{
    uint8_t ***color = (uint8_t ***)malloc(sizeof(uint8_t **)*h);
    for (int i = 0; i < h; i++) {
    	color[i] = (uint8_t **)malloc(sizeof(uint8_t *)*w);
    	for (int j = 0; j < w; j++) {
    	    color[i][j] = (uint8_t *)malloc(sizeof(uint8_t)*3);
    	}
    }
    return color;
}

int color_free(uint8_t ***tab, int w, int h)
{
    if (tab == NULL) return -1;
    for (int i = 0; i < h; i++) {
	for (int j = 0; j < w; j++) {
	    free(tab[i][j]);
	}
	free(tab[i]);
    }
    free(tab);
    return 0;
}

void CreateImagePPM(const char *nFile, uint8_t ***color, uint32_t Width, uint32_t Height)
{
    FILE *f = fopen(nFile, "wb");
    if (f == NULL) {
	fprintf(stderr, "ERROR: could not open file %s: %m\n", nFile);
	exit(1);
    }
    
    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", Width, Height);
    fprintf(f, "255\n");

    for (uint32_t y = 0; y < Height; y++) {
	for (uint32_t x = 0; x < Width; x++) {
	    fputc(color[y][x][0], f);
	    fputc(color[y][x][1], f);
	    fputc(color[y][x][2], f);
	}
    }
    fclose(f);
}


void CreateImageBMP(const char *nFile, uint8_t ***color, uint32_t Width, uint32_t Height)
{
    Signature *id = (Signature *)malloc(sizeof(Signature) + 1);
    BMPHeader *bmph = (BMPHeader *)malloc(sizeof(BMPHeader) + 1);
    DIBHeader *dibh = (DIBHeader *)malloc(sizeof(DIBHeader) + 1);

    if (!dibh || !bmph) {
	fprintf(stderr, "Erreur : %s, ligne : %d\n", strerror(errno), __LINE__);
	exit(1);
    }

    id->ID[0] = 'B';
    id->ID[1] = 'M';

    bmph->SizeBMP = (Width*(Height)*4) + 54;

    bmph->reserved = 0;
    bmph->Offcet = 14 + 40;

    dibh->SizeDIB = 40;

    dibh->Width = Width;
    dibh->Height = Height;

    dibh->Plane = 1;

    dibh->ColorBits = 24;
    dibh->Compression = 0;
    dibh->Sizedata = Width*(Height)*4;
    dibh->ResolH = 0;
    dibh->ResolV = 0;
    dibh->colorUsed = 0;
    dibh->colorImportant = 0;

    FILE *File = NULL;
    File = fopen(nFile, "wb");
    if (File == NULL) {
	fprintf(stderr, "ERROR: could not open file %s: %m\n", nFile);
	exit(1);
    }


    fwrite(id, sizeof(Signature), 1, File);
    fwrite(bmph, sizeof(BMPHeader), 1, File);
    fwrite(dibh, sizeof(DIBHeader), 1, File);


    int ecart = Width;
    while (ecart >= 4) {
	ecart = ecart - 4;
    }

    uint8_t *padding = (uint8_t *)calloc(ecart, sizeof(uint8_t));

    uint32_t i, j;
    for (i = 0; i < Height; i++) {
	for (j = 0; j < Width; j++) {
	    fwrite(color[i][j], sizeof(uint8_t), 3, File);
	}
	fwrite(padding, sizeof(uint8_t), ecart, File);
    }

    fclose(File);

    free(padding);
    free(id);
    free(bmph);
    free(dibh);
}
