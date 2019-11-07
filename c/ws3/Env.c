
/******WS3 - Environment********/
/*copy and print environment variables in lowercase*/


#include <stdio.h>
#include <stdlib.h> /*NULL macro*/
#include <string.h> /*strlen*/
#include <ctype.h> /*tolower*/
#include <assert.h> /*assert*/
#include "Env.h"


/*same as strdup*/
char *MyStrDup(const char* s)
{
    int str_size = strlen(s) + 1;
    char *temp = (char*)malloc(sizeof(char) * str_size);
    const char *runner = s;
    
    
    assert(NULL != s);
    assert(NULL != temp);
   
    if(NULL == temp)
    {
        return NULL;
    }
   
    strcpy(temp, runner);
       
    return temp;
   
}

/*countin pointers in an array*/
size_t EnvpLines(const char **envp)
{
	int count = 0;
	const char **runner;
	runner = envp;
	
	assert (NULL != envp);
	
	while (NULL != *runner)
	{
		++runner;
		++count;
	}
	return count;
}

/*turn strings to lowercase*/
void ToLower(char *str)
{ 
	char *runner = str;
	
	assert (NULL != str);
	
	while('\0' != *runner)
	{
		*runner = tolower(*runner);
		++runner;
	}
}

/*print out strings*/
void PrintEnv(char **env)
{ 

	assert (NULL != env);
	
    while (NULL != *env)
    {
        printf("%s\n", *env); 
        ++env;
    } 
}
 
/*free allocated memoryarrays*/
void CleanEnvCopy(char **envp_cpy)
{
	int i = 0;
	
	assert (NULL != envp_cpy);
	
	while (*(envp_cpy + i))
	{
		free(*(envp_cpy +i));
		*(envp_cpy + i) = NULL;
		++i;
	}
	free (envp_cpy);
	envp_cpy = NULL;		
}

/*copy and print environment variables in lowercase*/
char **CpyEnv(const char **envp)

{
	
	int count = 0, i = 0;
	const char **runner;
	char **envp_cpy = NULL;
	char **head = envp_cpy;
	runner = envp;
	count = EnvpLines(envp);
	envp_cpy = (char**) calloc (count, sizeof(char *));
	head = envp_cpy;
	
	assert (NULL != envp_cpy);
	
	while (i < count)
	{ 
		*envp_cpy = MyStrDup(*runner);
		ToLower(*envp_cpy);
		++runner;
		++envp_cpy;
		++i;
	}
	PrintEnv(head);
	
	CleanEnvCopy(head);
	
	return head;
	
}

	
	
	
	
