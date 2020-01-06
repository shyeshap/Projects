#ifndef _SORTS_H_
#define _SORTS_H_

#include <stddef.h>

/* complexity: O(n^2) */
void BubbleSort(int *arr, size_t size);

/* complexity: O(n^2) */
void InsertionSort(int *arr, size_t size);

/* complexity: O(n^2) */
void SelectionSort(int *arr, size_t size);

/* complexity: O(n) */
int CountingSort(const int *arr, size_t size, int min, int max, int *res);

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits);

void InitArr(int *arr, size_t size, int min, int max);

void PrintArr(int *arr, size_t size);

int FindMin(int arr[], size_t size);

int FindMax(int arr[], size_t size);

#endif
