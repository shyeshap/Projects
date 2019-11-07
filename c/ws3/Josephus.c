#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*malloc*/
#include "Josephus.h"



int Josephus(int solds_num)
{
	int *solds_arr = (int *) malloc (sizeof(int) * solds_num);
	int alive = solds_num, i = 0, j = 1;
	
	while (i < solds_num)
	{
		solds_arr[i] = 1;
		i++;
	}

	while (alive > 1)
	{
		move
		solds_arr[j] = 0;
		--alive;
		move
		
		
		
		
	}
	return j;
}
		
void movetonextalive(int current, int *solds_arr, int solds_num)
{
	if (j == solds_num)
		{
			j = 0;
		}
	++j;
	if (j == solds_num)
		{
			j = 0;
		}	
	while (0 == solds_arr[j])
	{	
		++j;	
	}
	
	if (j == solds_num)
		{
			j = 0;
		}
	
	
	
}
