/* Worksheet2 - Exercise
	string.h */

#include<stdio.h>
#include<assert.h>

size_t strLen(const char *s);
int strCmp(char *s1, char *s2);

int main()
{
	char s[] = "Hello world";
	printf("the length of %s is %ld\n\n", s, strLen(s));
	return 0;
}


size_t strLen(const char *s) 
{
	assert(NULL != s);
	const char *runner = s;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-s;
}


