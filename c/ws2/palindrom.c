#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "palindrom.h"


int IsPalindrome(const char *str)
{
	const char *runner1 = str, *runner2 = str + strlen(str) -1;
	
	assert(NULL != str);
	
	while (runner1 < runner2)
	{
		if (*runner1 != *runner2)
		{
			return 0;
		}
		++runner1;
		--runner2;
	}
	return 1;
}

int IsSeven(int x)
{
	while (x > 0)
	{
		if(x % 10 == 7)
		{
			return 1;
		}
		x /= 10;
	}
	return 0;
}
int *SevenBoom(int from, int to)
{
	int x = from; 
	
	for (x = from; x < to; ++x)
	{
		if (IsSeven(x) || x % 7 == 0)
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%d\n", x);
		}
	}
	printf("\n");
	return 0;
}

/*
void Swap(int **x, int **y)
{
	printf	("\nx initial address: %p\ny inital address: %p\n", *x, *y);
	
	assert(NULL != x && NULL != y);
		
	int **tmp;
	tmp = x;
	x = y;
	y = tmp;
	printf("\nx address after swap: %p\ny address after swap: %p\n\n", *x, *y);
}*/

void SpaceDelete(char *str)
{
	char *runner = str, *runner2 = str+1;
	
	assert(NULL != str);
	
	while (isspace(*runner))
	{
		++runner;
	}
	strcpy(str, runner);
	
	runner2 = runner;
	
	while('\0' != *runner && '\0' != *runner2)
	{
			if (isspace(*runner) && isspace(*(runner+1)))
			{
				while (isspace(*runner2))
				{
					++runner2;
				}
			strcpy(++runner, runner2);
			runner = runner2;
			}
			++runner2;
			++runner;
	}
	--runner;
	if (isspace(*runner))
	{
		*runner = '\0';
	}
	printf("%s\n", str);
}

char *SumLargeNums(const char *l_num1, const char *l_num2)
{
	char *l_num_fin = l_num1, *runner1 = l_num1 + strlen(l_num1);
	int i = 0, delta = l_num1 - l_num2;
	
	if (delta > 0)
	{
		l_num_fin = (char *) malloc (sizeof(char) * (strlen(l_num1) + 1))
	}
	elseif (delta < 0)
	{
		l_num_fin = (char *) malloc (sizeof(char) * (strlen(l_num2) + 1))
	}
	
	while (i > )
	{
		i





