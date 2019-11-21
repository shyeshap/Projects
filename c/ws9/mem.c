#include <stdio.h> /* size_t */

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

#define WORD_SIZE sizeof(size_t)

typedef unsigned char byte_t;

void *MemsetByByte(void *ptr, int x, size_t n)
{
	char *runner = (char *)ptr;
	
	while (0 < n)
	{
		*runner = (char)x;
		--n;
		++runner;
	}
	
	return ptr;
}

size_t SetWord(int x)
{
	size_t x_str = (size_t)*xp;
	int shift = 1;
	
	while (3 >= shift)
	{
		x_str |= (x_str << (WORD_SIZE * shift));
		++shift;
	}
	
	return x_str;
}

void *mymemset(void *ptr, int x, size_t n)
{
	char *runner = (char *)ptr;
	size_t chunk = 0;
	
	MemsetByByte(runner, x, n);
	
	chunk = SetWord(x);
	
	while (WORD_SIZE <= n)
	{
		*(size_t *)runner = chunk;
		runner += WORD_SIZE;
		n -= WORD_SIZE;
	}
	
	MemsetByWord(runner, x, n)
	
	return (char *)ptr;	
}



void test(int cond, const char *msg)
{
	if (cond)
	{
		printf(GRN "SUCCESS\n" RESET);
	}
	else
	{
		printf(RED "FAIL: %s\n" RESET, msg);
	}
}

int main()
{

	char str[] = "hello world 123456789kjsdhfiuhgfdsysdfiydspf";
	test(MemsetByByte(str, 65, 4) == "AAAAAAAA", "Byte 65, 4");
	test(MemsetByWord(str + 4, 90, 16) == "ZZZZ", "Word 90, 4");
	printf("%s\n", str);

	
	return 0;
}
