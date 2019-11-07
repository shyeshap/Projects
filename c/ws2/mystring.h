/* Worksheet2 - Exercise
	string.h */

#ifndef _mystring_h
#define _mystring_h

#include <stdio.h>
#include <stddef.h>


 size_t MyStrLen(const char *s);
 
 int MyStrCmp(const char *s1, const char *s2);
 
 char *MyStrCpy(char *dest, const char *src);
 
 char *MyStrNCpy(char *dest, const char *src, size_t n);
 
 int MyStrCaseCmp(const char *s1, const char *s2);
 
 char *MyStrChr(const char *s, int c);
 
 char *MyStrDup(const char *s);

 char *MyStrCat(char *dest, const char *src);
 
char *MyStrNCat(char *dest, const char *src, int n);

#endif
