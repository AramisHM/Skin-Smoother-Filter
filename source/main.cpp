/* Aramis' Bitmap Lib - Copyright (c) 2017 Aramis Hornung Moraes */

#define AHMBMP_VERSION "0.9.6"

#include <stdio.h>
#include "ahmbmp.h"
#include "ahmycbcr.h"
#include "ahmlux.h"
#include "ahmskin.h"
#include "ahmfilters.h"
#include "string.h"

/* debug stuff for MSVC */
#ifdef WIN32
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
#endif
#ifdef WIN32
#include "windows.h"
#endif

void main_process_image(char *file_path)
{
    ahm_bitmap *myBmp;
	ahm_bitmap *ycbcr;
	ahm_bitmap *ycbcr_y;
	ahm_bitmap *ycbcr_cb;
	ahm_bitmap *ycbcr_cr;
	ahm_bitmap *lux;
	ahm_bitmap *lux_l;
	ahm_bitmap *lux_u;
	ahm_bitmap *lux_x;
	ahm_bitmap *skinMap;
	ahm_bitmap *uChannel;
	ahm_bitmap *experimentalskin;
	ahm_bitmap *filtered;
	char *input_file_name;
	char file_output_name[4096];
	
	/* iterators */
	unsigned int i = 0;
	unsigned int j = 0; 

    myBmp = create_bmp_from_file(file_path);
	input_file_name = strtok(file_path, ".");
    if(myBmp == 0)
    {
        destroy_ahmBitmap(myBmp);
		return;
		printf("Error: File is not supported. Only 24bit bitmaps can be processed.\n");
    }

	/* allocate image structures */
	ycbcr=create_ahmBitmap(myBmp->Width,myBmp->Height);
	lux=create_ahmBitmap(myBmp->Width,myBmp->Height);
	lux_l = create_ahmBitmap(myBmp->Width, myBmp->Height);
	lux_u = create_ahmBitmap(myBmp->Width, myBmp->Height);
	lux_x = create_ahmBitmap(myBmp->Width, myBmp->Height);
	ycbcr_y = create_ahmBitmap(myBmp->Width, myBmp->Height);
	ycbcr_cb = create_ahmBitmap(myBmp->Width, myBmp->Height);
	ycbcr_cr = create_ahmBitmap(myBmp->Width, myBmp->Height);
	skinMap=create_ahmBitmap(myBmp->Width,myBmp->Height);
	uChannel=create_ahmBitmap(myBmp->Width,myBmp->Height);
	experimentalskin=create_ahmBitmap(myBmp->Width,myBmp->Height);
	filtered=create_ahmBitmap(myBmp->Width,myBmp->Height);

	/* start processing */
	create_ycbcr(myBmp, ycbcr);
	create_ycbcr_channels(myBmp, ycbcr_y, ycbcr_cb, ycbcr_cr);
	//ycbcr_to_rgb(ycbcr,myBmp); // testing
	create_lux(myBmp, lux);
	create_lux_channels(myBmp, lux_l, lux_u, lux_x);
	bilateralFilter(ycbcr, filtered, 9,20,70);

	for(i=0; i < myBmp->Width; ++i)
	{
		for(j=0; j < myBmp->Height; ++j)
		{
			ahm_pixel p = get_pixel(myBmp, i, j);

			if(p.r_ == 0)
				p.r_++;
			if(p.g_ == 0)
				p.g_++;
			if(p.b_ == 0)
				p.b_++;

			set_pixel(myBmp, i, j, p.r_, p.g_, p.b_);
		}
	}
	create_skin_map(myBmp, ycbcr, lux, skinMap, uChannel, experimentalskin);

	for(i=0; i < myBmp->Width; ++i)
	{
		for(j=0; j < myBmp->Height; ++j)
		{
			unsigned char neval, neval2;

			ahm_pixel p0 = get_pixel(ycbcr, i, j);
			ahm_pixel p1 = get_pixel(experimentalskin, i, j);
			ahm_pixel p2 = get_pixel(filtered, i, j);

			neval = neval2 = 0;

			//neval = (p2.r_ > 0)?p1.r_*(p0.r_-p1.r_):0;
			//neval = p0.r_-p2.r_/2;

			neval2 = (p1.r_>20)? p2.r_: p0.r_;

			set_pixel(uChannel, i, j, neval, neval, neval);
			//set_pixel(lux, i, j, neval2, neval2, neval2);
			//neval2 = p0.r_+neval2;
			set_pixel(ycbcr, i, j, neval2, p0.g_, p0.b_);
		}
	}
	ycbcr_to_rgb(ycbcr,myBmp);

	sprintf(file_output_name, "%s_output.bmp\0", input_file_name);
	save_bmp(myBmp, file_output_name);

	sprintf(file_output_name, "%s_YCbCr.bmp\0", input_file_name);
	save_bmp(ycbcr, file_output_name);

	sprintf(file_output_name, "%s_Y_(YCbCr).bmp\0", input_file_name);
	save_bmp(ycbcr_y, file_output_name);
	sprintf(file_output_name, "%s_Cb_(YCbCr).bmp\0", input_file_name);
	save_bmp(ycbcr_cb, file_output_name);
	sprintf(file_output_name, "%s_Cr_(YCbCr).bmp\0", input_file_name);
	save_bmp(ycbcr_cr, file_output_name);

	sprintf(file_output_name, "%s_LUX.bmp\0", input_file_name);
	save_bmp(lux, file_output_name);

	sprintf(file_output_name, "%s_L_(LUX).bmp\0", input_file_name);
	save_bmp(lux_l, file_output_name);
	sprintf(file_output_name, "%s_U_(LUX).bmp\0", input_file_name);
	save_bmp(lux_u, file_output_name);
	sprintf(file_output_name, "%s_X_(LUX).bmp\0", input_file_name);
	save_bmp(lux_x, file_output_name);

	sprintf(file_output_name, "%s_Pele.bmp\0", input_file_name);
	save_bmp(skinMap, file_output_name);
	
	//save_bmp(experimentalskin,"exp.bmp");

	sprintf(file_output_name, "%s_Filtro.bmp\0", input_file_name);
	save_bmp(filtered, file_output_name);

	destroy_ahmBitmap(lux);
	destroy_ahmBitmap(lux_l);
	destroy_ahmBitmap(lux_u);
	destroy_ahmBitmap(lux_x);
	destroy_ahmBitmap(ycbcr);
	destroy_ahmBitmap(ycbcr_y);
	destroy_ahmBitmap(ycbcr_cb);
	destroy_ahmBitmap(ycbcr_cr);
	destroy_ahmBitmap(skinMap);
	destroy_ahmBitmap(uChannel);
	destroy_ahmBitmap(myBmp);
	destroy_ahmBitmap(experimentalskin);
	destroy_ahmBitmap(filtered);
}

int main(int argc, char *argv[])
{
#ifdef _MSC_VER
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#endif
    //main_process_image("C:\\Users\\IEUser\\Desktop\\ruiva.bmp");

	if(argc > 1)
        main_process_image(argv[1]);
	else
	{
		printf("Usage: parameter 1 = 24bits Bitmap file\n");
		fflush(stdin);
		getchar();
	}

#ifdef _MSC_VER
#ifdef WIN32
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
#endif
	return 0;
}
/*
#if defined(_WIN32)
int APIENTRY _WinMain(HINSTANCE hInstance, HINSTANCE hPevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return main( __argc, __argv);
}
#endif*/
