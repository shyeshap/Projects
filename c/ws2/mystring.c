/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>


size_t mystrLen(const char *s);
int MyStrCmp(const char *s1, const char *s2);
char *MyStrCpy(char *dest, const char *src);

int main()
{
	char s[] = "Hello world";
	printf("the length of %s is %ld\n\n", s,mystrLen(s));
	

	/*test*/
	char s1[] = "ac";
	char s2[] = "A";
	char s3[] = "";
	char s4[] = "achg";
	printf("%d\n", strcmp(s1, s4));
	printf("%d\n", strcmp(s1, s2));
	printf("%d\n\n", strcmp(s2, s1));
	
	printf("%d\n", MyStrCmp(s1, s4));
	printf("%d\n", MyStrCmp(s1, s2));
	printf("%d\n\n", MyStrCmp(s2, s1));
	
	printf("%s\n", strcpy(s1, s2));
	printf("%s\n", strcpy(s1, s3));
	printf("%s\n\n", strcpy(s1, s4));

	printf("%s\n", MyStrCpy(a1, a2));
	printf("%s\n", MyStrCpy(a1, a3));
	printf("%s\n", MyStrCpy(a1, a4));
	
	
	
	return 0;
}

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
	char *d = dest;
	const char *s = src;
	int i = 0;
	while('\0' != *src)
	{
		d[i] = *src;
		++src;
	}
		
	return d;
}
	
