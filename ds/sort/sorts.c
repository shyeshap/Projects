/************************************/
/*	  Data Structures				*/
/*    Doubly linked list			*/
/*    Author: Shye Shapira			*/
/*    Reviewed By: Itai				*/
/*    Date:     05/01/2020			*/
/************************************/ 

#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() */ 
#include <time.h> /* clock() */ 
#include <math.h> /* pow() */
#include <string.h> /* memcpy() */
#include <alloca.h> /* alloca() */

#include "sorts.h"

#define BITS_IN_BYTE 8
#define FREE(x) free(x); x = NULL;
#define BYTE_SIZE char *

typedef char *byte_t;

static void Merge(int *src_arr, int *dest_arr, size_t first_in, size_t mid_in, size_t last_in);
static void MergeDevide(int *src_arr, int *dest_arr, size_t first_in, size_t last_in);
static void RadixCountingSort(unsigned int *arr, 
								size_t size, 
								unsigned int mask, 
								unsigned int shift, 
								size_t *histogram, 
								unsigned int *res);
static void GenericSwapIMP(void *arr, size_t indx1, size_t indx2, size_t element_size);
static size_t MedianOfThreeIMP(void *arr, size_t low_in, size_t high_in, size_t element_size,
                									comp_func_t cmp_func);
static size_t PartitionIMP(void *arr, size_t low_in, size_t high_in, size_t element_size,
                 							 comp_func_t cmp_func);
static void QuicksortIMP(void *arr, size_t low_in, size_t high_in, 
							size_t element_size, comp_func_t cmp_func);

/*******************************************************/

void BubbleSort(int *arr, size_t size)
{
	size_t swapped = 0, i = 0, j = 0;
	int temp = 0;
	
	while (swapped == 0)
	{
		swapped = 1;
		
		for (j = 0; j < (size - i - 1); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 0;
			}
		}
		
		++i;
	}
}

void InsertionSort(int *arr, size_t size)
{
	size_t i = 1;
	int current = arr[i];
	long j = 0;
	
	while (i < size)
	{
		current = arr[i];
		j = i - 1;
		
		while (j >= 0 && arr[j] > current)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		
		arr[j + 1] = current;
		++i;
	}
}

void SelectionSort(int *arr, size_t size)
{
	size_t i = 0, j = 0, min_index = 0;
	int temp = 0;
	
	while (i < size - 1)
	{
		j = i;
		min_index = j;
		
		while (j < size)
		{
			if (arr[min_index] > arr[j])
			{
				min_index = j;
			}
			++j;
		}
		
		temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
		++i;  
	}

}

int CountingSort(const int *arr, size_t size, int min, int max, int *res)
{
	size_t range = max - min;
	size_t i = 0;
	size_t *histogram = (size_t *)calloc((range + 1), sizeof(size_t));
	
	if (histogram != NULL)
	{
		for (i = 0; i < size; ++i)
		{
			++histogram[arr[i] - min];
		}
		
		for (i = 0; i < range; ++i)
		{
			histogram[i + 1] += histogram[i];
		}
		
		for(i = size - 1; 0 <= (long)i; --i)
		{
			--histogram[arr[i] - min];
			res[histogram[arr[i] - min]] =  arr[i];
		}
		
		FREE(histogram);
		
		return 0;
	}
	
	return 1;
}

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits)
{
	unsigned int i = 0;
	unsigned int *temp_holder = NULL;
	unsigned int mask = ((1 << num_of_bits) - 1);
	unsigned int shift = 0;
	
	size_t *histogram = (size_t *)malloc((mask + 1) * sizeof(size_t));
	if (histogram != NULL)
	{
		unsigned int *res = (unsigned int *)malloc((size + 1) * sizeof(unsigned int));
		if (res != NULL)
		{
	
			for (i = 0; i < sizeof(int) * BITS_IN_BYTE / num_of_bits; ++i)
			{
				shift = i * num_of_bits;
				RadixCountingSort(arr, size, mask, shift, histogram, res);
				
				temp_holder = arr; /* swap */
				arr = res;
				res = temp_holder;
			}
			
			FREE(res);
			FREE(histogram);
			
			return 0;
		}
		FREE(histogram);
	}

	return 1;
}

void MergeSort(int *src_arr, int *dest_arr, size_t size)
{
	if (size == 1)
	{
		return;
	}

	MergeDevide(src_arr, dest_arr, 0, size - 1);
}

void Quicksort(void *arr, size_t nmemb, size_t element_size,
                 							 comp_func_t cmp_func)
{
	QuicksortIMP(arr, 0, nmemb - 1, element_size, cmp_func);
}

/******************************************************************/

