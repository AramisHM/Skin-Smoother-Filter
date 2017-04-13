/* 	Logarithmic hue extension (LUX) Colorspace
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"
#include <math.h>

/* extractes the L U and X from a given RGB image */
void create_lux(ahm_bitmap *rgb_bmp,
				  ahm_bitmap *lux_bmp)
{
	unsigned int i = 0; /* iterator */
	unsigned int j = 0; /* iterator */
	
	
	/* extract the Y */
	for(i = 0; i < rgb_bmp->Width; ++i)
	{
		for(j = 0; j < rgb_bmp->Height; ++j)
		{
			float l, u ,x;
			const float M = 255;
			ahm_pixel p = get_pixel(rgb_bmp,i,j);

			l = u = x = 0.0f; /* null initialization */
			
			/* casting the value is importante because certain compilers need this to be very explicit */
			l  = (float)(powf((float)(((float)p.r_) + 1.0f),0.3f) + powf((float)(((float)p.g_) + 1.0f),0.6f) + powf((float)((float)p.b_ + 1.0f),0.1f)) - 1.0f;
			u = ((float)p.r_ < l)? (float)(M/2.0f)*(float)((float)(p.r_+1.0f)/(float)(l+1.0f)):		(float)M - (float)((float)(M/2)*(float)((float)(l+1)/(float)(p.r_+1)));
			x = ((float)p.r_ < l)? (float)(M/2.0f)*(float)((float)(p.b_+1.0f)/(float)(l+1.0f)):		(float)M - (float)((float)(M/2)*(float)((float)(l+1)/(float)(p.b_+1)));
			

			set_pixel(lux_bmp, i, j, l, u, x);
		}
	}
}

#ifdef __cplusplus
}
#endif