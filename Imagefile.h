#ifndef IMAGEFILE_INCLUED_H
#define IMAGEFILE_INCLUED_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


uint8_t ***b24_color_alloc(int w, int h);
int b24_color_free(uint8_t ***tab, int w, int h);

uint8_t ***b8_color_alloc(int w, int h);
int b8_color_free(uint8_t ***tab, int w, int h);

typedef struct {
   char ID[2];
} Signature;

typedef struct {
   uint32_t SizeBMP;
   uint32_t reserved;
   uint32_t Offcet;
} BMPHeader;

typedef struct {
   uint32_t SizeDIB;
   uint32_t Width;
   uint32_t Height;
   uint16_t Plane;
   uint16_t ColorBits;
   uint32_t Compression;
   uint32_t Sizedata;
   uint32_t ResolH;
   uint32_t ResolV;
   uint32_t colorUsed;
   uint32_t colorImportant;
} DIBHeader;

void CreateImagePPM24b(const char *nFile, uint8_t ***color, uint32_t Width, uint32_t Height);
void CreateImagePPM8b(const char *nFile, uint8_t ***color, uint32_t Width, uint32_t Height);

void CreateImageBMP24b(const char *nFile, uint8_t ***color, uint32_t Width, uint32_t Height);

uint8_t ***ReadImage(const char *path, int *w, int *h, int *nb_color);

#endif // IMAGEFILE_INCLUED_H
