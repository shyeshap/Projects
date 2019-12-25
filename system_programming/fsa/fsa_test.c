#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#include "fsa.h"

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"

#define TEST(test, errmsg)\
							{\
								if(test)\
								{\
									printf(GREEN "SUCCESS\n" RESET);\
								}\
								else\
								{\
									printf(RED);\
									printf("%s \n", errmsg);\
									printf(RESET);\
								}\
							}

void TestFSASuggestSize()
{
	printf("\nSUGGESTED SIZE \n");
	TEST(88 == FSASuggestSize(4, 8), "aligned suggested");
	printf("%lu\n", FSASuggestSize(4, 8)); 
	TEST(88 == FSASuggestSize(4, 7), "unaligned suggested");
	printf("%lu\n", FSASuggestSize(4, 7));
}

void TestInit()
{
	fsa_t *fsa = (fsa_t *)malloc(88);
	fsa = FSAInit(fsa, 88, 7);
	
	printf("\n INIT \n");
		
	TEST(4 == FSACountFree(fsa), "4 free");
	free(fsa);
}

void TestAlloc()
{
	fsa_t *fsa = (fsa_t *)malloc(95);
	fsa = FSAInit(fsa, 88, 7);

	printf("\n ALLOC \n");

	TEST(((size_t)((char *)fsa + 32)) == (size_t)FSAAlloc(fsa), "first alloc");
	TEST(3 == FSACountFree(fsa), "3 free");
	TEST(((size_t)((char *)fsa + 48)) == (size_t)FSAAlloc(fsa), "second alloc");
	TEST(2 == FSACountFree(fsa), "2 free");
	TEST(((size_t)((char *)fsa + 64)) == (size_t)FSAAlloc(fsa), "third alloc");
	TEST(1 == FSACountFree(fsa), "1 free");

	free(fsa);
}

void TestFree()
{
	void *al1 = NULL, *al2 = NULL, *al3 = NULL;
	fsa_t *fsa = (fsa_t *)malloc(88);

	printf("\n FREE \n");
	
	fsa = FSAInit(fsa, 88, 7);
	al1 = FSAAlloc(fsa);
	al2 = FSAAlloc(fsa);
	al3 = FSAAlloc(fsa);

	TEST(1 == FSACountFree(fsa), "1 free");
	
	FSAFree(al2);
	
	TEST(2 == FSACountFree(fsa), "2 free");
	TEST(((size_t)((char *)fsa + 48)) == (size_t)FSAAlloc(fsa), "first init");
	
	FSAAlloc(fsa);
	
	TEST(0 == FSACountFree(fsa), "1 free");
	
	free(fsa);
}

int main()
{
	TestFSASuggestSize();
	TestInit();
	TestAlloc();
	TestFree();
	
	return 0;
}
