/*********************************/
/*                               */
/*    Work Sheet 9               */       
/*    Author: 	Shye Shapira	 */
/*    Reviewer: 		         */
/*    Date:   	23/11/2019       */
/*                               */
/*********************************/

#include <stdio.h> /* printf(), size_t */
#include <string.h> /* strlen() */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "mem.h"

#define WORD_SIZE sizeof(size_t)
#define ASCII_CHARS 127

/*** EX1 ***/
static size_t SetWord(int x)
{
	size_t word = (size_t) x;
	int shift = WORD_SIZE;
	
	while (WORD_SIZE * 4 >= (unsigned) shift)
	{
		word |= word << shift;
		shift *= 2;
	}
	
	return word;
}

void *MyMemset(void *ptr, int x, size_t n)
{
	char *runner = NULL;
	size_t word = 0;
	
	assert (NULL != ptr);
	
	runner = (char *)ptr;
	
	while ((0 != ((size_t)runner % WORD_SIZE)) && (0 < n)) /* If not aligned */
	{
		*runner = (char)x;
		--n;
		++runner;
	}
	
	word = SetWord(x); 
	
	while (WORD_SIZE <= n) /* Set in chunks */
	{
		*(size_t *)runner = word;
		runner += WORD_SIZE;
		n -= WORD_SIZE;
	}
	
	while (0 < n) /* remaning chars */
	{
		*runner = (char)x;
		--n;
		++runner;
	}
	
	return ptr;	
}

void *MyMemcpy(void *dst, const void *src, size_t n)
{
	char *runner_dst = NULL, *runner_src = NULL;
	size_t *lsrc = (size_t *)src, *ldst = (size_t *)dst;
	
	assert(NULL != dst);
	assert(NULL != src);
	
	runner_dst = (char *)dst;
	runner_src = (char *)src;
	
	while ((0 != ((size_t)runner_dst % WORD_SIZE)) && (0 < n)) /* If not aligned */
	{
		*runner_dst = *runner_src;
		++runner_dst;
		++runner_src;
		--n;
	}
	
	lsrc = (size_t *)runner_src;
	ldst = (size_t *)runner_dst;
	
	while (WORD_SIZE <= n) /* copy chunks */
	{
		*ldst = *lsrc;
		++ldst;
		++lsrc;
		n -= WORD_SIZE;
	}
	
	runner_dst = (char *)ldst;
	runner_src = (char *)lsrc;
	
	while (0 < n) /* Leftovers */
	{
		*runner_dst = *runner_src; 
		++runner_dst;
		++runner_src;
		--n;
	}	
	
	*runner_dst = '\0';
	
	return dst;
}
	
void *MyMemmove(void *dst, const void *src, size_t num)
{
	char *end_src = NULL, *end_dst = NULL;
	
	assert(NULL != dst);
	assert(NULL != src);
	
	end_src = (char *)src + num;
	end_dst = (char *)dst + num;
	
	if (((size_t)dst > (size_t)src) && ((size_t)dst < (size_t)src + num))
	{
		while (0 < num)
		{
			--end_dst;
			--end_src;
			*end_dst = *end_src;
			--num;
		}
	}
	else
	{
		MyMemcpy(dst, src, num);
	}

	return dst;
}

/*** EX2 ***/
static char *ReverseStr(char *str)
{
	char tmp = 0, *src = NULL, *dst = NULL;
	size_t len = 0;
	
	assert(NULL != str);
	
	len = strlen(str);
	src = str;
	dst = src + len - 1;
	
	while (src < dst)
	{
		tmp = *src;
		*src = *dst;
		++src;
		*dst = tmp;
		--dst;
	}
	
	return str;
}

char *ItoAby10(int num, char *str)
{
	int signe = 0;
	char *head = NULL;
	
	assert(NULL != str);
	
	head = str;
	
	if (num < 0)
	{
		signe = num;
		num = -num;
	}
	
	do
	{
		*str = num % 10 + '0';
		++str;
		num /= 10;
	} while (num > 0);
	
	if (signe < 0)
	{
		*str = '-';
		++str;
	}
	
	*str = '\0';
	ReverseStr(head);
	
	return head;
}

