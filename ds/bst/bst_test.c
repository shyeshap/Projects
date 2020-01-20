#include <stdio.h> /* printf() */

#include "bst.h" /* bst API */

#define UNUSED(param) (void)param;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define BLUE "\n\x1b[34m"
#define RESET "\033[0m\n"

#define TEST(test, Msg) if (test)\
						   {\
						      printf(GREEN "%s - %s" RESET, "SUCCESS", Msg);\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf(RED "%s, %s\n" RESET, "FAILURE", Msg);\
						   }\
						   printf(WHITE);		   
						   
int Compare(const void *data1, const void *data2, void *param)
{
	UNUSED(param);
	
	return *(int *)data1 > *(int *)data2;
}

static int AddNum(void *node_data, void *num)
{
    *(int *)node_data += *(int *)num;
    
    return 0;
}

static int PrintTree(void *node_data, void *param)
{
    UNUSED(param);
    
    printf("%d\n", *(int *)node_data);
    
    return 0;
}

void TestCreate()
{
	bst_t *tree = BSTCreate(&Compare, NULL);
	
	printf(BLUE "CREATE\n" RESET);
		
	TEST(BSTIsEmpty(tree), "create 1");
	TEST(BSTIsSameItr(BSTBegin(tree), BSTEnd(tree)), "create 2");
	
	BSTDestroy(tree); tree = NULL;
	
}

void TestInsert()
{
	bst_t *tree = BSTCreate(&Compare, NULL);
	int d1 = 10, d2 = 20, d3 = 5;
	bst_itr_t itr = NULL;
	
	printf(BLUE "INSERT\n" RESET);
	
	TEST(!BSTInsert(tree, &d1), "insert d1");
	itr = BSTBegin(tree);
	TEST(&d1 == BSTGetData(itr), "insert - get data");
	
	TEST(!BSTInsert(tree, &d2), "insert d2");
	itr = BSTEnd(tree);
	TEST(!BSTInsert(tree, &d3), "insert d3");
	itr = BSTBegin(tree);
	TEST(&d3 == BSTGetData(itr), "insert - begin");

	BSTDestroy(tree); tree = NULL;
}

void TestNextPrev()
{
	bst_t *tree = BSTCreate(&Compare, NULL);
	int d1 = 10, d2 = 20, d3 = 33, d4 = 6, d5 = 9, d6 = 12;
	bst_itr_t itr = NULL;
	
	printf(BLUE "NEXT & PREV\n" RESET);
	
	TEST(!BSTInsert(tree, &d1), "insert d1");
	itr = BSTBegin(tree);
	TEST(!BSTInsert(tree, &d2), "insert d2");
	itr = BSTNext(itr); 
	TEST(&d2 == BSTGetData(itr), "next 1");
	TEST(!BSTInsert(tree, &d3), "insert d3");
	itr = BSTNext(itr);
	TEST(&d3 == BSTGetData(itr), "next 2");
	TEST(!BSTInsert(tree, &d4), "insert d4");
	TEST(!BSTInsert(tree, &d5), "insert d5");
	TEST(!BSTInsert(tree, &d6), "insert d6");
	itr = BSTEnd(tree);
	itr = BSTPrev(itr);
	TEST(&d3 == BSTGetData(itr), "prev 1");
	itr = BSTPrev(itr);
	TEST(&d2 == BSTGetData(itr), "prev 2");
	itr = BSTPrev(itr);
	TEST(&d6 == BSTGetData(itr), "prev 3");
	itr = BSTPrev(itr);
	TEST(&d1 == BSTGetData(itr), "prev 4");
	itr = BSTPrev(itr);
	TEST(&d5 == BSTGetData(itr), "prev 5");
	itr = BSTPrev(itr);
	TEST(&d4 == BSTGetData(itr), "prev 6");
	itr = BSTPrev(itr);
	TEST(BSTEnd(tree) == itr, "final prev");
	
	BSTDestroy(tree); tree = NULL;
}

