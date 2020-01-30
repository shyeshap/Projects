/*********************************
 *          SHYE SHAIRA          *
 *          20/01/2020           *
 *                               *
 *             HASH              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "ip.h" /*IP API */

#define FREE(ptr) free(ptr); ptr = NULL;

#define m1 0xF0
#define m2 0xCC
#define m3 0xAA

#define BITS_IN_BYTE 8

static unsigned char ByteMirror(unsigned char x);

void IPConvertAddress(ip_t ip_address, unsigned char *ip_str)
{
	unsigned int i = 0, j = 0;
	unsigned char *runner = ip_str;
	unsigned char mask = 1;
	unsigned char container;

	assert(NULL != ip_str);

	for (i = 0; i < ADDRESS_SIZE_IN_BYTES; ++i)
	{
		container = ByteMirror(ip_address[i]);

		for (j = 0; j < BITS_IN_BYTE; ++j)
		{
			*runner = (mask & (container >> j)) + 48;
			++runner;
		}
	}

	*runner = '\0';
}

static unsigned char ByteMirror(unsigned char x)
{
	x = ((x & m1) >> 4)  | ((x & ~m1) << 4);
	x = ((x & m2) >> 2)  | ((x & ~m2) << 2);
	x = ((x & m3) >> 1)  | ((x & ~m3) << 1);
	
	return x; 	
}