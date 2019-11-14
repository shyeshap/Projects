/**************Logger****************
 *			Shye Shapira			*
 *			Reviewr: Ben			*
 ************************************/

#ifndef _Logger_h
#define _Logger_h

#include <stddef.h>

#define MAX_STR_LEN 1000 /*cant receiv longer strings*/
#define MAX_FILE_LEN 100 /*maximum length of file name*/
#define ELEMEN_NUM 5 /*elements of array*/
#define UNUSED(var) (void)(var)

typedef enum ChecknReturn
{
	SUCCESS, 
	FAILTOOPEN,  
	NOMATCH,
	REMOVEFAIL,
	FAILTOCLOSE,
	TERMINATE
} ChecknReturn;

typedef struct match
{
		char *str;
		ChecknReturn (*op) (const char *file, const char *str);
		ChecknReturn (*cmp) (const char *s1, const char *s2);
} match;

void InfraStruct(const char *file, match *arr);

match *InitializArr(match *arr);

ChecknReturn CountLines(const char *file, const char *redundent);

#endif
