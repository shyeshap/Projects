/* Worksheet2 - Exercise
	string.h */
#include <stdio.h>

#ifndef _mystring_h
#define _mystring_h


 size_t mystrLen(const char *s);
 int MyStrCmp(const char *s1, const char *s2);
 char *MyStrCpy(char *dest, const char *src);
 char *mystrncpy(char *dest, const char *src, size_t n);
 int mystrcasecmp(const char *s1, const char *s2);
 char *mystrchr(const char *s, int c);




#endif
