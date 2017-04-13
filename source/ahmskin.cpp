/* 	ahmskin.c, skin detection algorithm
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"
//#include <math.h>

/* extractes skin map region given RGB image */
void create_skin_map(ahm_bitmap *rgb_bmp,
				  ahm_bitmap *ycbcr,
				  ahm_bitmap *lux,
				  ahm_bitmap *skin_map,
				  ahm_bitmap *uChannel,
				  ahm_bitmap *experimental)
{
	unsigned int i = 0; /* iterator */
	unsigned int j = 0; /* iterator */

	/* extract the Y */
	for(i = 0; i < rgb_bmp->Width; ++i)
	{
		for(j = 0; j < rgb_bmp->Height; ++j)
		{
			float Ul = 0;
			float SM = 0;

			float SMexpMeu = 0; /* meu skin map */
			float exp = 0;		/* meu skin map sem labios e arredores dos olhos */

			float labios = 0;
			float skinMap = 0;

			ahm_pixel rgb_p = get_pixel(rgb_bmp,i,j);
			ahm_pixel ycc_p = get_pixel(ycbcr,i,j);
			ahm_pixel lux_p = get_pixel(lux,i,j);

			/* original */
			Ul = (((float)((float)rgb_p.r_/(float)rgb_p.g_) < 1.5f) && (rgb_p.r_ > rgb_p.g_ && rgb_p.g_ > 0))? 256.0*(float)((float)rgb_p.g_/(float)rgb_p.r_):255;
			SM  = ((77 <= ycc_p.b_ <= 127) && (0 <= lux_p.g_ <= 249))? lux_p.g_: (lux_p.g_/ycc_p.b_);

			/* custom approach */
			skinMap = ((float)((float)lux_p.g_/ycc_p.b_)-1)*255;
			skinMap = (SM < 250?255:0);

			exp = ((float)((float)lux_p.g_/(float)ycc_p.g_)-1)*255;
			exp = (exp < 255 ? 0:skinMap); /*remove hair, eyes and objects*/
			exp = ((exp == 255 && lux_p.g_!=255) ? Ul:exp); /* merge the 2 skin tone */

			/*get lips*/
			labios = ((exp == 255) ? 255:0);

			/* replace the mapping with Y */
			exp = ((exp > 0) ? ycc_p.r_:0); 
			SMexpMeu = exp;

			/* remove lips */
			exp = ((labios == 255) ? 0:exp); 

			set_pixel(experimental, i, j, exp, exp, exp);
			set_pixel(skin_map, i, j, SMexpMeu, SMexpMeu, SMexpMeu);
			set_pixel(uChannel, i, j, Ul, Ul, Ul);
		}
	}
}

#ifdef __cplusplus
}
#endif