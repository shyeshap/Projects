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
	
/*	while(j<i)
	{
	
	printf("Soldier %d, %c \n",j+1,arr[j]);
	++j;
	}
	*/

return 0;
}



