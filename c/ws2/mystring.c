/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>




/****strlen******/

size_t mystrLen(const char *s) 
{
	assert(NULL != s);
	const char *runner = s;

	while('\0' != *runner)
	{
		++runner;
	}
	return runner-s;
}

/******strcmp******/

int MyStrCmp(const char *s1, const char *s2)
{
	assert(NULL != s1 && NULL != s2);
	
	const char *runner1 = s1, *runner2 = s2;
	int i = 0;

	while(*runner1 == *runner2 && '\0' != *runner1)
	{
	    ++runner1;
	    ++runner2;
	}
	return (*runner1-*runner2);
}

/*******strcpy**********/

char *MyStrCpy(char *dest, const char *src)
{
	assert(NULL != dest && NULL != src);
	
	char *destination = dest;

	while('\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	
	*destination = '\0';
		
	return destination;
}

/********strncpy*********/
	
