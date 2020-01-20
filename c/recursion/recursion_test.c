#include <stdio.h>
#include <string.h>
#include <time.h> /* time_t, clock() */

#include "recursion.h"

clock_t start_t, end_t;
double total_t;

void TestFib()
{
	size_t fib = 10;
	
	printf("**itr fib**\n");
	start_t = clock();
	printf("%lu\n", ItrFib(fib));
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("total time: %f\n", total_t);
	
	printf("**rec fib**\n");
	start_t = clock();
	printf("%lu\n", RecFib(fib));
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("total time: %f\n", total_t);
}

void TestStrcmp()
{
	char *s1 = "Hi", *s2 = "hi";
	
	printf("strcmp: %d\n", RecStrcmp(s1, s2) == strcmp(s1, s2));
}

void TestStrlen()
{
	char *s = "hello world";
	printf("strlen: %d\n", RecStrlen(s) == strlen(s));
}

void TestStrcpy()
{
	char src[12] = "hello world", dst[12];
	printf("strcpy: %d\n", strcmp(RecStrcpy(dst, src), strcpy(dst, src)) == 0);
}

void TestStrcat()
{
	char src1[6] = "world", dst1[12] = "hello ";
	char src2[6] = "world", dst2[12] = "hello ";	
	
	printf("strcat: %s\n%s\n", RecStrcat(dst1, src1) , strcat(dst2, src2));
}

int main()
{
	TestFib();
	TestStrlen();
	TestStrcmp();
	TestStrcpy();
	TestStrcat();

	return 0;
} 
