/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



/****strlen******/

size_t mystrLen(const char *s) 
{
	const char *runner = s;
	
	assert(NULL != s); /*WARNING! Can not reciev NULL pointer to s*/

	while ('\0' != *runner)
	{
		++runner;
	}
	return runner-s;
}

/******strcmp******/

int MyStrCmp(const char *s1, const char *s2)
{
	const char *runner1 = s1, *runner2 = s2;
	
	assert(NULL != s1 && NULL != s2); /*WARNING! Can not reciev NULL pointer to s1 and s2*/

	while (*runner1 == *runner2 && '\0' != *runner1)
		{
	    ++runner1;
	    ++runner2;
		}
	return (*runner1-*runner2);
}

/*******strcpy**********/

char *MyStrCpy(char *dest, const char *src)
{
	char *destination = dest;
	
	assert(NULL != dest && NULL != src); /*WARNING! Can not reciev NULL pointer to dest snd src*/

	while ('\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	
	*dest = '\0';
		
	return destination;
}


/*******strncpy**********/

char *mystrncpy(char *dest, const char *src, size_t n)
{
	char *runner = dest;
	size_t i = 0;
	
	assert(NULL != dest && NULL != src); /*WARNING! Can not reciev NULL pointer to dest and src*/

	for(i = 0; i < n; i++)
	{
	*runner = src[i];
	++runner;
	}
	
		
	return dest;
}

/*********strcasecmp*******/

int mystrcasecmp(const char *s1, const char *s2)
{
	const char *runner1 = s1, *runner2 = s2;
	
	assert(NULL != s1 && NULL != s2); /*WARNING! Can not reciev NULL pointer to s1 and s2*/ 

	while (tolower(*runner1) == tolower(*runner2) && '\0' != *runner1)
		{
	    ++runner1;
	    ++runner2;
		}
	return (*runner1-*runner2);
}


/********strchr**********/

char *mystrchr(const char *s, int c)
{
	const char *runner = s;
	
	assert(NULL != s); /*WARNING! Can not reciev NULL pointer to s*/
	
	while (*runner!= c)
	{
		++runner;
	}
	return (char *)runner;
}










