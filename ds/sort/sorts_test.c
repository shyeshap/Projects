#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() */ 
#include <time.h> /* clock() */ 
#include <string.h> /* memcpy() */

#include "sorts.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define BLUE printf("\x1b[34m")
#define RESET printf("\033[0m")

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);

size_t size = 100000;
int *arr = NULL, *sorted_arr = NULL, *arr_cpy = NULL;
clock_t start_t, end_t;
double total_t;
int min = 0, max = 10000;

int FindMin(int arr[], size_t size)
{
	size_t i = 0;
	int min = arr[i];
	
	for(i = 1; i < (size); ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	
	return min;
}

int FindMax(int arr[], size_t size)
{
	size_t i = 0;
	int max = arr[i];
	
	for(i = 0; i < (size); ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	return max;
}

void PrintArr(int *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n\n");
}

void InitArr(int *arr, size_t size, int min, int max)
{
	size_t i = 0;
	srand(time(0));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % (max - min + 1) + min;
	}
}

int compare(const void *data1, const void *data2)
{
	return *(unsigned int *)data1 - *(unsigned int *)data2;
}
	
void TestBubble()
{
	InitArr(arr, size, min, max);
	memcpy(arr_cpy, arr, size * sizeof(int));

	BLUE;
	printf("\nBubble\n");
	RESET;
	
	start_t = clock();
	BubbleSort(arr, size);
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("BUBBLE: Total time taken by CPU: %f\n\n", total_t);
	
	start_t = clock();
	qsort(arr_cpy, size, sizeof(unsigned int), &compare);
	end_t = clock();
	printf("qsort:\n");
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("QSORT: Total time taken by CPU: %f\n", total_t);
	
	TEST(0 == memcmp(arr, arr_cpy, size), "bubble");
}

void TestInsertion()
{
	BLUE;
	printf("\ninsertion\n");
	RESET;
	
	InitArr(arr, size, min, max);
	
	memcpy(arr_cpy, arr, size * sizeof(int));
	
	start_t = clock();
	InsertionSort(arr, size);
	end_t = clock();

	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("INSERTION: Total time taken by CPU: %f\n\n", total_t);
	
	start_t = clock();
	qsort(arr_cpy, size, sizeof(unsigned int), &compare);
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("QSORT: Total time taken by CPU: %f\n", total_t);
	
	TEST(0 == memcmp(arr, arr_cpy, size), "insertion");
}

void TestSelection()
{
	BLUE;
	printf("\nselection\n");
	RESET;
	
	InitArr(arr, size, min, max);
	
	memcpy(arr_cpy, arr, size * sizeof(int));
	
	start_t = clock();
	SelectionSort(arr, size);
	end_t = clock();

	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("SELECTION: Total time taken by CPU: %f\n\n", total_t);
	
	start_t = clock();
	qsort(arr_cpy, size, sizeof(unsigned int), &compare);
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("QSORT: Total time taken by CPU: %f\n", total_t);
	
	TEST(0 == memcmp(arr, arr_cpy, size), "selection");
}

void TestCount()
{
	BLUE;
	printf("\nCOUNT\n");
	RESET;
	
	InitArr(arr, size, min, max);
	memcpy(arr_cpy, arr, size * sizeof(int));
	
	printf("Find minimum: ");
	printf("%d\n\n", FindMin(arr, size));
	
	printf("Find maximum: ");
	printf("%d\n\n", FindMax(arr, size));
	
	start_t = clock();
	CountingSort(arr, size, FindMin(arr, size), FindMax(arr, size), sorted_arr);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("COUNT: Total time taken by CPU: %f\n", total_t);

	start_t = clock();
	qsort(arr_cpy, size, sizeof(int), &compare);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("QSORT: Total time taken by CPU: %f\n", total_t);
	
	TEST(0 == memcmp(sorted_arr, arr_cpy, size), "counting");
}

void TestRadix()
{	
	BLUE;
	printf("\nRADIX\n");
	RESET;
	
	InitArr(arr, size, 0, max);
	memcpy(arr_cpy, arr, size * sizeof(int));
	
	printf("Find minimum: ");
	printf("%d\n\n", FindMin(arr, size));
	
	printf("Find maximum: ");
	printf("%d\n\n", FindMax(arr, size));
	
	start_t = clock();
	RadixSort((unsigned int *)arr, size, 4); 
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("RADIX: Total time taken by CPU: %f\n", total_t);
	
	start_t = clock();
	qsort(arr_cpy, size, sizeof(unsigned int), &compare);
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("QSORT: Total time taken by CPU: %f\n", total_t);
	
	TEST(0 == memcmp(arr, arr_cpy, size), "radix");
	

}

int main()
{	
	arr = (int *)malloc(size * sizeof(int));
	sorted_arr = (int *)malloc(sizeof(int) * size);
	arr_cpy = (int *)malloc(size * sizeof(int));
	
	TestBubble();
	TestInsertion();
	TestSelection();
	TestCount();
	TestRadix();
	
	free(arr);
	free(sorted_arr);
	
	return 0;
}
