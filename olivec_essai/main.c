#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#define WIDTH 800
#define HEIGHT 600

#define try uint8_t handle_err=0;
#define throw(x) do {if (x) handle_err=1;}while(0);
#define catch if (handle_err)

void olivec_fill(uint32_t *pixels[WIDTH], size_t width, size_t height, uint32_t color)
{
    for (size_t y = 0; y < height; y++){
	for (size_t x = 0; x < width; x++) {
	    pixels[y][x] = color;
	}
    }
}

int olivec_save_to_ppm_file(uint32_t **pixels, size_t width, size_t height, const char *file_path)
{
   FILE *f = NULL;

   try
   {
      f = fopen(file_path, "wb");
      throw(f == NULL);
      
      fprintf(f, "P6\n%zu %zu 255\n", width, height);
      throw(ferror(f));
      for (int y = 0; y < height; y++) {
	  for (int x = 0; x < width; x++) {
	      uint32_t pixel = pixels[y][x];
	      uint8_t bytes[3] = {
		  	    (pixel>>(8*0))&0xFF,
			    (pixel>>(8*1))&0xFF,
			    (pixel>>(8*2))&0xFF,
	      };
	      fwrite(bytes, sizeof(bytes), 1, f);
	      throw(ferror(f));
	  }
      }      
   }
   catch
   {
      return errno;
      fclose(f);
   }

   return 0;
      
}

static uint32_t pixels[HEIGHT][WIDTH];

int main()
{
    static uint32_t *ptrpixels[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) ptrpixels[i] = pixels[HEIGHT];
    
   olivec_fill(ptrpixels, WIDTH, HEIGHT, 0xFF0000FF);
   olivec_save_to_ppm_file(ptrpixels, WIDTH, HEIGHT, "test.ppm");
   
   
   fprintf(stdout, "salut tout le monde\n");
   return 0;
}
