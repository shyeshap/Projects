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
	char *d1 = "1";
	char *d2 = "010101000";
	char *d3 = "0101000111001";
	trie_t *trie = TrieCreate();

	TEST(1 ==  TrieIsEmpty(trie), "empty");
	TEST(0 == TrieSize(trie), "size = 0");
	TEST(0 == TrieInsert(trie, d1), "insert d1");
	TEST(1 == TrieSize(trie), "size = 1");
	TEST(0 == TrieInsert(trie, d2), "insert d2");
	TEST(10 == TrieSize(trie), "size = 10");
	TEST(2 == TrieCountLeafs(trie), "2 leafs");

	TrieFreeLeaf(trie, d1);
	TEST(1 == TrieCountLeafs(trie), "1 leafs");

	TEST(1 == TrieIsAvailable(trie, d1), "available");
	TEST(1 == TrieIsAvailable(trie, d3), "available");
	TEST(0 == TrieIsAvailable(trie, d2), "not available");
	TrieDestroy(trie);
}

int main()
{
	TestInsert();

	return 0;
}