#include <stdio.h> /* printf() */

#include "avl.h" /* bst API */

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
						      printf(RED "%s, %s" RESET, "FAILURE", Msg);\
						   }\
						   printf(WHITE);

int CmpFunc(const void *user_data, const void *tree_data)
{
	return *(int *)user_data - *(int *)tree_data;
}

int PrintData(void *tree_data, void *param)
{
	UNUSED(param);
	
	printf("%d\n", *(int *)tree_data);
	
	return 0;
}
						 
void TestInsert()
{
	int d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5, d6 = 6;
	avl_t *tree = AVLCreate(CmpFunc);
	
	printf(BLUE"TEST INSERT"RESET);
	TEST(1 == AVLIsEmpty(tree), "empty tree");
	TEST(0 == AVLSize(tree), "size = 0");
	TEST(0 == AVLInsert(tree, &d1), "first insert");
	TEST(1 == AVLSize(tree), "size = 1");
	TEST(0 == AVLInsert(tree, &d4), "second insert");
	TEST(2 == AVLSize(tree), "size = 2");
	TEST(0 == AVLInsert(tree, &d6), "third insert");
	TEST(3 == AVLSize(tree), "size = 3");
	TEST(0 == AVLInsert(tree, &d3), "forth insert");
	TEST(4 == AVLSize(tree), "size = 4");
	TEST(0 == AVLIsEmpty(tree), "not empty tree");
	
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");;
	
	AVLDestroy(tree);
}

void TestRemove()
{
	int d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
	avl_t *tree = AVLCreate(CmpFunc);
	
	printf(BLUE"TEST REMOVE"RESET);
	TEST(0 == AVLInsert(tree, &d3), "first insert");
	TEST(0 == AVLInsert(tree, &d5), "second insert");
	TEST(0 == AVLInsert(tree, &d1), "third insert");
	TEST(0 == AVLInsert(tree, &d2), "forth insert");
	TEST(0 == AVLInsert(tree, &d6), "forth insert");
	TEST(0 == AVLInsert(tree, &d4), "forth insert");
	TEST(0 == AVLInsert(tree, &d7), "forth insert");
	TEST(7 == AVLSize(tree), "size = 7");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	printf(BLUE"remove 2"RESET);
	AVLRemove(tree, &d2);
	TEST(6 == AVLSize(tree), "size = 6");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	printf(BLUE"remove 6"RESET);
	AVLRemove(tree, &d6);
	TEST(5 == AVLSize(tree), "size = 5");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	printf(BLUE"remove 5"RESET);
	AVLRemove(tree, &d5);
	TEST(4 == AVLSize(tree), "size = 4");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	printf(BLUE"remove root"RESET);
	AVLRemove(tree, &d3);
	TEST(3 == AVLSize(tree), "size = 3");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	AVLRemove(tree, &d7);
	TEST(2 == AVLSize(tree), "size = 2");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	AVLRemove(tree, &d1);
	TEST(1 == AVLSize(tree), "size = 1");
	TEST(0 == AVLForeach(tree, &PrintData, NULL), "print each");
	AVLRemove(tree, &d4);
	TEST(0 == AVLSize(tree), "size = 0");
	
	AVLDestroy(tree);
}

void TestBalance()
{
	int d1 = 1, d2 = 2, d3 = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
	int d8 = 8, d9 = 9, d10 = 10, d11 = 11;
	avl_t *tree = AVLCreate(CmpFunc);
	
	printf(BLUE"TEST HEIGHT"RESET);
	TEST(-1 == AVLGetHeight(tree), "height = empty");
	TEST(0 == AVLInsert(tree, &d4), "insert 4");
	TEST(0 == AVLGetHeight(tree), "height = 0");
	TEST(0 == AVLInsert(tree, &d1), "insert 1");
	TEST(1 == AVLGetHeight(tree), "height = 1");
	TEST(0 == AVLInsert(tree, &d6), "insert 6");
	TEST(1 == AVLGetHeight(tree), "height = 1");
	TEST(0 == AVLInsert(tree, &d3), "insert 3");
	TEST(2 == AVLGetHeight(tree), "height = 2");
	TEST(0 == AVLInsert(tree, &d5), "insert 5");
	TEST(2 == AVLGetHeight(tree), "height = 2");
	TEST(0 == AVLInsert(tree, &d7), "insert 7");
	TEST(2 == AVLGetHeight(tree), "height = 2");
	TEST(0 == AVLInsert(tree, &d2), "insert 2");
	TEST(2 == AVLGetHeight(tree), "height = 2");
	
	printf(BLUE"TEST BALANCE"RESET);
	TEST(0 == AVLInsert(tree, &d8), "insert 8");
	TEST(3 == AVLGetHeight(tree), "height = 3");
	TEST(0 == AVLInsert(tree, &d9), "insert 9");
	TEST(3 == AVLGetHeight(tree), "height = 3");
	TEST(0 == AVLInsert(tree, &d10), "insert 10");
	TEST(3 == AVLGetHeight(tree), "height = 2");
	TEST(0 == AVLInsert(tree, &d11), "insert 11");
	TEST(3 == AVLGetHeight(tree), "height = 3");
	
	AVLDestroy(tree);
}

int main()
{
	TestInsert();
	TestRemove();
	TestBalance();
		
	return 0;
}
