
/******WS3 - Environment********/



#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "Env.h"

#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

void PrintEnv(const char **env)
{ 
    while (NULL != *env)
    {
        printf("\n%s", *env); 
        ++*env;
    } 
} 


size_t EnvpLines(char **envp)
{
	int count = 0;
	char **runner = envp;
	
	while (NULL != *runner)
	{
		++runner;
		++count;
	}
	return count;
}


char **CpyEnv(char **envp)

{
	
	int count = 0, i = 0, temp = 0;
	char **runner, **envp_cpy = NULL;
	runner = envp;
	

	count = EnvpLines(**envp);
	
	envp_cpy = (char**) calloc (sizeof(char *) * count);
	
	while (i < count)
	{ 
		tmp = strlen(*runner);
		*envp_cpy = (char*) calloc (sizeof(char) * tmp);
		strcpy(*envp_cpy, *runner);
		++*runner;
		++i;
	}
		
}
		

	
	
	
	
