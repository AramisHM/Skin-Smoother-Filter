/* 	Simple Bilateral Filter
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmutils.h" /* bin to dec and vice-versa */
#include "ahmbmp.h" /* bin to dec and vice-versa */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Print out all the bitmap's basic headers */
void print_bmp_info(char *filePath)
{
	unsigned char *bmpData; /*the bmp raw data*/
	int i = 0;

	bmpData =0;

	bmpData = ahmlu_create_char_array_from_file(filePath); /*load file to memory*/

	if(!bmpData)
		return; // failed TODO: print error
	printf("%s\n\n",filePath);
	printf("BITMAPFILEHEADER\n");
	printf("Signature: %c%c\n", 	bmpData[0], bmpData[1]);
	printf("Filesize: %d bytes\n", 	ahmu_read_n_bytes_to_ui32(bmpData, 2, 4));
	printf("Dataoffset: %d\n", 		ahmu_read_n_bytes_to_ui32(bmpData, 10, 2));
	printf("\n\n");
	printf("BITMAPINFOHEADER\n");
	printf("DIB Header Size: %lu\n",ahmu_read_n_bytes_to_ui32(bmpData, 14, 4));
	printf("Width: %lu\n",			ahmu_read_n_bytes_to_ui32(bmpData, 18, 4));
	printf("Height: %lu\n",			ahmu_read_n_bytes_to_ui32(bmpData, 22, 4));
	printf("Planes: %lu\n",			ahmu_read_n_bytes_to_ui32(bmpData, 26, 2));
	printf("BitCount: %lu\n",		ahmu_read_n_bytes_to_ui32(bmpData, 28, 2));
	printf("Compression: %lu\n",	ahmu_read_n_bytes_to_ui32(bmpData, 30, 4));
	printf("ImageSize:%d\n",		ahmu_read_n_bytes_to_ui32(bmpData, 34, 4));
	printf("XPixelperM:%d\n",		ahmu_read_n_bytes_to_ui32(bmpData, 38, 4));
	printf("YPixelperM:%d\n",		ahmu_read_n_bytes_to_ui32(bmpData, 42, 4));
	printf("ColorsUsed:%d\n",		ahmu_read_n_bytes_to_ui32(bmpData, 46, 4));
	printf("ColorsImportant:%d\n",	ahmu_read_n_bytes_to_ui32(bmpData, 50, 4));
	printf("\n\n");

	free(bmpData);
}

/* dev debug func */
long unsigned int n_black_pixels(ahm_bitmap *bmp)
{
	unsigned int i = 0;
	unsigned int j = 0;
	long unsigned int ret_count = 0;
	for(i = 0; i < bmp->Width; ++i)
	{
		for(j = 0; j < bmp->Height; ++j)
		{
			if(get_pixel(bmp, i, j).r_ == 0)
				++ret_count;
		}
	}
	return ret_count;
}

ahm_bitmap *create_ahmBitmap(unsigned int w, unsigned int h)
{
	ahm_bitmap *ret;

	unsigned int ImageSize;
	unsigned int pixelCount;
	unsigned int padding = 0;
	unsigned int i = 0;
	ahm_pixel *raw_bmp_pixels = 0;

	padding = ((w*3)%4==0)?0:(4-((w*3)%4));
	ImageSize = (((w*3)+padding)*h); /* ((wid times 3 color channel (brg)) plus padding) times height */
	pixelCount = w*h;

	raw_bmp_pixels = (ahm_pixel*)calloc(pixelCount+1,sizeof(struct ahm_pixel));

	ret = (ahm_bitmap*)calloc(1,sizeof(ahm_bitmap));
	ret->signature[0] = 'B';
	ret->signature[1] = 'M';
	ret->Filesize =					54 + ImageSize,
	ret->Dataoffset =				54;
	ret->DIBHeaderSize =			40;
	ret->Width =					w;
	ret->Height =					h;
	ret->Planes =					1;
	ret->BitCount =					24;
	ret->Compression =				0;
	ret->ImageSize =				ImageSize;
	ret->XPixelperM =				2835;
	ret->YPixelperM =				2835;
	ret->ColorsUsed =				0;
	ret->ColorsImportant =			0;
	ret->padding =					padding;
	ret->nPixels =					w*h;
	ret->pixels =					raw_bmp_pixels;

	return ret;
}
void destroy_ahmBitmap(ahm_bitmap *bmp)
{
    if(bmp && bmp->pixels)
        free(bmp->pixels);
    if(bmp)
        free(bmp);
}

