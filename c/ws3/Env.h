#include <stdio.h>

#ifndef _mystring_h
#define _mystring_h

void PrintEnv(char **env);

size_t EnvpLines(const char **envp);

char **CpyEnv(const char **envp);

void ToLower(char *str);

#endif
