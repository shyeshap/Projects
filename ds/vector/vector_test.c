/*********************************/
/*    Data Structures            */
/*    Vector                     */       
/*    Author :  SHYE             */
/*    Reviewed By: YONATAN       */
/*    Date:     1/12/2019        */
/*                               */
/*********************************/

#include <stdio.h>  /*printf() */
#include <string.h> /* strcmp(), strcpy() */
#include <stdlib.h> /*malloc */

#include "vector.h" /* vector data structure functions */

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
							
struct Vector{
	void *start;
	size_t size;
	size_t capacity;
	size_t element_size;
};

void test()
{
	int x = 1;
	
	vector_t *myvector = VectorCreate(4, 3);
	RUN_TEST(3 == myvector->capacity, "capacity empty array");
	RUN_TEST(0 == myvector->size, "size of empty array");
	RUN_TEST(4 == myvector->element_size, "element size");
	
	VectorPopBack(myvector);
	
	RUN_TEST(0 == VectorPushBack(myvector, &x), "first push");
	RUN_TEST(3 == VectorCapacity(myvector), "capacity of 1 element array");
	RUN_TEST(1 == VectorSize(myvector), "size of 1 element array");
	RUN_TEST(1 == *(int *)VectorGetItemAddress(myvector, 1), "get");
	
	RUN_TEST(0 == VectorPushBack(myvector, &x), "second push");
	RUN_TEST(3 == VectorCapacity(myvector), "capacity of 2 element array");
	RUN_TEST(2 == VectorSize(myvector), "size of 2 element array");
	RUN_TEST(1 == *(int *)VectorGetItemAddress(myvector, 1), "get");
	RUN_TEST(1 == *(int *)VectorGetItemAddress(myvector, 2), "get");
	
	RUN_TEST(0 == VectorPushBack(myvector, &x), "third push");
	RUN_TEST(3 == VectorCapacity(myvector), "capacity of 3 element array");
	RUN_TEST(3 == VectorSize(myvector), "size of 3 element array");
	
	RUN_TEST(0 == VectorPushBack(myvector, &x), "fourth push");
	RUN_TEST(6 == VectorCapacity(myvector), "capacity of 4 element array");
	RUN_TEST(4 == VectorSize(myvector), "size of 4 element array");
	
	VectorPopBack(myvector);
	RUN_TEST(6 == VectorCapacity(myvector), "capacity of 3 element after pop");
	RUN_TEST(3 == VectorSize(myvector), "size of 3 elements after pop");
	
	VectorPopBack(myvector);
	RUN_TEST(6 == VectorCapacity(myvector), "capacity of 2 element after pop");
	RUN_TEST(2 == VectorSize(myvector), "size of 2 element after pop");
	
	VectorPopBack(myvector);
	RUN_TEST(3 == VectorCapacity(myvector), "capacity of 1 element after pop");
	RUN_TEST(1 == VectorSize(myvector), "size of 1 element after pop");
	RUN_TEST(NULL == VectorGetItemAddress(myvector, 2), "get");
	
	VectorPopBack(myvector);
	RUN_TEST(1 == VectorCapacity(myvector), "capacity of 1 element after pop");
	RUN_TEST(0 == VectorSize(myvector), "size of 1 element after pop");
	
	VectorPopBack(myvector);
	
	VectorDestroy(myvector);
	
	myvector = VectorCreate(4, 0);
	
	myvector = VectorCreate(0, 2387654);
}

int main()
{
	test();
	
	return 0;
}
