#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*malloc*/
#include "Josephus.h"



char *EndCheck(char *sword, char *arr)
{
	if(*sword == '\0' || *(sword+1) == '\0')
	{
		sword = arr;
	}
	else
	{
		++sword;
	}

	return sword;
}
	

char *MoveToNext(char *sword, char *arr)
{
	sword = EndCheck(sword, arr);

	while (*sword == 'D')
	{
		++sword;
		if(*sword == '\0')
		{
			sword = arr;
		}
	}
	
	return sword;
}

char *kill(char *sword)
{
	
	*sword = 'D';
	
	return sword;
}


int Size(char *arr)
{
	int size = 0;
	char *run = arr;
	while (*run != '\0')
	{
		++run;
		if(*run != '\0')
		{
		++size;
		}
	}

	return size;
}

int Jos(char *arr, int start)
{
	char *sword = arr + start -1;
	int size = Size(arr);
	int alive = size;
	
	if (start > size)
	{
		printf("start point out of range");
		return 0;
	}
	else
	{
		while (alive > 1)
		{
			sword = MoveToNext(sword, arr);
			sword = kill(sword);
			--alive;
			sword = MoveToNext(sword, arr);
		}

	}
	return sword - arr + 1;
}

