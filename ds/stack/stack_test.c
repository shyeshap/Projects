#include <stdio.h>  /*printf() */
#include <string.h> /* strcmp(), strcpy() */
#include <stdlib.h> /*malloc */

#include "stack.h" /* stack ds functions */

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

#define M1   0x5555555555555555UL
#define M8   0x00FF00FF00FF00FFUL


#define BITS_IN_WORD 64

#define RUN_TEST(test, msg)	if(test)					 	\
							{								\
								printf(GRN "[OK]\n" RESET);	\
							}								\
							else							\
							{								\
								printf(RED "%s\n", msg);	\
							}
							
struct Stack
{
	void *start;
	void *current;
	void *end;
	size_t element_size;
};

void TestCreate()
{
	stack_t *mystack;
	int x = 10, y = 5;
	char c[] = "abcd";
	float f = 5.5;
	long int l = 32545, i = 0, sum = 0;
	
	mystack = StackCreate(4, 8);
	RUN_TEST((mystack->element_size) == 4, "create 1");
	RUN_TEST(StackIsEmpty(mystack) == 1, "stack empty");
	RUN_TEST(StackSize(mystack) == 0, "stack size 0");
	RUN_TEST(StackPush(mystack, &x), "push x");
	RUN_TEST(*(int *)StackPeek(mystack) == x, "peek x");
	RUN_TEST(StackSize(mystack) == 1, "stack size 1");
	RUN_TEST(StackPush(mystack, &y), "push y");
	RUN_TEST(*(int *)StackPeek(mystack) == y, "peeck x");
	RUN_TEST(StackSize(mystack) == 2, "stack size 2");
	RUN_TEST(StackPush(mystack, &f), "push y");
	RUN_TEST(*(float *)StackPeek(mystack) == f, "peeck x");
	RUN_TEST(StackSize(mystack) == 3, "stack size 3");
	StackPop(mystack);
	RUN_TEST(StackIsEmpty(mystack) == 0, "stack empty");
	RUN_TEST(StackSize(mystack) == 2, "stack size 3");
	StackDestroy(mystack);
	
	printf("\n");
	
	mystack = StackCreate(8, 10);
	RUN_TEST(StackIsEmpty(mystack) == 1, "stack empty");
	while(i < 10)
	{
		printf("%ld\n", i);
		RUN_TEST(StackSize(mystack) == (size_t)i, "stack size 2");
		sum = l + i;
		RUN_TEST(StackPush(mystack, &sum), "push sum");
		RUN_TEST(*(long int *)StackPeek(mystack) == sum, "peeck x");
		i++;
	}
	RUN_TEST(StackIsEmpty(mystack) == 0, "stack empty");
	
	RUN_TEST(StackPush(mystack, &sum) == 0, "push sum");
	
	StackDestroy(mystack);
}

void TestSortRec()
{
	stack_t *stack;
	int n1 = 10, n2 = 5, n3 = 7;
	
	stack = StackCreate(4, 8);
	StackPush(stack, &n1);
	StackPush(stack, &n2);
	StackPush(stack, &n3);
	
	StackSortRec(stack);
	
	while (!StackIsEmpty(stack))
	{
		printf("%d\n", *(int *)StackPop(stack));
	}
}

int main()
{
	TestCreate();
	TestSortRec();
	
	return 0;
}