static void QuicksortIMP(void *arr, size_t low_in, size_t high_in, 
							size_t element_size, comp_func_t cmp_func)
{
	if (low_in < high_in)
	{
		size_t pivot_in = PartitionIMP(arr, low_in, high_in, element_size, cmp_func);
		
		QuicksortIMP(arr, low_in, pivot_in - 1, element_size, cmp_func);
		QuicksortIMP(arr, pivot_in, high_in, element_size, cmp_func);
	}
}

static size_t PartitionIMP(void *arr, size_t low_in, size_t high_in, size_t element_size,
                 							 comp_func_t cmp_func)
{
	size_t pivot_in = MedianOfThreeIMP(arr, low_in, high_in, element_size, cmp_func);

	while(1)
	{
		while (0 > cmp_func((byte_t)arr + (low_in * element_size), 
							(byte_t)arr + (high_in * element_size)))
		{
			++low_in;
		} 
		
		while (0 > cmp_func((byte_t)arr + (pivot_in * element_size), 
							(byte_t)arr + (high_in * element_size)))
		{
			--high_in;
		} 

		if (0 <= cmp_func((byte_t)arr + (high_in * element_size), 
							(byte_t)arr + (low_in * element_size)))
		{
			return high_in;
		}

		GenericSwapIMP(arr, low_in, high_in, element_size);
	}

	return high_in;
}

static void GenericSwapIMP(void *arr, size_t indx1, size_t indx2, size_t element_size)
{
	void *temp = alloca(element_size);

	memcpy(temp, ((byte_t)arr + (indx1 * element_size)), element_size);
	memcpy((byte_t)arr + (indx1 * element_size), ((byte_t)arr + (indx2 * element_size)), element_size);
	memcpy((byte_t)arr + (indx2 * element_size), (byte_t)temp, element_size);
}

static size_t MedianOfThreeIMP(void *arr, size_t low_in, size_t high_in, size_t element_size,
                									comp_func_t cmp_func)
{
   size_t mid_in = ((high_in - low_in) / 2) + low_in;
	
	if (0 < cmp_func((byte_t)arr + (mid_in * element_size), arr))
	{
		GenericSwapIMP(arr, mid_in, 0, element_size);
	}

	if (0 < cmp_func((byte_t)arr + (high_in * element_size), arr))
	{
		GenericSwapIMP(arr, high_in, 0, element_size);
	}

	if (0 < cmp_func(((byte_t)arr + (mid_in * element_size)), ((byte_t)arr + (high_in * element_size))))
	{
		GenericSwapIMP(arr, high_in, mid_in, element_size);
	}

	return high_in;
}
	
static void MergeDevide(int *src_arr, int *dest_arr, size_t first_in, size_t last_in)
{
	size_t mid_in = 0;
	
	if (first_in < last_in) 
	{
		mid_in = (first_in + last_in) / 2;
		MergeDevide(src_arr, dest_arr, first_in, mid_in);
		MergeDevide(src_arr, dest_arr, (mid_in + 1), last_in);
		Merge(src_arr, dest_arr, first_in, mid_in, last_in);
	}
}

static void Merge(int *src_arr, int *dest_arr, size_t first_in, size_t mid_in, size_t last_in)
{
		size_t left = first_in, right = mid_in + 1, dst_in = first_in;

		while ((left <= mid_in) && (right <= last_in)) /* length(left) > 0 and length(right) > 0 */ 
		{
			if (src_arr[left] <= src_arr[right]) /* first(left) ≤ first(right) */
			{
				dest_arr[dst_in] = src_arr[left]; /* cpy first(left) into dst */
				++left; /* modve left one forward */ 
			}

			else /* first(right) < first(left) */
			{
				dest_arr[dst_in] = src_arr[right]; /* cpy first right into dst */ 
				++right; /* move right one forwared */
			}

			++dst_in; /* move dst indx one forward */
		}

		if (left > mid_in) 
		{
			for (; right <= last_in; ++right)
			{
				dest_arr[dst_in] = src_arr[right];
				++dst_in;
			}
		}
		
		else
		{
			for (; left <= mid_in; ++left)
			{
				dest_arr[dst_in] = src_arr[left];
				++dst_in;
			}
		}

		for (dst_in = first_in; dst_in <= last_in; ++dst_in)
		{
			src_arr[dst_in] = dest_arr[dst_in];
		}
}

static void RadixCountingSort(unsigned int *arr, 
								size_t size, 
								unsigned int mask, 
								unsigned int shift, 
								size_t *histogram, 
								unsigned int *res)
{
	size_t i = 0;
	
	for (i = 0; i <= mask; ++i)
	{
		histogram[i] = 0;
	}
	
	for (i = 0; i < size; ++i)
	{
		++histogram[(arr[i] >> shift) & mask];
	}
	
	for (i = 0; i < mask; ++i)
	{
		histogram[i + 1] += histogram[i];
	}
	
	for (i = size - 1; 0 <= (long)i; --i)
	{
		--histogram[(arr[i] >> shift) & mask];
		res[histogram[(arr[i] >> shift) & mask]] = arr[i];
	}
}