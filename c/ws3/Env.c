
/******WS3 - Environment********/
/*copy and print environment variables in lowercase*/


#include <stdio.h>
#include <stdlib.h> /*NULL macro*/
#include <string.h> /*strlen*/
#include <ctype.h> /*tolower*/
#include <assert.h> /*assert*/
#include "Env.h"

/*reassurence of allocation*/
void *MyMalloc(size_t size, int fall)
{
	if (0 == fall)
	{
		return NULL;
		printf("ERROR");
	}
	else
	{
		return (void *) malloc (size);
	}
}


char *MyStrCpyToLower(char *dest, const char *src)
{
	char *destination = dest;
	
	assert(NULL != dest && NULL != src); /*WARNING! Can not reciev NULL pointer*/

	while ('\0' != *src)
	{
		*dest = tolower(*src);
		++src;
		++dest;
	}
	
	*dest = '\0';
		
	return destination;
}

/*same as strdup wit tolower*/
char *MyStrDupLower(const char* s)
{
    int str_size = strlen(s) + 1;
    const char *runner = s;
    char *temp = (char*) MyMalloc ((sizeof(char) * str_size), 1); /*insert 0 to 
    								reassure simulate allocation faileure;*/
    assert(NULL != char);/*WARNING! Can not reciev NULL pointer */
    
    if(temp == NULL)
    {
    	return NULL;
    }
    
    assert(NULL != s);
    assert(NULL != temp);
   
    if(NULL == temp)
    {
        return NULL;
    }
   
    MyStrCpyToLower(temp, runner);
       
    return temp;
   
}


/*countin pointers in an array*/
size_t EnvpLines(const char **envp)
{
	int count = 0;
	const char **runner = envp;
	
	assert (NULL != envp); /*WARNING! Can not reciev NULL pointer */
	
	while (NULL != *runner)
	{
		++runner;
		++count;
	}
	return count-1;
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
	
	assert (NULL != envp_cpy); /*WARNING! Can not reciev NULL pointer */
	
	while (*(envp_cpy + i))
	{
		free(*(envp_cpy +i));
		*(envp_cpy + i) = NULL;
		++i;
	}
	free (envp_cpy);
	envp_cpy = NULL;
	printf("Cleanup successful");		
}


/*copy and print environment variables in lowercase*/

void CpyEnv(const char **envp)
{
	
	int count = 0, i = 0;
	const char **runner;
	char **envp_cpy = NULL;
	char **head = envp_cpy;
	runner = envp;
	count = EnvpLines(envp);
	
	envp_cpy = (char**) calloc (count, sizeof(char *));
	if(envp_cpy == NULL)
    {
    	printf("allocation failed");
    }
	head = envp_cpy;
	
	assert (NULL != envp_cpy); /*WARNING! Can not reciev NULL pointer */
	
	while (i < count)
	{ 
		*envp_cpy = MyStrDupLower(*runner);
		if (*envp_cpy == NULL)
		{
			printf("allocation failed\n");
			CleanEnvCopy(head);
			return;
		}
		++runner;
		++envp_cpy;
		++i;
	}
	PrintEnv(head);
	
	CleanEnvCopy(head);
}

	
	
	
	
