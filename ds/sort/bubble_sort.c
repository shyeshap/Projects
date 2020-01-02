#include <stdio.h>
#include <stdlib.h>

static void Swap(int *x, int *y)
{
	int temp = *x;

	*x = *y;
	*y = temp;
}

void bubble(int *arr, size_t size)
{
	size_t swapped = 0, i = 0, j = 0;
	
	for (i = 0; i < size - 1; ++i)
	{
		swapped = 0;
		
		for (j = 0; j < (size - i - 1); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
		}
		
		if (swapped == 0)
		{
			break;
		}
	}
}

void Insertion(int arr[], size_t size)
{
	size_t i = 1, sorted = 1;
	int current = arr[i], j = 0;
	
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

void Selection(int arr[], size_t size)
{
	int sorted = 0 , min = 0;
	size_t i = 0, j = 0;
	
	while (i < size - 1)
	{
		j = i;
		min = j;
		
		while (j < size)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
			++j;
		}
		
		Swap(&arr[i], &arr[min]);
		++i;  
	}

}

static void PrintArr(int *arr, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n\n");
}

void InitArr(int *arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}
}

int main()
{
	size_t size = 10;
	int *arr = (int *)malloc(size * sizeof(int));
	int arr2[] = {32,6,2,89,1,98,2,5,3,5};
	 
	InitArr(arr, size);
	
	printf("Bubble\n");
	PrintArr(arr, size);
	bubble(arr, size);
	PrintArr(arr, size);
	
	printf("insertion\n");
	InitArr(arr, size);
	PrintArr(arr, size);
	Insertion(arr, size);
	PrintArr(arr, size);
	
	printf("selection\n");
	InitArr(arr, size);
	PrintArr(arr2, size);
	Selection(arr2, size);
	PrintArr(arr2, size);
	
	free(arr);
	
	return 0;
}
