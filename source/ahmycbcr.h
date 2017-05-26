/* 	YCbCr Colorspace
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"

#ifndef AHMYCRCB_H
#define AHMYCRCB_H

/* extractes the Y Cr and Cb from a given RGB image */
void create_ycbcr(ahm_bitmap *rgb_bmp,
				  ahm_bitmap *ycbcr);
/* extractes the Y Cr and Cb from a given RGB image */
void create_ycbcr_channels(ahm_bitmap *rgb_bmp,
	ahm_bitmap *i_y,
	ahm_bitmap *i_cb,
	ahm_bitmap *i_cr);
/* revert color space to RGB from YCbCr */
void ycbcr_to_rgb(ahm_bitmap *ycbcr,
				  ahm_bitmap *rgb_bmp);
#endif

#ifdef __cplusplus
}
#endif