#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Env.h"


int main(int argc, char **argv, char **envp)
{

	/*PrintEnv(CpyEnv);*/
	/*char **env = "CLUTTER_IM_MODULE=xim"
	PrintEnv(*/
	
	




	
	int count = 54, i = 0, tmp = 0;
	char **runner, **envp_cpy = NULL;
	runner = envp;
	

	
	envp_cpy = (char**) calloc (count, sizeof(char *));
	
	while (i < count)
	{ 
		tmp = strlen(*runner);
		*envp_cpy = (char*) calloc (tmp, sizeof(char));
		strcpy(*envp_cpy, *runner);
		++*runner;
		++i;
	}
		

	
/*	int count = 0;
	char **runner, **envp_cpy = NULL;
	runner = envp;
	
	
	while ('\0' != *runner)
	{
		++count;
		++*runner;
	}
	runner = envp;
	count = 0;
	
	envp_cpy = (char**) malloc (sizeof(char *) * count);
	
	while ('\0' != *runner)
	{ 
		while('\0' != **runner)
		{
			++count;
			++**runner;
		}
		*envp_cpy = (char*) malloc (sizeof(char) * count);
		**envp_cpy = **runner;
		++*runner;
		++*envp_cpy;
		count = 0;
	}
*/
	
	
	return 0;
}



