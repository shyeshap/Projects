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

#include "sorts.h"

#define BITS_IN_BYTE 8
#define FREE(x) free(x); x = NULL;

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

