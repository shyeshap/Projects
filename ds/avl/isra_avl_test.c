
#include "utilities.h" /* TEST */
#include "avl.h"

int CmpData(const void *data1, const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

int AddOne(void *tree_data, void *param)
{
	UNUSED(param);
	
	++*(int *)tree_data;
	
	return 0;
}

int PrintData(void *tree_data, void *param)
{
	UNUSED(param);
	
	printf("%d\n", *(int *)tree_data);
	
	return 0;
}

int AddOne2(void *tree_data, void *param)
{
	UNUSED(param);
	
	if ( 50 < *(int *)tree_data)
	{
		return 1;
	}
	
	++*(int *)tree_data;
	
	return 0;
}

void Test1()
{
	int one = 1, two = 2;
	
	avl_t *tree = AVLCreate(CmpData);
	TEST(AVLSize(tree) == 0, "Size(), empty tree");
	TEST(AVLIsEmpty(tree) == 1, "IsEmpty(), empty tree");
	AVLDestroy(tree);
	
	tree = AVLCreate(CmpData);
	AVLInsert(tree, &one);
	TEST(AVLSize(tree) == 1, "Size(), one item int tree");
	TEST(AVLIsEmpty(tree) == 0, "IsEmpty(), one item int tree");
	TEST(AVLFind(tree, &one) == &one, "Find(), True");
	TEST(AVLFind(tree, &two) == NULL, "Find(), False");
	AVLForeach(tree, AddOne, NULL);
	TEST(one == 2, "Foreach()");
	one = 1;
	AVLRemove(tree, &two);
	TEST(AVLIsEmpty(tree) == 0, "Remove(), item not found");
	AVLRemove(tree, &one);
	TEST(AVLIsEmpty(tree) == 1, "Remove(), item found");
	AVLDestroy(tree);
	printf("\n");
}

void Test2()
{
	int one = 1, two = 2, three = 3;
	
	avl_t *tree = AVLCreate(CmpData);
	AVLInsert(tree, &one);
	AVLInsert(tree, &two);
	AVLInsert(tree, &three);
	TEST(AVLSize(tree) == 3, "Size(), 3 items in tree");
	TEST(AVLFind(tree, &two) == &two, "Find(), 3 items in tree");
	AVLForeach(tree, AddOne, NULL);
	TEST(three == 4, "Foreach()");
	AVLRemove(tree, &two);
	TEST(AVLSize(tree) == 2, "Remove(), 3 items in tree");
	AVLDestroy(tree);
	printf("\n");
}

static void TestInsert(avl_t *tree, int *a)
{
	int i = 0;
	
	for(; i < 10; ++i)
	{
		AVLInsert(tree, &a[i]);
	}
}

static void TestFind(avl_t *tree, int *a)
{
	int i = 0;
	
	for(; i < 10; ++i)
	{
		TEST(AVLFind(tree, &a[i]) == &a[i], "Find(), Test3, False");
	}
}

static void PrintArray(int *a)
{
	int i = 0;
	
	for (; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

static void TestRemove(avl_t *tree, int *a)
{
	int i = 0;
	
	for (; i < 10; ++i)
	{
		AVLRemove(tree, &a[i]);
	}
	printf("\n");
}

void Test3()
{
	int a[10] = {10,20,30,40,50,60,15,35,55,65};
	avl_t *tree = AVLCreate(CmpData);
	int zero = 0;
	/*
	TestInsert(tree, a);
	*/
	AVLInsert(tree, &a[2]);
	AVLInsert(tree, &a[0]);
	AVLInsert(tree, &a[1]);
	AVLInsert(tree, &a[4]);
	AVLInsert(tree, &a[3]);
	AVLInsert(tree, &a[5]);
	AVLInsert(tree, &a[6]);
	AVLInsert(tree, &a[7]);
	AVLInsert(tree, &a[8]);
	AVLInsert(tree, &a[9]);
	
	TEST(AVLSize(tree) == 10, "Size(), Test3");
	TEST(AVLFind(tree, &zero) == NULL, "Find(), Test3, False");
	TestFind(tree, a);
	PrintArray(a);
	AVLForeach(tree, AddOne, NULL);
	PrintArray(a);
	AVLForeach(tree, AddOne2, NULL);
	PrintArray(a);
	TestRemove(tree, a);
	TEST(AVLIsEmpty(tree) == 1, "Remove(), Test3");
	AVLDestroy(tree);
	printf("\n");
}

int main()
{
	Test1();
	Test2();
	Test3();
	
	return 0;
}











