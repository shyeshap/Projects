/**************ws8*******************
 *			Shye Shapira			*
 *			Reviewr: Ben			*
 ************************************/

#include "struct_arr.h"

#define MAX_ARR 3
#define MAX_INT 11

#define UNUSED(var) (void)(var)

typedef struct element{ 
	void *data;
	void (*print) (void *data);
	int (*add) (void *data, int);
	int (*myfree) (void *ptr);
} element_t;

/* Print functions to stdout for different data-types */

static void PrintInt(void *data)
{
	assert(NULL != data);
	
	printf("%ld\n", (size_t)data); 
}

static void PrintFloat(void *data)
{
	assert(NULL != data);
		
	printf("%f\n", *(float *)&data); 
}

static void PrintStr(void *data)
{
	printf("%s\n", (char *)data);
}

/* increment or concatenate by a given number */

static int AddInt(void *pdata, int n)
{
	assert(NULL != pdata);
	
	*(int *)pdata = *(int *)pdata + n;
	return 0;
}

static int AddFloat(void *pdata, int n)
{
	assert(NULL != pdata);
	
	*(float *)pdata = *(float *)pdata + (float) n;
	return 0;
}

static int AddStr(void *pdata, int n)
{
	char int_to_str[MAX_INT];
	int len = 0;
	
	assert(NULL != pdata);
	
	sprintf(int_to_str, "%d", n);
	len = strlen(int_to_str);
	
	*(char **)pdata = (char *) realloc (*(char **)pdata, strlen (*(char **)pdata) + len + 1);
	if(pdata == NULL)
	{
		fprintf(stderr , "Error line: %d", __LINE__);
		
		return 1;
	}
	
	strcat(*(char **)pdata, int_to_str);
	
	return 0;
}


/* free functions */

static int FreeStr(void *data)
{
	assert(NULL != data);
	
	free(data); data = NULL;
	
	return 0;
}

static int FreeDummi(void *data)
{
	UNUSED(data);
	
	return 0;
}

int Infrastruct()
{
	int i = 10, n = 0;
	float f = 3.7;
	char str[] = "abcdef";
	char *copy = NULL;
	element_t struct_arr[MAX_ARR];
	
	copy = (char *) malloc (strlen(str) + 1);
	if (copy == NULL)
	{
		fprintf(stderr , "Error line: %d", __LINE__);
		return 1;
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
	
	return 0;
}




