/* Worksheet2 - Exercise
	string.h */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mystring.h"



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
	

	printf("mystrlen\n");
	printf("the length of %s is %ld\n\n", s,MyStrLen(s));
	
	/*test strcmp*/
	printf("***strcmp***\n");
	printf("%d\n", strcmp(s1, s4));
	printf("%d\n", strcmp(s1, s2));
	printf("%d\n\n", strcmp(s2, s1));
	
	printf("***mystrcmp***\n");
	printf("%d\n", MyStrCmp(s1, s4));
	printf("%d\n", MyStrCmp(s1, s2));
	printf("%d\n\n", MyStrCmp(s2, s1));
	
	/*test strcpy*/
	printf("***strcpy***\n");
	printf("%s\n", strcpy(s1, s2));
	printf("%s\n", strcpy(s1, s3));
	printf("%s\n\n", strcpy(s1, s4));

	printf("***mystrcpy***\n");
	printf("%s\n", MyStrCpy(b1, b2));
	printf("%s\n", MyStrCpy(b1, b3));
	printf("%s\n\n", MyStrCpy(b1, b4));
	
	/*test strncpy*/
	
	printf("***strncpy***\n");
	printf("%s\n", strncpy(s1, s2, 2));
	printf("%s\n", strncpy(s1, s3, 0));
	printf("%s\n\n", strncpy(s4, s4, 1));

	printf("***mystrncpy***\n");
	printf("%s\n", MyStrNCpy(s1, s2, 2));
	printf("%s\n", MyStrNCpy(s1, s3, 0));
	printf("%s\n\n", MyStrNCpy(s4, s4, 1));

    /*test strchr*/
    printf("***strchr***\n");
	printf("%s\n", strchr(b1, 'a'));

	printf("***mystrchr***\n");
	printf("%s\n", MyStrChr("abocd", 'o'));

	
	/*test strdup*/
	printf("***strdup***");
	printf("%s", strdup(s1));
	
	return 0;
}
