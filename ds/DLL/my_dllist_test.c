#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */
#include <stdio.h> /* printf() */

#include "dllist.h" /* doubly linked list */

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);
						   
#include "dllist.h"

struct Iterator
{
	struct DLLNode *node;
};

void test()
{
	int a = 1, b = 2, c = 3;
	
	iterator_t it;
	dll_t *manage = DLLCreate();
	TEST(0 == DLLSize(manage), "size of empty list");
	TEST(1 == DLLIsEmpty(manage), "is empty");
	it = DLLBegin(manage);
	it = DLLInsert(manage, it, &a);
	TEST(1 == DLLSize(manage), "size: 1 element");
	TEST(0 == DLLIsEmpty(manage), "is not empty");
	TEST(1 == *(int *)GetData(it), "get data 1");
	it = DLLPushBack(manage, &b);
	TEST(2 == DLLSize(manage), "size: 2 element");
	TEST(2 == *(int *)GetData(it), "get data 2");
	
	DLLDestroy(manage);
}

int main()
{
	test();
	
	return 0;
}
