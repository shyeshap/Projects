#include <stdio.h>
#include <stdlib.h> /*rand*/
#include <math.h>
#include "Josephus.h"


int main()
{
	
	char arr[101];
	int i = 0,j = 0;
	char *ptr_arr = arr;
	
	while(i<101)
	{
		arr[i] = 'L';
		++i;
	}
	
	printf("%d\n", Jos(ptr_arr, 1));

return 0;
}



