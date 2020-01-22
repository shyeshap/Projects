#include <stdio.h> /* printf() */
#include <string.h> /* strcmp() */

#include "dll.h" /*DLL API */
#include "hash.h" /* avl API */
#include "Logger.h"

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

int MatchFunc(void *data, void *additional)
{   
    return (*(int*)data == *(int*)additional);
}

int MatchFuncStr(void *data, void *additional)
{   
    return 0 == strcmp((char *)data, (char *)additional);
}

size_t HashFunc(const void *data)
{
	return *(size_t *)data % 10;
}

size_t HashFuncStr(const void *data)
{
	return (*(size_t *)data - 65) % 570;
}

size_t HashFunc3(const void *data)
{
	return *(size_t *)data % 3;
}

int PrintEach(void *data, void *param)
{
	UNUSED(param);

	printf("%lu\n", *(size_t *)data);

	return 0;
}

int AddtoEach(void *data, void *param)
{
	*(size_t *)data += *(size_t *)param;

	return 0;
}

void TestHashInsert()
{
	hash_t *hash = HashCreate(10, HashFunc, MatchFunc);
	size_t a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
	
	printf(BLUE "INSERT" RESET);
	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(1 == HashSize(hash), "size = 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(2 == HashSize(hash), "size = 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");
	TEST(3 == HashSize(hash), "size = 3");

	HashDestroy(hash);

	printf(BLUE"INSERT MORE"RESET);
	hash = HashCreate(3, HashFunc3, MatchFunc);

	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(1 == HashSize(hash), "size = 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(2 == HashSize(hash), "size = 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");
	TEST(3 == HashSize(hash), "size = 3");

	TEST(0 == HashInsert(hash, &e), "insert 5");
	TEST(4 == HashSize(hash), "size = 4");
	TEST(0 == HashInsert(hash, &g), "insert 7");
	TEST(5 == HashSize(hash), "size = 5");
	TEST(0 == HashInsert(hash, &d), "insert 4");
	TEST(6 == HashSize(hash), "size = 6");
	TEST(0 == HashInsert(hash, &f), "insert 6");
	TEST(7 == HashSize(hash), "size = 7");
	TEST(0 == HashInsert(hash, &d), "insert 4");
	TEST(8 == HashSize(hash), "size = 8");

	HashDestroy(hash);
}

void TestHashRemove()
{
	hash_t *hash = HashCreate(10, HashFunc, MatchFunc);
	size_t a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
	
	printf(BLUE "REMOVE" RESET);
	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(1 == HashSize(hash), "size = 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(2 == HashSize(hash), "size = 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");
	TEST(3 == HashSize(hash), "size = 3");

	HashRemove(hash, &b);
	TEST(2 == HashSize(hash), "remove 2");
	HashRemove(hash, &a);
	TEST(1 == HashSize(hash), "size = 2");
	HashRemove(hash, &c);
	TEST(0 == HashSize(hash), "size = 3");
	TEST(1 == HashIsEmpty(hash), "empty");

	HashDestroy(hash);

	printf(BLUE"MORE REMOVE"RESET);
	hash = HashCreate(3, HashFunc3, MatchFunc);

	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(1 == HashSize(hash), "size = 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(2 == HashSize(hash), "size = 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");
	TEST(3 == HashSize(hash), "size = 3");

	HashRemove(hash, &c);
	TEST(2 == HashSize(hash), "size = 2");

	TEST(0 == HashInsert(hash, &e), "insert 5");
	TEST(3 == HashSize(hash), "size = 3");
	TEST(0 == HashInsert(hash, &g), "insert 7");
	TEST(4 == HashSize(hash), "size = 4");
	TEST(0 == HashInsert(hash, &d), "insert 4");
	TEST(5 == HashSize(hash), "size = 5");
	TEST(0 == HashInsert(hash, &f), "insert 6");
	TEST(6 == HashSize(hash), "size = 6");
	TEST(0 == HashInsert(hash, &d), "insert 4");
	TEST(7 == HashSize(hash), "size = 7");

	HashRemove(hash, &e);
	TEST(6 == HashSize(hash), "size = 6");
	HashRemove(hash, &d);
	TEST(5 == HashSize(hash), "size = 5");
	HashRemove(hash, &g);
	TEST(4 == HashSize(hash), "size = 4");

	HashDestroy(hash);
}

void TestHashFind()
{
	hash_t *hash = HashCreate(10, HashFunc, MatchFunc);
	size_t a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
	
	printf(BLUE "FIND" RESET);
	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(1 == HashSize(hash), "size = 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(2 == HashSize(hash), "size = 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");
	TEST(3 == HashSize(hash), "size = 3");

	TEST(a == *(size_t *)HashFind(hash, &a), "find 1");
	TEST(b == *(size_t *)HashFind(hash, &b), "find 2");
	TEST(c == *(size_t *)HashFind(hash, &c), "find 3");

	HashDestroy(hash);

	printf(BLUE"MORE FIND"RESET);
	hash = HashCreate(3, HashFunc3, MatchFunc);

	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");

	TEST(0 == HashInsert(hash, &e), "insert 5");
	TEST(0 == HashInsert(hash, &g), "insert 7");
	TEST(0 == HashInsert(hash, &d), "insert 4");
	TEST(0 == HashInsert(hash, &f), "insert 6");
	TEST(0 == HashInsert(hash, &d), "insert 4");

	TEST(g == *(size_t *)HashFind(hash, &g), "find 7");
	TEST(d == *(size_t *)HashFind(hash, &d), "find 4");
	TEST(e == *(size_t *)HashFind(hash, &e), "find 5");

	HashDestroy(hash);
}

void TestHashForEach()
{
	hash_t *hash = HashCreate(10, HashFunc, MatchFunc);
	size_t add = 1, a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
	
	printf(BLUE "FOR-EACH" RESET);
	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(1 == HashSize(hash), "size = 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(2 == HashSize(hash), "size = 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");
	TEST(3 == HashSize(hash), "size = 3");

	HashForeach(hash, PrintEach, NULL);

	HashDestroy(hash);

	printf(BLUE"MORE FIND"RESET);
	hash = HashCreate(3, HashFunc3, MatchFunc);

	TEST(0 == HashSize(hash), "size = 0");
	TEST(1 == HashIsEmpty(hash), "empty");
	TEST(0 == HashInsert(hash, &a), "insert 1");
	TEST(0 == HashIsEmpty(hash), "not empty");
	TEST(0 == HashInsert(hash, &b), "insert 2");
	TEST(0 == HashInsert(hash, &c), "insert 3");

	TEST(0 == HashInsert(hash, &e), "insert 5");
	TEST(0 == HashInsert(hash, &g), "insert 7");
	TEST(0 == HashInsert(hash, &d), "insert 4");
	TEST(0 == HashInsert(hash, &f), "insert 6");
	TEST(0 == HashInsert(hash, &d), "insert 4");

	HashForeach(hash, PrintEach, NULL);
	HashForeach(hash, AddtoEach, &add);
	printf("\n");
	HashForeach(hash, PrintEach, NULL);

	HashDestroy(hash);
}

/*void TestDict()
{
	hash_t *hash = HashCreate(570, HashFuncStr, MatchFunc);
	const file_name = "/usr/share/dict/words";
	FILE *words = fopen();

	while (i < 5000)
	{
		fputs(words);
	}
}
*/
int main()
{
	const char *file_name = "";

	TestHashInsert();
	TestHashRemove();
	TestHashFind();
	TestHashForEach();

	return 0;
}