char *ItoAAnyBase(int num, char *str, int base)
{
	int signe = 0, rem = 0;
	char *head = NULL;
	
	assert(NULL != str);
	
	head =  str;
	
	if ((num < 0) && (10 == base))
	{
		signe = num;
		num = -num;
	}
	
	do 
	{
		rem = num % base;
		*str = (rem > 9) ? (rem-10) + 'A' : rem + '0';
		++str;
		num /= base;
	} while (num > 0);
	
	if (signe < 0)
	{
		*str = '-';
		++str;
	}
	
	*str = '\0';
	ReverseStr(head);
	
	return head;
}

int AtoIby10(const char *nptr)
{
	const char *runner = NULL;
	int ret = 0;
	unsigned int len = 0, times = 1;
	
	assert(NULL != nptr);
	
	runner = nptr;
	len = strlen(nptr);
	
	runner += len - 1;
	
	if ('-' == *nptr)
	{
		--len;
	}
	
	while (0 < len)
	{
		ret += (*runner - '0') * times;
		times *= 10;
		--runner;
		--len;		
	}
	
	if ('-' == *nptr)
	{
		ret *= -1;
	}
	
	return ret;
}

static long power(int base, int exp)
{
	long lbase = (long)base, pow = 1;
	
	if (0 == exp)
	{
		return 1;
	}
	
	while (0 < exp)
	{
		lbase *= pow;
		pow = (long)base;
		--exp;
	}
	
	return lbase;
}

/* atoi by any base */
int AtoIAnyBase(const char *nptr, int base)
{
	const char *runner = NULL;
	int ret = 0;
	unsigned int len = strlen(nptr), exp = 0;
	
	assert(NULL != nptr);
	assert((37 > base) && (0 < base));
	
	runner = nptr;
	runner += len - 1;
	
	if ('-' == *nptr && 10 == base)
	{
		--len;
	}
	
	while (0 < len)
	{
		ret += power(base, exp) * ((*runner > 57) ? (*runner - 'A' + 10) : (*runner - '0'));
		++exp;
		--runner;
		--len;		
	}
	
	if ('-' == *nptr)
	{
		ret *= -1;
	}
	
	return ret;
}

/*** EX3 ***/
static ascii_t *SetArr(ascii_t arr[])
{
	int i = 0;
	for (i = 0; i < 127; ++i)
	{
		arr[i].c = i;
		arr[i].status = 0;
	}
	
	return arr;
}

void CmpThreeArr(char *arr1, int len1, char *arr2, int len2, char *arr3, int len3)
{
	ascii_t *arr = NULL;
	int i = 0;
	
	assert(NULL != arr1);
	assert(NULL != arr2);
	assert(NULL != arr3);
		
	arr = (ascii_t *) malloc (ASCII_CHARS * sizeof(ascii_t));
	SetArr(arr);
	
	for (i = 0; i < len1; ++i)
	{
		arr[(int)arr1[i]].status = 1;
	}
	for (i = 0; i < len2; ++i)
	{
		if (arr[(int)arr2[i]].status == 1)
		{
			arr[(int)arr2[i]].status = 2;
		}
	}
	for (i = 0; i < len3; ++i)
	{
		if (arr[(int)arr3[i]].status == 2)
		{
			arr[(int)arr3[i]].status = 0;
		}
	}
	
	for (i = 0; i < ASCII_CHARS; ++i)
	{
		if ((int)arr[i].status == 2)
		{
			printf ("%c ", arr[i].c);
		}
	}
	printf("\n");
	
	free (arr); arr = NULL;
}

/*** EX4 ***/
int IsLittleEndian() 
{
	size_t checkend = 1;
	size_t *ptr = &checkend;
	
	return (*(char *)ptr == 1);
}


