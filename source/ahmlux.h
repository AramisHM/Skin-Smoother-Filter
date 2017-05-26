/* 	Logarithmic hue extension (LUX) Colorspace
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"

#ifndef AHMLUX_H
#define AHMLUX_H

/* extractes the L U and X from a given RGB image */
void create_lux(ahm_bitmap *rgb_bmp,
				ahm_bitmap *lux_bmp);

/* extractes the L U and X from a given RGB image and store each channel into an individual RGB image */
void create_lux_channels(ahm_bitmap *rgb_bmp,
	ahm_bitmap *l_bmp,
	ahm_bitmap *u_bmp,
	ahm_bitmap *x_bmp);
#endif

#ifdef __cplusplus
}
#endif