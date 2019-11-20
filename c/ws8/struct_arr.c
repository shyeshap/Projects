/**************ws8*******************
 *			Shye Shapira			*
 *			Reviewr: Ben			*
 ************************************/

#include <stdio.h> /* printf, size_t */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen */

#include "struct_arr.h"

#define MAX_ARR 3
#define MAX_INT 11

#define UNUSED(var) (void)(var)


typedef struct element{
	void *data;
	void (*print) (void *data);
	int (*add) (void *data, int);
	int (*myfree) (void *ptr);
} element;

void PrintInt(void *data)
{
	printf("%ld\n", (size_t)data); 
}

void PrintFloat(void *data)
{
	printf("%f\n", *(float *)&data); 
}

void PrintStr(void *data)
{
	printf("%s\n", (char *)data);
}

int AddInt(void *pdata, int n)
{
	*(int *)pdata = *(int *)pdata + n;
	return 0;
}

int AddFloat(void *pdata, int n)
{
	*(float *)pdata = *(float *)pdata + (float) n;
	return 0;
}

int CountDig(int n)
{
	int count = 0;
	while(n != 0)
    {
        n /= 10;
        ++count;
    }
	
	return count;
}

int AddStr(void *pdata, int n)
{
	char int_to_str[MAX_INT];
	int len = 0;
	
	sprintf(int_to_str, "%d", n);
	len = strlen(int_to_str);
	
	*(char **)pdata = (char *) realloc (*(char **)pdata, strlen (*(char **)pdata) + len + 1);
	if(pdata == NULL)
	{
		return 1;
		fprintf(stderr , "Error line: %d", __LINE__);
	}
	
	strcat(*(char **)pdata, int_to_str);
	
	return 0;
}



int FreeDummi(void *data)
{
	UNUSED(data);
	return 0;
}



int FreeStr(void *data)
{
	free(data); data = NULL;
	return 0;
}


int Infrastruct()
{
	int i = 10, n = 0;
	float f = 3.7;
	char str[] = "abcdef";
	char *copy = NULL;
	element struct_arr[MAX_ARR];
	
	copy = (char *) malloc (strlen(str) + 1);
	if (copy == NULL)
	{
		fprintf(stderr , "Error line: %d", __LINE__);
		return 0;
	}
	
	*(float *)&(struct_arr[0].data) = f;
	struct_arr[0].print = PrintFloat;
	struct_arr[0].add = AddFloat;
	struct_arr[0].myfree = FreeDummi;
	
	struct_arr[1].data = (void *)(size_t)i;
	struct_arr[1].print = PrintInt;
	struct_arr[1].add = AddInt;
	struct_arr[1].myfree = FreeDummi;
	
	struct_arr[2].data = (void *)strcpy(copy, str);
	struct_arr[2].print = PrintStr;
	struct_arr[2].add = AddStr;
	struct_arr[2].myfree = FreeStr;
	
	printf("Insert a number: ");
	scanf("%d", &n);
	
	for (i = 0; i < MAX_ARR; ++i)
	{
		printf("\nOld: ");
		struct_arr[i].print(struct_arr[i].data);
		struct_arr[i].add(&struct_arr[i].data, n);
		printf("New: ");
		struct_arr[i].print(struct_arr[i].data);
		struct_arr[i].myfree(struct_arr[i].data);
	}
	
	return 1;
}