unsigned char* create_bmp_data(ahm_bitmap *abmp)
{
	unsigned char *bmp_file_bytes;
	unsigned int i; /* iterator */
	unsigned int k; /* iterator */
	unsigned int j = 0; /* iterator */
	unsigned int pix = 0; /* iterator */
	unsigned int padding = abmp->padding;
	bmp_file_bytes = 0;
	bmp_file_bytes = (unsigned char *)calloc(abmp->Filesize+1, sizeof(unsigned char));

	/* write the 54 byte header */
	bmp_file_bytes[0] = 'B';
	bmp_file_bytes[1] = 'M';
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,2,abmp->Filesize);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,10,abmp->Dataoffset);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,14,abmp->DIBHeaderSize);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,18,abmp->Width);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,22,abmp->Height);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,26,abmp->Planes);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,28,abmp->BitCount);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,30,abmp->Compression);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,34,abmp->ImageSize);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,38,abmp->XPixelperM);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,42,abmp->YPixelperM);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,46,abmp->ColorsUsed);
	ahmu_write_n_bytes_to_ui32(bmp_file_bytes,50,abmp->ColorsImportant);

	/*write the image data */
	if(padding)
		j=abmp->Width;

	for(i = abmp->Dataoffset; i < abmp->Filesize; i+=3) /* abmp->Filesize includes the 54 bytes of header */
	{
		if(!j && padding) /* end of line, we reached the padding */
		{
			for(k = 0; k < padding; ++k)
				ahmu_write_n_bytes_to_ui32(bmp_file_bytes,(i+k-abmp->Dataoffset),0);
			j = abmp->Width-1;
			i += padding;
		}
		else if(padding)
			--j;
		if(i < abmp->Filesize)
		{
			ahmu_write_n_bytes_to_ui32(bmp_file_bytes,	(i),	abmp->pixels[pix].b_);
			ahmu_write_n_bytes_to_ui32(bmp_file_bytes,	(i+1),	abmp->pixels[pix].g_);
			ahmu_write_n_bytes_to_ui32(bmp_file_bytes,	(i+2),	abmp->pixels[pix].r_);
			++pix;
		}

	}

	return bmp_file_bytes;
}

/* Writes the .bmp file into a given path, return 0 if fails or 1 if created .bmp */
int save_bmp(ahm_bitmap *bmp, char *file_path)
{
	FILE *fp = 0;
	int ret = 0;
	unsigned char *bmp_bytes = 0;
	if((fp = fopen(file_path,"w+b"))==NULL)
	{
		printf("Error: Could not generate .bmp.\nError reason: Could not open a file at the directory \"%s\"\n",file_path);
		return 0; /* 0 = fail */
	}
	bmp_bytes = create_bmp_data(bmp);

	ret = fwrite(bmp_bytes,
			1,
			bmp->Filesize+1,
			fp);

	free(bmp_bytes); /* must have, since the function generate_bmp_file actually allocated memory to generate this data*/

	fclose(fp);

	return ret;
}

/* Reads a .bmp file into a ahm_bitmap structure */
ahm_bitmap *create_bmp_from_file(char *filePath)
{
	ahm_bitmap *ret = 0;
	unsigned char *file_bytes = 0;
	unsigned int bit_count = 0;
	unsigned int w = 0;
	unsigned int h = 0;
	unsigned int Filesize = 0;
	unsigned int i; /* iterator */
	unsigned int j; /* iterator */
	unsigned int k; /* iterator */
	unsigned int pix = 0; /* iterator */
	unsigned int padding = 0;



	file_bytes = ahmlu_create_char_array_from_file(filePath); /* dont forget to free! */

	bit_count = ahmu_read_n_bytes_to_ui32(file_bytes,28,2);

	if(!bit_count || bit_count > 24)
        return 0;// we don't process more than 24bit

	w = ahmu_read_n_bytes_to_ui32(file_bytes,18,4);
	h = ahmu_read_n_bytes_to_ui32(file_bytes,22,4);
	Filesize = ahmu_read_n_bytes_to_ui32(file_bytes,2,4);

	ret=create_ahmBitmap(w,h);

	padding = ret->padding;

	/*read the image data */
	if(padding)
		j=w;
	for(i = ret->Dataoffset; i < Filesize; i+=3) /* abmp->Filesize includes the abmp->Dataoffset (54) bytes of header */
	{
		if(padding && !j) /* end of line, we reached the padding */
		{
			j = w-1;
			i += ret->padding;
		}
		else if(padding)
			--j;

		if(i < Filesize)
		{
			ret->pixels[pix].b_ = ahmu_read_n_bytes_to_ui32(file_bytes,	(i), 1);
			ret->pixels[pix].g_ = ahmu_read_n_bytes_to_ui32(file_bytes,	(i+1), 1);
			ret->pixels[pix].r_ = ahmu_read_n_bytes_to_ui32(file_bytes,	(i+2), 1);
			++pix;
		}

	}
	free(file_bytes);
	return ret;
}

ahm_pixel get_pixel(ahm_bitmap *bmp, unsigned int px, unsigned int py)
{
	ahm_pixel p;

	unsigned w = 0;
	w = bmp->Width;

	/* make sure we dont surpass the 8 bit value */
	px = (px > bmp->Width-1? bmp->Width-1:px);
	py = (py > bmp->Height-1? bmp->Height-1:py);
	px = (px < 0? 0:px);
	py = (py < 0? 0:py);

	p.r_ = bmp->pixels[px+(py*w)].r_;
	p.g_ = bmp->pixels[px+(py*w)].g_;
	p.b_ = bmp->pixels[px+(py*w)].b_;

	return p;
}
void set_pixel(ahm_bitmap *bmp, unsigned int px, unsigned int py, unsigned int red, unsigned int green, unsigned int blue)
{
	unsigned w = 0;
	w = bmp->Width;

	/* make sure we dont surpass the 8 bit value */
	px = (px > bmp->Width-1? bmp->Width-1:px);
	py = (py > bmp->Height-1? bmp->Height-1:py);
	px = (px < 0? 0:px);
	py = (py < 0? 0:py);

	bmp->pixels[px+(py*w)].r_ = red;
	bmp->pixels[px+(py*w)].g_ = green;
	bmp->pixels[px+(py*w)].b_ = blue;
}

#ifdef __cplusplus
}
#endif
