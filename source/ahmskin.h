/* 	ahmskin.c, skin detection algorithm
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"

#ifndef AHMSKIN_H
#define AHMSKIN_H

/* extractes skin map region given RGB image */
void create_skin_map(ahm_bitmap *rgb_bmp,
				  ahm_bitmap *ycbcr,
				  ahm_bitmap *lux,
				  ahm_bitmap *skin_map,
				  ahm_bitmap *uChannel,
				  ahm_bitmap *experimental);

#endif

#ifdef __cplusplus
}
#endif