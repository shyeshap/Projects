/************************************/
/*	  								*/
/*    SEARCH						*/
/*    Author: Shye Shapira			*/
/*    Reviewed By: 					*/
/*    Date:     					*/
/************************************/ 

#include <assert.h> /* assert */
#include <math.h> /* sqrt() */

#include "search.h"

#define FREE(x) free(x); x = NULL;

typedef char *byte_t;

void *BinarySearch(void *arr, size_t elm_size, size_t num_of_elm, cmp_func_t cmp, const void *data, const void *param)
{
	size_t mid_in = num_of_elm / 2;
	void *mid_elm = NULL;
	int match = 0;

	assert(NULL != arr);
	assert(NULL != cmp);

	if (0 >= mid_in)
	{
		return NULL;
	}

	mid_elm = (byte_t)arr + (elm_size * mid_in);
	match = cmp(data, mid_elm, param);

	if (0 == match)
	{
		return mid_elm;
	}

	else if (0 < match)
	{
		BinarySearch(mid_elm, elm_size, num_of_elm - mid_in, cmp, data, param);
	}
	
	else
	{
		BinarySearch(arr, elm_size, mid_in, cmp, data, param);
	}

}

void *JumpSearch(void *arr, size_t elm_size, size_t num_of_elm, cmp_func_t cmp, const void *data, const void *param)
{
	int jump = sqrt(num_of_elm);
	size_t i = 0, j = 0;

	assert(NULL != arr);
	assert(NULL != cmp);	

	while (i + jump < num_of_elm && 0 < cmp(data, (byte_t)arr + (i * elm_size), param))
	{
		i += jump;
	}

	if (0 == cmp(data, (byte_t)arr + (i * elm_size), param))
	{
		return (byte_t)arr + (i * elm_size);
	} 

	if (0 > cmp(data, ((byte_t)arr + (i * elm_size)), param))
	{
		BinarySearch((byte_t)arr + (i * elm_size) - jump, elm_size, jump, cmp, data, param);
	}

	if (0 < cmp(data, ((byte_t)arr + (i * elm_size)), param))
	{
		BinarySearch((byte_t)arr + (i * elm_size), elm_size, num_of_elm - i, cmp, data, param);
	}
	return NULL;
}


