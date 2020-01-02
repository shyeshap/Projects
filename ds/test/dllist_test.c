/*********************************/
/*    Data Structures            */
/*               */       
/*    Author : Eliya Goldfisher  */
/*    Reviewed By:               */
/*    Date: 8/12/2019            */
/*                               */
/*********************************/

#include <stdio.h> /* printf */

#include "dllist.h"

#define UNUSED(x) (void)(x)
#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define RUN_TEST(test,mssg)\
            if (test)\
            {\
                printf(GREEN "SUCCESS: %s\n",mssg);\
                printf(RESET);\
            }\
            else\
            {\
                printf(RED "FAIL: %s\n",mssg);\
                printf(RESET);\
            }\

int PrintNode(void *data, void *additional) 
{      
    UNUSED(additional);
    
    printf("data: %d\n", *(int*)data);
    
    return 0;
}

int ActionFunc(void *data, void *additional)
{	
	*(int*)data += *(int*)additional;
	
	return 0;
}

int MatchFunc(void *data, void *additional)
{   
    return (*(int*)data == *(int*)additional);
}

static void TestDLlist()
{
    dll_t *dll = NULL;
    dll_t *dll2 = NULL;
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 10;
    int *data = NULL;
    
    iterator_t it;
    iterator_t it2;
    iterator_t it_begin;
    iterator_t it_next;
    iterator_t it_prev;
    
    printf("DLL Test 1:\n");  
    dll = DLLCreate();
    RUN_TEST(1 == DLLIsEmpty(dll), "is empty");    
    RUN_TEST(0 == DLLSize(dll), "size"); 
    it = DLLEnd(dll);
    it = DLLInsert(dll, it, &x1);
    RUN_TEST(1 == DLLSize(dll), "size"); 
    it = DLLInsert(dll, it, &x1);
    RUN_TEST(2 == DLLSize(dll), "size"); 
    it_begin = DLLBegin(dll);
    RUN_TEST(1 == DLLIsSameIter(it_begin, it), "is same");
    it_next = DLLGetNext(it_begin);
    it = DLLInsert(dll, it_next, &x1);
    it_prev = DLLGetPrev(it_next);
    RUN_TEST(1 == DLLIsSameIter(it_prev, it), "is same");

    DLLDestroy(dll);
    
    printf("DLL Test 2:\n");  
    dll = DLLCreate();
    it = DLLEnd(dll);
    it = DLLInsert(dll, it, &x1);
    RUN_TEST(1 == DLLSize(dll), "size"); 
    it = DLLPushBack(dll, &x1);
    RUN_TEST(2 == DLLSize(dll), "size");
    data = DLLGetData(it);
    RUN_TEST(DLLPopBack(dll) == data, "pop + get data");
    RUN_TEST(1 == DLLSize(dll), "size");

    DLLDestroy(dll);

    printf("DLL Test 3:\n");  
    dll = DLLCreate();
    it = DLLPushFront(dll, &x1);
    RUN_TEST(1 == DLLSize(dll), "size");
    data = DLLGetData(it);
    RUN_TEST(DLLPopFront(dll) == data, "pop + get data");
    RUN_TEST(0 == DLLSize(dll), "size");

    DLLDestroy(dll);
    
    printf("DLL Test 4:\n");  
    dll = DLLCreate();
    it_begin = DLLPushBack(dll, &x1);
    it = DLLPushBack(dll, &x1);
    it = DLLPushBack(dll, &x1);
    it = DLLPushBack(dll, &x1);
    RUN_TEST(4 == DLLSize(dll), "size");
    
    dll2 = DLLCreate();
    it2 = DLLPushBack(dll2, &x1);
    it2 = DLLPushBack(dll2, &x1);
    it2 = DLLPushBack(dll2, &x1);
    it2 = DLLGetPrev(it2);
    RUN_TEST(3 == DLLSize(dll2), "size");
    
    DLLSplice(it_begin, it, it2);
    RUN_TEST(6 == DLLSize(dll2), "size");

    DLLDestroy(dll);
    DLLDestroy(dll2);
   
    printf("DLL Test 5:\n");  
    dll = DLLCreate();
    it = DLLPushBack(dll, &x1);
    it = DLLPushBack(dll, &x2);
    it = DLLPushBack(dll, &x3);
    RUN_TEST(3 == DLLSize(dll), "size");
    it_begin = DLLBegin(dll);
    RUN_TEST(0 == DLLForEach(it_begin, it, &PrintNode, &x1), "for each");
    RUN_TEST(0 == DLLForEach(it_begin, it, &ActionFunc, &x4), "for each");
    RUN_TEST(0 == DLLForEach(it_begin, it, &PrintNode, &x1), "for each");
    DLLDestroy(dll);
    
    printf("DLL Test 6:\n");  
    dll = DLLCreate();
    it = DLLPushBack(dll, &x1);
    it = DLLPushBack(dll, &x1);
    it = DLLPushBack(dll, &x1);
    RUN_TEST(3 == DLLSize(dll), "size");
    it_begin = DLLBegin(dll);
    it2 = DLLFind(it_begin, it, &MatchFunc, &x1);
    RUN_TEST(1 == DLLIsSameIter(it_begin, it2), "is same");
    
    DLLDestroy(dll);   
}

int main()
{   
    TestDLlist();
    return 0;
}
