#include "linked_list.h" /* linked list API */
#include "recursion.h"

size_t ItrFib(size_t num)
{
	size_t first = 1, second = 1, i = 0, n = 1;
	 
	if (0 == num)
	{
		return 0;	
	}
	
	for (i = 2; i < num; ++i)
	{
		n = first + second;
		first = second;
		second = n; 
	}
	
	return n;
}

size_t RecFib(size_t num)
{
	if (num <= 1)
	{
		return num;
	}
	
	return RecFib(num - 1) + RecFib(num - 2);
}

size_t RecStrlen(const char *str)
{
	if ('\0' == *str)
	{
		return 0;
	}
	
	return (RecStrlen((char *)str + 1) + 1);
}

int RecStrcmp(const char *s1, const char *s2)
{
	if (*s1 != *s2 || '\0' == *s1 || '\0' == *s2)
	{
		return *s1 - *s2;
	}
	
	return RecStrcmp(s1 + 1, s2 + 1);
}

char *RecStrcpy(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = *src;
		
		return dest;
	}
	
	RecStrcpy(dest + 1, src + 1);
	
	*dest = *src;
	
	return dest;
}

char *RecStrcat(char *dest, const char *src)
{
	
	if (*dest != '\0')
	{
		RecStrcat(dest + 1, src);
	}
	
	else if((*dest = *src) != '\0')
	{	

		RecStrcat(dest + 1, src + 1);
	}
	
	return dest;
}



