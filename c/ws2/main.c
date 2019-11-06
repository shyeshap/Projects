/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mystring.h"



int main()
{
	char s1[] = "bbbb", s2[] = "aahhh";
	
	printf("strcpy: %s\n", strncpy(s1, s2, 2));
	printf("MY strcpy: %s\n", MyStrNCpy(s1, s2, 2));

	
	
	return 0;
}
