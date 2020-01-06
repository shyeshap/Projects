/************************/
/*	Sorting             */
/*	Eliya Goldfisher    */
/*	Last update 6/1/20  */
/************************/

#include <stdlib.h>


#define INT_BITS sizeof(int)*8
#define MIN 0
#define MAX 9
#define UNSWAPPED 1
#define SWAPPED 0
#define FREE(x) { \
                    free(x); \
                    x = NULL; \
                } \

void BubbleSort(int arr[], size_t size)
{
	int flag = UNSWAPPED;
	size_t i = 0;
	size_t j = 0;
	int temp = 0;
   	
	for (; i < size; ++i)
	{
		flag = UNSWAPPED;

		for (j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				flag = SWAPPED;
			}
		}
		
		if (flag == UNSWAPPED)
		{	
			break;
		}
	}
}

void InsertionSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	int element = 0;

	for (i = 1; i < size; ++i)
	{
		j = i - 1;
		element = arr[i];

		while ((element < arr[j]) && (0 != j))
		{
			arr[j + 1] = arr[j];
			--j;	
		}

		if ((j == 0) && (element < arr[j]))
		{
			arr[j + 1] = arr[j];
			j = -1;
		}
		arr[j+1] = element;
	}
}

void SelectionSort(int arr[], size_t size)
{
	size_t i =0;
	size_t j = 0;
	size_t index = 0;
	int min = 0;

	for (; i < size; ++i)
	{
		min = arr[i];
		index = i;

		for (j = i + 1; j < size; ++j)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				index = j;
			}
		}

		arr[index] = arr[i];
		arr[i] = min;
	}
}

int CountingSort(const int *arr, size_t size, int min, int max, int *res)
{
	size_t *count_arr = NULL;
	size_t range = 0;
	size_t i = 0;
	
	range = max - min + 1;
	
	count_arr = (size_t *)calloc(range, sizeof(size_t));
	if (NULL == count_arr)
	{
		return 1;
	}

	for(; i < size; ++i)
	{
		++count_arr[arr[i] - min];
	}	
	
	for(i = 1 ; i < range; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}
	
	for(i = size - 1; 0 < i; --i)
	{
		res[count_arr[arr[i] - min] -1] = arr[i];
		--count_arr[arr[i] - min];
	}
	
	res[count_arr[arr[i] - min] -1] = arr[i];	
	
	FREE(count_arr);

	return 0;
}

static void Zeros(size_t *arr, size_t size)
{
	size_t i = 0;

	for (; i < size; ++i)
	{
		arr[i] = 0;
	}
}

static void RCountingSort(unsigned int *arr, size_t size, unsigned int mask, unsigned int shift, size_t *histogram, unsigned int *res)
{
	size_t i = 0;

	for(; i < size; ++i)
	{
		++histogram[(arr[i] >> shift) & mask];
	}
	
	for(i = 1 ; i < mask + 1; ++i)
	{
		histogram[i] += histogram[i - 1];
	}
	
	for(i = size - 1; 0 < i; --i)
	{
		res[histogram[(arr[i] >> shift) & mask] -1] = arr[i];
		--histogram[(arr[i] >> shift) & mask];
	}
	
	res[histogram[(arr[i] >> shift) & mask] -1] = arr[i];
}

static void ArraySwap(unsigned int **arr, unsigned int **res)
{
	unsigned int *temp = *arr;
	*arr = *res;
	*res = temp;
}

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits)
{
	size_t *histogram = NULL;
	unsigned int *res = NULL;
	unsigned int shift = 0;
	unsigned int mask = 0;
	unsigned int i = 0;
	
	for (i = 0; i < num_of_bits; ++i)
	{
		mask <<= 1;
		mask |= 1;
	}

	histogram = (size_t *)malloc((mask + 1) * sizeof(size_t));
	if (NULL != histogram)
	{
		res = (unsigned int *)malloc(sizeof(unsigned int)*size);
		if (NULL == res)
		{
			FREE(histogram);
			return 1;
		}
	}
	
	for (i = 0; i < INT_BITS/num_of_bits; ++i)
	{
		Zeros(histogram, mask + 1);
		RCountingSort(arr, size, mask, shift, histogram, res);
		ArraySwap(&arr ,&res);
		shift += num_of_bits;
	}

	FREE(res);
	FREE(histogram);
	
	return 0;
}
