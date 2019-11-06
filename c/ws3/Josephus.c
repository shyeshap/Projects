#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "Env.h"



int *Josephos(int n, int first)
{
	int sold[n] = {[0 ... n] = 1};
	int i = first;
	
	while (i < n)
	{
		while (sold[i] = 0)
		{
			++i;
		}
		if (sold[i + 1] < n)
		{
			sold[i+1] = 0;
		
	 
	
