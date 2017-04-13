/*
Aramis Hornung Moraes Utility lib (ahmultils.h)
copyright (c) 2017 by Aramis Hornung Moraes

Copyright (c) 2017 Aramis Hornung Moraes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AHMUTILS_H
#define AHMUTILS_H

/*Returns the size of a given file*/
long ahmlu_get_file_size(char* file_path);

/*Returns a char array formated data from a file, WARNING !
not null terminated!!! DO NOT FORGET
TO FREE THE RETURN OF THIS FUNCTION!!! returns 0 if fails*/
unsigned char *ahmlu_create_char_array_from_file(char* file_path);

/* can read up to 4 bytes from a unsigned char array and return the
corresponding value of it. If if fails returns 0, but this might be
a number too. */
unsigned int ahmu_read_n_bytes_to_ui32(unsigned char *data,
									   unsigned int start_point,
									   unsigned int n_bytes);

/* Writes up to 4 bytes to a unsigned char array and
from a decimal value */
void ahmu_write_n_bytes_to_ui32(unsigned char *dest,
								unsigned int start_point,
								unsigned int value);

#endif

#ifdef __cplusplus
}
#endif