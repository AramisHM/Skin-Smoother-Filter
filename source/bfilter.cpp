/* 	Simple Bilateral Filter
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the ahmBitmap project
	read ahmbmp.h for copying conditions.
 */


#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#include "windows.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ahmbmp.h"
#include "ahmycbcr.h"
#include "ahmlux.h"



#define D_PI (3.14159265358979323846f)

/* Returns the distance between two points in 2D space */
/*
float dist2points(int x0, int y0, int x1, int y1)
{
    return (sqrt(pow((float)x0 - x1, 2) + pow((float)y0 - y1, 2)));
}*/

/* Simple linear gaussian function */
double gaussian(float x, double sigma)
{
	return (exp(-(pow(x, 2))/(2 * pow(sigma, 2)))/(2 * D_PI * pow(sigma, 2)));
}

/* Per-pixel bilateral filter iterative function, should be applyed to each pixel in the image. */
void applyBilateralFilter(ahm_bitmap *source, ahm_bitmap *filteredImage, int x, int y, int diameter, double sigmaI, float sigmaS) {

	register long i, j;
	register long double gi, gs, w, iFiltered, wP;
    register float neighbor_x = 0;
    register float neighbor_y = 0;
    register long half = diameter/2;

	gi = gs = w = iFiltered = wP = 0.0f;

	for(i = 0; i < diameter; ++i)
	{
        for(j = 0; j < diameter; ++j)
		{
            neighbor_x = x - (half - i);
            neighbor_y = y - (half - j);

			gi = gaussian((float)get_pixel(source, neighbor_x, neighbor_y).r_ - (float)get_pixel(source, x, y).r_, sigmaI);
            gs = gaussian(sqrt(pow((float)x - neighbor_x, 2.0f) + pow((float)y - neighbor_y, 2.0f)), sigmaS);

            w = gi * gs;

			iFiltered = iFiltered + (float)get_pixel(source, neighbor_x, neighbor_y).r_ * w;

            wP = wP + w;
        }
    }
    iFiltered = iFiltered / wP;

	set_pixel(filteredImage, x, y, (unsigned char)iFiltered, (unsigned char)iFiltered, (unsigned char)iFiltered);
}

/* Bilateral filter function */
void bilateralFilter(ahm_bitmap *source, ahm_bitmap *filtered, int diameter, double sigmaI, double sigmaS) {
    unsigned long i, j;
	unsigned long width = filtered->Width;
    unsigned long height = filtered->Height;

    for(i = 0; i < width; ++i)
	{
        for(j = 0; j < height; ++j)
		{
            applyBilateralFilter(source, filtered, i, j, diameter, sigmaI, sigmaS);

		}
#ifdef WIN32
			system("cls");
			printf("Progress: %d/%d (%d%%)", i, width, (unsigned int)((float)((float)i/(float)width)*100.0f));
#endif
	}
}

#ifdef __cplusplus
}
#endif