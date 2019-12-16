#include <stdio.h> /* printf */

#include "priorityqueue.h"

#define UNUSED(x) (void)(x)

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define TEST(test,mssg)\
            if (test)\
            {\
                printf(GREEN "SUCCESS: %s\n",mssg);\
                printf(RESET);\
            }\
            else\
            {\
                printf(RED "FAIL: %s\n",mssg);\
                printf(RESET);\
            }

int compaire(void *data1, void *data2, void *ap)
{
	return *(int *)data2 - *(int *)data1;
}

void test()
{
	int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
	
	pq_t *pq = PQCreate(&compaire, &i1);
	TEST(0 == PQSize(pq), "empty pq");
	TEST(1 == PQIsEmpty(pq), "is empty");
	
	printf("\nENQUEUE\n");
	TEST(0 == PQEnqueue(pq, &i4), "first enqueue");
}
int main()
{
	test();
	
	return 0;
}
