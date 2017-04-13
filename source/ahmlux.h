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
#endif

#ifdef __cplusplus
}
#endif