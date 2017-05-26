/* 	Color Space YCbCr
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"
#include <math.h>

#ifndef max
#define max(a,b)((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b)((a)<(b)?(a):(b))
#endif

/* extractes the Y Cr and Cb from a given RGB image */
void create_ycbcr(ahm_bitmap *rgb_bmp,
				  ahm_bitmap *ycbcr)
{
	unsigned int i = 0; /* iterator */
	unsigned int j = 0; /* iterator */
	
	/* extract the Y */
	for(i = 0; i < rgb_bmp->Width; ++i)
	{
		for(j = 0; j < rgb_bmp->Height; ++j)
		{
			ahm_pixel p = get_pixel(rgb_bmp,i,j);

			int y  = (int)( 0.299f	* p.r_ + 0.587f		* p.g_ + 0.098f		* p.b_) + 3;
			int cb = (int)(-0.1687f * p.r_ - 0.33126f	* p.g_ + 0.50059f	* p.b_) + 128;
			int cr = (int)( 0.500f	* p.r_ - 0.4187f	* p.g_ - 0.0813f	* p.b_) + 128;

			set_pixel(ycbcr, i, j, y, cb, cr);
		}
	}
}

/* extractes the Y Cr and Cb from a given RGB image */
void create_ycbcr_channels(ahm_bitmap *rgb_bmp,
	ahm_bitmap *i_y,
	ahm_bitmap *i_cb,
	ahm_bitmap *i_cr)
{
	unsigned int i = 0; /* iterator */
	unsigned int j = 0; /* iterator */

						/* extract the Y */
	for (i = 0; i < rgb_bmp->Width; ++i)
	{
		for (j = 0; j < rgb_bmp->Height; ++j)
		{
			ahm_pixel p = get_pixel(rgb_bmp, i, j);

			int y = (int)(0.299f	* p.r_ + 0.587f		* p.g_ + 0.098f		* p.b_) + 3;
			int cb = (int)(-0.1687f * p.r_ - 0.33126f	* p.g_ + 0.50059f	* p.b_) + 128;
			int cr = (int)(0.500f	* p.r_ - 0.4187f	* p.g_ - 0.0813f	* p.b_) + 128;

			set_pixel(i_y, i, j, y, y, y);
			set_pixel(i_cb, i, j, cb, cb, cb);
			set_pixel(i_cr, i, j, cr, cr, cr);
		}
	}
}

/* revert color space to RGB from YCbCr */
void ycbcr_to_rgb(ahm_bitmap *ycbcr,
				  ahm_bitmap *rgb_bmp)
{
	unsigned int i = 0; /* iterator */
	unsigned int j = 0; /* iterator */
	
	/* extract the Y */
	for(i = 0; i < rgb_bmp->Width; ++i)
	{
		for(j = 0; j < rgb_bmp->Height; ++j)
		{
			int y, cb, cr, r, g, b;
			ahm_pixel p = get_pixel(ycbcr,i,j);

			y=p.r_;
			cb=p.g_;
			cr=p.b_;

			r = (int) ((float)y + 1.40200f * (float)((float)cr - (float)128));
			g = (int) ((float)y - 0.34414f * (float)((float)cb - (float)128) - 0.71414f * (float)((float)cr - (float)0x80));
			b = (int) ((float)y + 1.77200f * (float)((float)cb - (float)128));

			r = max(0, min(255, r));
			g = max(0, min(255, g));
			b = max(0, min(255, b));

			set_pixel(rgb_bmp, i, j, r, g, b);
		}
	}
}

#ifdef __cplusplus
}
#endif