#include <stdio.h> /* printf() */

#include "trie.h"

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

void TestInsert()
{
	unsigned char d1[4] = {3,5,4,2};
	unsigned char d2[4] = {6,1,7,8};
	unsigned char d3[4] = {1,0,5,9};
	unsigned char buff[4] = {1,2,3,4};
	trie_t *trie = TrieCreate(8);

	TEST(1 ==  TrieIsEmpty(trie), "empty");
	TEST(0 == TrieCountEdges(trie), "size = 0");
	TEST(0 == TrieInsert(trie, d1), "insert d1");
	TEST(8 == TrieCountEdges(trie), "edges num = 8");
	TEST(0 == TrieInsert(trie, d2), "insert d2");
	TEST(12 == TrieCountEdges(trie), "edges num = 12");
	TEST(2 == TrieCountOccupiedLeafs(trie), "2 leafs");

	TrieFreeLeaf(trie, d1);
	TEST(1 == TrieCountOccupiedLeafs(trie), "1 leafs");

	TEST(1 == TrieIsAvailable(trie, d1), "available");
	TEST(1 == TrieIsAvailable(trie, d3), "available");
	TEST(0 == TrieIsAvailable(trie, d2), "not available");

	TrieFindFirstAvailable(trie, buff);

	printf("%d\n", buff[0]);
	printf("%d\n", buff[1]);
	printf("%d\n", buff[2]);
	printf("%d\n", buff[3]);

	TrieDestroy(trie);
}

void TestFirsatAvail()
{
	unsigned char buff[4] = {4,3,2,1};
	trie_t *trie = TrieCreate(10);

	TrieFindFirstAvailable(trie, buff);

	printf("%d\n", buff[0]);
	printf("%d\n", buff[1]);
	printf("%d\n", buff[2]);
	printf("%d\n", buff[3]);

	TrieDestroy(trie);
}

int main()
{
	TestInsert();
	TestFirsatAvail();

	return 0;
}