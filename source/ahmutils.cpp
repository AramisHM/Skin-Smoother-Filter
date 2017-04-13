/* 	Aramis Hornung Moraes Utility lib
	copyright (c) 2017 by Aramis Hornung Moraes
	This file is part of the Aramis Hornung Moraes Utility lib project
	read ahmutils.h for copying conditions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Returns the size of a given file*/
long ahmlu_get_file_size(char* file_path)
{
	FILE *fp;
	long file_size;

	fp = fopen (file_path , "rb");

	if(!fp)
	{
		printf("Can't find or open the file \"%s\" for reading.\n", file_path);
		return 0;
	}

	// Get the file size in bytes.
	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);

	fclose (fp);

	return file_size;
}


/*Returns a char array formated data from a file
WARNING !not null terminated!!!
DO NOT FORGET TO FREE THE RETURN OF THIS FUNCTION!!!
returns 0 if fails*/
unsigned char *ahmlu_create_char_array_from_file(char* file_path)
{
	unsigned char *ret; /* we will store the file data here */
	long fsize; /* the file size */
	FILE * pFile; /* file pointer */

	fsize = ahmlu_get_file_size(file_path);
	ret = (unsigned char*)malloc(fsize*sizeof(unsigned char)); /* allocate needed memory */

	pFile = fopen (file_path, "rb");
  	if (!pFile)
	{

		printf("Can't find or open the file \"%s\" for reading.\n", file_path);
		fputs ("File error",stderr);
		return 0;
	}
	fread (ret,1,fsize,pFile);
	fclose(pFile);

	return ret;
}

/* Reads up to 4 bytes from a unsigned char array and
return the corresponding decimal value of it.
If if fails returns 0 but this might be a number too. */
unsigned int ahmu_read_n_bytes_to_ui32(unsigned char *data,
									   unsigned int start_point,
									   unsigned int n_bytes)
{
	unsigned int ret = 0;

	if(!data)
        return 0;
	if (n_bytes <= 4)
	{
		if(n_bytes < 1)
			printf("ERROR: Must convert at least 1 byte.\n");
		else
		{
			unsigned int i; /* iterator */
			unsigned int sum = 0;
			unsigned int factor = 1; /* multiplication factor, always multiplicated by 256(2^8bits) */

			for(i = 0; i < n_bytes; ++i)
			{
				sum += data[start_point+i]*factor;
				factor *= (unsigned int)256;
			}
			ret = sum;
		}
	}
	else
		printf("ERROR: Cant'convert more than 4 bytes.\n");
	return ret;
}

/* Writes up to 4 bytes to a unsigned char array and
from a decimal value */
void ahmu_write_n_bytes_to_ui32(unsigned char *dest,
								unsigned int start_point,
								unsigned int value)
{
	unsigned int i; /* iterator */
	unsigned int factor = 16777216;
	unsigned char outputData[4] = {0, 0, 0, 0};

	double decimals = 0;
	double primary_val = 0;
	double division_ret = 0;
	int n_bytes_to_write = 0;

	if(value > 4294967295 || value < 0)
	{
		printf("ERROR: The value exceeds the buffer.\n");
		return;
	}

	for(i = 4; i > 0; --i)
	{
		division_ret =  value/factor;
		decimals = modf(division_ret, &primary_val);
		if(primary_val > 0)
		{
			outputData[i-1]=primary_val;
			n_bytes_to_write = (n_bytes_to_write>i?n_bytes_to_write:i);
			value -= primary_val*factor;
		}
		factor /= 256;
	}

	for(i = 0; i < n_bytes_to_write; ++i)
		dest[start_point+i] = outputData[i];

}


#ifdef __cplusplus
}
#endif
