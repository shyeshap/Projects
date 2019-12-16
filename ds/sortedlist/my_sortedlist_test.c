#include <stdio.h> /* printf */

#include "sortedlist.h"

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
                
int IsBefore(const void *data1, const void *data2, void *param)
{
	UNUSED(param);
	
	return *(int *)data1 <= *(int *)data2;
}

void test()
{
	int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
	sll_iterator_t iter1, iter2, iter3;
	sll_t *sll = SortLLCreate(&IsBefore, NULL);
	
	printf("\nTEST INSERT\n");
	TEST(0 == SLLSize(sll), "create - size 0");
	iter1 = SortLLinsert(sll, &i1);
	TEST(1 == SLLSize(sll), "insert - size 1");
	TEST(i1 == *(int *)SLLGetData(iter1), "data i1");
	iter2 = SortLLinsert(sll, &i3);
	TEST(2 == SLLSize(sll), "insert - size 2");
	TEST(i3 == *(int *)SLLGetData(iter2), "data i3");
	iter3 = SortLLinsert(sll, &i2);
	TEST(3 == SLLSize(sll), "insert - size 3");
	TEST(i2 == *(int *)SLLGetData(iter3), "data i3");
	TEST((IsBefore(SLLGetData(SLLPrev(iter3)), SLLGetData(iter3), NULL)), "comp");
	
	iter1 =	SLLBegin(sll);
	iter2 = SLLEnd(sll);
	printf("\nTEST FIND\n");
	iter3 = SLLFind(sll, &i2, iter1, iter2);
	TEST(i2 == *(int *)SLLGetData(iter3), "comp");
	iter1 =	SLLBegin(sll);
	iter2 = SLLEnd(sll);
	iter3 = SLLFind(sll, &i4, iter1, iter2);
	TEST(&i3 == (int *)SLLGetData(iter3), "comp");
	
	SortLLDestroy(sll);
}

int main()
{
	test();
	
	return 0;
}
