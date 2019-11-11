#include <stdio.h>

int Jos(int);

int main()
{
	int n = 100;
	printf("last one for %d soldiers: %d\n", n, Jos(100));
	
	return 0; 
}


int Jos(int n)
{
   int arr[100], i = 0;
   int *runner = arr;
   while (i <100 - 1)
   {
   		runner[i] = i + 1;
   		++i;
   }
   runner[i] = 0;   
   
	i = 0;
	
	while (arr[i] != i)
	{
		arr[i] = arr[arr[i]];
		i = arr[i];
	}
   
   return i+1;
}
