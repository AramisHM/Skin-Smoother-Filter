/* 	Aramis' Bitmap Library - Filters
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ahmbmp.h"

#ifndef AHMFILTERS_H
#define AHMFILTERS_H

/* Simple Bilateral Filter */
void bilateralFilter(ahm_bitmap *source, ahm_bitmap *filtered, int diameter, double sigmaI, double sigmaS);
#endif

#ifdef __cplusplus
}
#endif