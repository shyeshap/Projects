/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mystring.h"
#include "palindrom.h"

int main()
{
	char s1[] = "bbbb", s2[] = "aahhh";
	char f[] = "    shye       shapira       ";
	
	printf("strcpy: %s\n", strncpy(s1, s2, 2));
	printf("MY strcpy: %s\n", MyStrNCpy(s1, s2, 2));
	
	/*if(IsPalindrome("01210"))
	{
		printf("true\n");
	}
	else
	{
		printf("Fale\n");
	}

	SevenBoom(70, 170);*/
	
	SpaceDelete(f);

	
	return 0;
}



