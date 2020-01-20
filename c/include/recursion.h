#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>

size_t ItrFib(size_t num);
size_t RecFib(size_t num);
size_t RecStrlen(const char *str);
int RecStrcmp(const char *s1, const char *s2);
char *RecStrcpy(char *dest, const char *src);
char *RecStrcat(char *dest, const char *src);

#endif
