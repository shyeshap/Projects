#include <stdio.h> /* printf() */
#include <math.h> /* sqrt() */

#include "search.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define BLUE printf("\x1b[34m")
#define RESET printf("\033[0m")

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


static int comp(const void *element1, const void *element2, const void *param)
{
	return (*(int *)element1 - *(int *)element2);
}

void TestBinary()
{
	int arr[] = {1,2,3,4,5,6,7,8,9};
	int d1 = 5, d2 = 2, d3 = 6, d4 = 9, d5 = 10; 

	TEST(d1 == *(int *)BinarySearch(arr, 4, 9, comp, &d1, NULL), "search 1");
	TEST(d2 == *(int *)BinarySearch(arr, 4, 9, comp, &d2, NULL), "search 2");
	TEST(d3 == *(int *)BinarySearch(arr, 4, 9, comp, &d3, NULL), "search 6");
	TEST(d4 == *(int *)BinarySearch(arr, 4, 9, comp, &d4, NULL), "search 9");
	TEST(NULL == BinarySearch(arr, 4, 9, comp, &d5, NULL), "search 10");

	TEST(d1 == *(int *)JumpSearch(arr, 4, 9, comp, &d1, NULL), "search 1");
	TEST(d2 == *(int *)JumpSearch(arr, 4, 9, comp, &d2, NULL), "search 2");
	TEST(d3 == *(int *)JumpSearch(arr, 4, 9, comp, &d3, NULL), "search 6");
	TEST(d4 == *(int *)JumpSearch(arr, 4, 9, comp, &d4, NULL), "search 9");
	TEST(NULL == JumpSearch(arr, 4, 9, comp, &d5, NULL), "search 10");

}


int main()
{	
	TestBinary();

	return 0;
}
