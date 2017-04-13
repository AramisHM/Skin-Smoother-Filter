/* 
Aramis's Bitmap File (ahmbmp.h)
copyright (c) 2017 by Aramis Hornung Moraes

MIT LICENSE:

Copyright (c) 2017 Aramis Hornung Moraes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AHMBMP_H
#define AHMBMP_H

typedef struct ahm_pixel
{
	unsigned char r_;
	unsigned char g_;
	unsigned char b_;
}ahm_pixel;

typedef struct ahm_bitmap
{
	unsigned char signature[3];
	unsigned int Filesize;
	unsigned int Dataoffset;
	unsigned int DIBHeaderSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int Planes;
	unsigned int BitCount;
	unsigned int Compression;
	unsigned int ImageSize;
	unsigned int XPixelperM;
	unsigned int YPixelperM;
	unsigned int ColorsUsed;
	unsigned int ColorsImportant;
	unsigned int nPixels;
	unsigned int padding;
	ahm_pixel *pixels;
}ahm_bitmap;


/* Print out all the bitmap's basic headers */
void print_bmp_info(char *filePath);

ahm_bitmap *create_ahmBitmap(unsigned int w, unsigned int h);
void destroy_ahmBitmap(ahm_bitmap *bmp);

unsigned char* create_bmp_data(ahm_bitmap *abmp);

/* Writes the .bmp file into a given path, return 0 if fails or 1 if created .bmp */
int save_bmp(ahm_bitmap *bmp, char *file_path);

/* Reads a .bmp file into a ahm_bitmap structure */
ahm_bitmap *create_bmp_from_file(char *filePath);

ahm_pixel get_pixel(ahm_bitmap *bmp, unsigned int px, unsigned int py);

void set_pixel(ahm_bitmap *bmp, unsigned int px, unsigned int py, unsigned int red, unsigned int green, unsigned int blue);

long unsigned int n_black_pixels(ahm_bitmap *bmp);

#endif

#ifdef __cplusplus
}
#endif