/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mystring.h"

size_t mystrLen(const char *s);
int MyStrCmp(const char *s1, const char *s2);
char *MyStrCpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
int mystrcasecmp(const char *s1, const char *s2);
char *strchr(const char *s, int c);


int main()
{
	char s[] = "Hello world";
	
	char s1[] = "ac";
	char s2[] = "A";
	char s3[] = "";
	char s4[] = "achg";
	
	char b1[] = "ac";
	char b2[] = "A";
	char b3[] = "";
	char b4[] = "achg";
	
	char *c1 = "comp";
	char *c2 = "CO!MP";
	char *c3 = "b";
	char *c4 = "";
	
	printf("the length of %s is %ld\n\n", s,mystrLen(s));
	
	/*test strcmp*/
	printf("%d\n", strcmp(s1, s4));
	printf("%d\n", strcmp(s1, s2));
	printf("%d\n\n", strcmp(s2, s1));
	
	printf("%d\n", MyStrCmp(s1, s4));
	printf("%d\n", MyStrCmp(s1, s2));
	printf("%d\n\n", MyStrCmp(s2, s1));
	
	/*test strcpy*/
	printf("%s\n", strcpy(s1, s2));
	printf("%s\n", strcpy(s1, s3));
	printf("%s\n\n", strcpy(s1, s4));


	printf("%s\n", MyStrCpy(b1, b2));
	printf("%s\n", MyStrCpy(b1, b3));
	printf("%s\n\n", MyStrCpy(b1, b4));
	
	/*test strncmp*/
	
	
	printf("%s\n", strncpy(c1, c2, 2));
	printf("%s\n", strncpy(c1, c3, 0));
	printf("%s\n\n", strncpy(c1, c4, 6));

	
	printf("%s\n", mystrncpy(c1, c2, 2));
	printf("%s\n", mystrncpy(c1, c3, 0));
	printf("%s\n\n", mystrncpy(c1, c4, 6));

    /*test strchr*/
    
	printf("%s\n", strchr(s1, 'o'));
	printf("%s\n", strchr(s1, 'p'));
	printf("%s\n\n", strchr(s1, 'a'));
	
	printf("%s\n", mystrchr(s1, 'o'));
	printf("%s\n", mystrchr(s1, 'p'));
	printf("%s\n\n", mystrchr(s1, 'a'));
	
	
	return 0;
}