void TestRemove()
{
	bst_t *tree = BSTCreate(&Compare, NULL);
	int d1 = 100, d2 = 50, d3 = 200, d4 =150, d5 = 300, d6 = 10, d7 =20, d8 =0 , d9 =30, d10 = 17;
	bst_itr_t itr = NULL;
	
	printf(BLUE "REMOVE\n" RESET);
	
	TEST(BSTSize(tree) == 0, "size 0");
	TEST(!BSTInsert(tree, &d1), "insert d1");
	TEST(BSTSize(tree) == 1, "size 1");
	TEST(!BSTInsert(tree, &d2), "insert d2");
	TEST(BSTSize(tree) == 2, "size 2");
	TEST(!BSTInsert(tree, &d3), "insert d3");
	TEST(BSTSize(tree) == 3, "size 3");
	TEST(!BSTInsert(tree, &d4), "insert d4");
	TEST(BSTSize(tree) == 4, "size 4");
	TEST(!BSTInsert(tree, &d5), "insert d5");
	TEST(BSTSize(tree) == 5, "size 5");
	TEST(!BSTInsert(tree, &d6), "insert d6");
	TEST(BSTSize(tree) == 6, "size 6");
	TEST(!BSTInsert(tree, &d7), "insert d7");
	TEST(BSTSize(tree) == 7, "size 7");
	TEST(!BSTInsert(tree, &d8), "insert d8");
	TEST(BSTSize(tree) == 8, "size 8");
	TEST(!BSTInsert(tree, &d9), "insert d9");
	TEST(BSTSize(tree) == 9, "size 9");
	TEST(!BSTInsert(tree, &d10), "insert d10");
	TEST(BSTSize(tree) == 10, "size 10\n");
	
	itr = BSTBegin(tree);
	TEST(&d8 == BSTGetData(itr), "remove 0 - no child");
	BSTRemove(itr);
	TEST(BSTSize(tree) == 9, "size 9");
	itr = BSTNext(BSTBegin(tree));
	TEST(&d10 == BSTGetData(itr), "remove 17 - no child");
	BSTRemove(itr);
	TEST(BSTSize(tree) == 8, "size 8");
	itr = BSTBegin(tree);
	TEST(&d6 == BSTGetData(itr), "remove 10 - right child only");
	BSTRemove(itr);
	TEST(BSTSize(tree) == 7, "size 7");
	printf("%d\n", *(int *)BSTGetData(BSTBegin(tree)));
	itr = BSTNext(BSTNext(BSTBegin(tree)));
	printf("%d\n", *(int *)BSTGetData(itr));
	TEST(&d2 == BSTGetData(itr), "remove 50 - left child only");
	BSTRemove(itr);
	TEST(BSTSize(tree) == 6, "size 6");
	
	printf("%d\n", *(int *)BSTGetData(BSTBegin(tree)));
	itr = BSTNext(BSTNext(BSTBegin(tree)));
	printf("%d\n", *(int *)BSTGetData(itr));
	TEST(&d1 == BSTGetData(itr), "remove root - 2 children");
	BSTRemove(itr);
	TEST(BSTSize(tree) == 5, "size 5");
	printf("%lu\n", BSTSize(tree));
	
	BSTDestroy(tree); tree = NULL;
}

static void TestFind()
{
    bst_t *tree = BSTCreate(&Compare, NULL);
    int x1 = 1, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    bst_itr_t it1 = NULL;
    
    printf("\nFind:\n");
    TEST(0 == BSTSize(tree), "size 0");
    TEST(1 == BSTIsEmpty(tree), "empty");
    
    TEST(0 == BSTInsert(tree, &x4), "insert 4");
    TEST(0 == BSTInsert(tree, &x1), "insert 1");
    TEST(0 == BSTInsert(tree, &x6), "insert 6");
    TEST(0 == BSTInsert(tree, &x5), "insert 5");
    TEST(0 == BSTInsert(tree, &x7), "insert 7");
    
    TEST(5 == BSTSize(tree), "size 5");
    
    it1 = BSTFind(tree, &x3);
    
    TEST(1 == BSTIsSameItr(it1, BSTEnd(tree)), "didnt find");
    
    it1 = BSTFind(tree, &x5);
    
    TEST(5 == *(int *)BSTGetData(it1), "find");
    
    printf("Before Add Number:\n");

    TEST(0 == BSTForEach(BSTBegin(tree), BSTEnd(tree), &PrintTree, NULL), "print origin");
    
    TEST(0 == BSTForEach(BSTBegin(tree), BSTEnd(tree), &AddNum, &x3), "add 3");

    printf("After Add Number:\n");
    
    TEST(0 == BSTForEach(BSTBegin(tree), BSTEnd(tree), &PrintTree, NULL), "print change");

    BSTDestroy(tree); tree = NULL; 
}

int main()
{
	TestCreate();
	TestInsert();
	TestNextPrev();
	TestRemove();
	TestFind();
	
	return 0;
}
