/**************Logger****************
 *			Shye Shapira			*
 *			Reviewr: Ben			*
 ************************************/

#include <stdio.h>
#include <assert.h> /*assert*/
#include <string.h> /*strcmp, strncmp*/
#include "Logger.h"

/***Append a string to the beggining of a file***/
ChecknReturn AppendLine(const char *file, const char *str)
{
	int close = 0;
	FILE *fp = NULL;
	
	assert(NULL != file);
	assert(NULL != str);
	
	fp = fopen(file, "a");
	if (fp == NULL)
	{
		return FAILTOOPEN;
	}
	
	fputs(str, fp);
	fclose(fp);
	close = fclose(fp);
	if (0 != close)
	{
		return FAILTOCLOSE;
	}
	
	return SUCCESS;
}

/***Delete a file***/
ChecknReturn Remove(const char *file, const char *redundent)
{
	int ret = remove(file);
	
	UNUSED(redundent);
	
	if ('\0' == ret)
	{
		return SUCCESS;
	}
	else
	{
		return REMOVEFAIL;
	}
}

/***Print number of lines from a file***/
ChecknReturn CountLines(const char *file, const char *redundent)
{
	char c = '\0';
	int count_line = 0, close = 0;
	FILE *fp = NULL;
	
	assert(NULL != file);
	UNUSED(redundent);
	
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		return FAILTOOPEN;
	}
	
	for (c = getc(fp); c != EOF; c = getc(fp))
	{
		if ('\n' == c)
		{
			++count_line;
		}
	}
	close = fclose(fp);
	if (0 != close)
	{
		return FAILTOCLOSE;
	}
	printf("The number of linse in file %s is: ", file);
	printf("%d\n", count_line);
	
	return SUCCESS;
}

/***Exit the program***/
ChecknReturn Terminate(const char *redundent1, const char *redundent2)
{
	UNUSED(redundent1);
	UNUSED(redundent2);
	return TERMINATE;
}

/***copy an entier file content to another file***/
ChecknReturn CopyFile(const char *file, const char *cpyfile)
{
	 char c = '\0';
	 int close = 0;
	 FILE *oldfile = NULL, *newfile = NULL;
	 	
	 assert(NULL != file);
	 	
	oldfile = fopen(file, "r");
	if (oldfile == NULL)
	{
		return FAILTOOPEN;
	}
	newfile = fopen(cpyfile, "a");
	if (newfile == NULL)
	{
		return FAILTOOPEN;
	}
	
	c = fgetc(oldfile);
	while (c != EOF)
	{
		fputc(c, newfile);
		c = fgetc(oldfile);
	}
	
	close = fclose(newfile);
	if (0 != close)
	{
		return FAILTOCLOSE;
	}
	close = fclose(oldfile);
	{
		return FAILTOCLOSE;
	}
	
	
	return SUCCESS;
}

/***Add a line to the beggining of a line***/
ChecknReturn PrependLine(const char *file, const char *str)
{
	char *cpyfile =  "/tmp/tmpfile.txt";
	FILE *oldfile = NULL, *newfile = NULL;
	int close = 0, rem = 0;
	
	assert(NULL != file);
	assert(NULL != str);
	
	newfile = fopen(cpyfile, "a");
	if (newfile == NULL)
	{
		return FAILTOOPEN;
	}
	oldfile = fopen(file, "r");
	if (oldfile == NULL)
	{
		return FAILTOOPEN;
	}
	
	AppendLine(cpyfile, str + 1);
	CopyFile(file, cpyfile);
	fclose(fopen(file, "w"));
	CopyFile(cpyfile, file);

	close = fclose(newfile);
	if (0 != close)
	{
		return FAILTOCLOSE;
	}
	fclose(oldfile);
	close = fclose(oldfile);
	if (0 != close)
	{
		return FAILTOCLOSE;
	}
	rem = remove(cpyfile);
	if (0 != rem)
	{
		return REMOVEFAIL;
	}
	
	return SUCCESS;
}

/***compare two strings***/
ChecknReturn MyStrCmp(const char *s1, const char *s2)
{
	const char *runner1 = s1, *runner2 = s2;
	
	while (*runner1 == *runner2 && '\0' != *(runner2 + 1))
	{
	    ++runner1;
	    ++runner2;
	}
	if (0 == *runner1-*runner2)
	{
		return SUCCESS;
	}
	else
	{
		return NOMATCH;
	}
}

/***compaire first character of a string to '<'***/
ChecknReturn MyCharCmp(const char *str, const char *redundent)
{
	const char *c = "<";
	int out = strncmp(str, c, 1);
	
	UNUSED(redundent);

	if (0 == out)
	{
		return SUCCESS;
	}
	else
	{ 
		return NOMATCH;
	}		
}

/***allways return True value***/ 
ChecknReturn AlwaysSuccess(const char *redundent1, const char *redundent2)
{
	UNUSED (redundent1);
	UNUSED (redundent2);
	return SUCCESS;
}

/***Initializing the array of structs**/
match *InitializArr(match *arr)
{
	arr[0].str = "-remove";
	arr[0].op = &Remove;
	arr[0].cmp = &MyStrCmp;
		
	arr[1].str = "-count";
	arr[1].op = &CountLines;
	arr[1].cmp = &MyStrCmp;
		
	arr[2].str = "-exit";
	arr[2].op = &Terminate;
	arr[2].cmp = &MyStrCmp;
		
	arr[3].str = "<";
	arr[3].op = &PrependLine;
	arr[3].cmp = &MyCharCmp;
		
	arr[4].str = "This struct is alwais True";
	arr[4].op = &AppendLine;
	arr[4].cmp = &AlwaysSuccess;	
		
	return arr;
}

/***main body of program***/
void InfraStruct(const char *file, match arr[])
{
	int ret = 0, i = 0;
	char in[MAX_STR_LEN];
	
	
	while (TERMINATE != ret)
	{
		printf("string or op: ");
		fgets(in, MAX_STR_LEN, stdin);
	
		for (i = 0; i < 5; i++)
		{
			if (SUCCESS == arr[i].cmp(in, arr[i].str))
			{
				ret = arr[i].op(file, in);
				break;
			}
		}
	}
}
		


