/* 	Erosion filter
	copyright (c) 2018 by Aramis Hornung Moraes
	This file is part of the ahmip project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"
#include <math.h>

/* Erode image (working in progress) */
void a_erode(ahm_bitmap *input,
	     ahm_bitmap *output) {

	unsigned int i = 0; /* iterator */
	unsigned int j = 0; /* iterator */

	/* extract the Y */
	for(i = 0; i < rgb_bmp->Width; ++i) {
		for(j = 0; j < rgb_bmp->Height; ++j) {

			float l, u ,x;
			const float M = 255;
			ahm_pixel p = get_pixel(rgb_bmp,i,j);

			l = u = x = 0.0f; /* null initialization */
			u = ((float)p.r_ < l)? (float)(M/2.0f)*(float)((float)(p.r_+1.0f)/(float)(l+1.0f)):		(float)M - (float)((float)(M/2)*(float)((float)(l+1)/(float)(p.r_+1)));
			set_pixel(lux_bmp, i, j, l, u, x);
		}
	}
}

#ifdef __cplusplus
}
#endif
