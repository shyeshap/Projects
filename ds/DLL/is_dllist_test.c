/************************************************
*
* File: dllist.c
* Ex: double linked list data structure
* writer: Israel Drayfus
* Description: functions of double linked list.
*
*************************************************/

#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/
#include <stdio.h> /*printf()*/

#include "dllist.h" /* API header */

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

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

struct Iterator
{
	struct DLLNode *node;
};

typedef struct DLLNode dllnode_t;

struct DLLNode
{
	void *data;
	struct DLLNode *next;
	struct DLLNode *prev;
};

struct DLL
{
	dllnode_t head;
	dllnode_t tail;
};

int value = 1;
int int_test[] = {1,2,3};
char char_test[] = {'1','2','3','4','5','6','7','8','9'};
float float_test[] = {1.0,2.0,3.0};

int PrintEach(void *data, void *ap)
{
	printf("%c\n", *(char *)data);
	
	return 0;
}

int IsMatch(void *data, void *ap)
{
	return *(char *)data == *(char *)ap;
}

int main()
{
	dll_t *dll = DLLCreate();
	iterator_t my_it;
	iterator_t my_it2;
	void *data = NULL;
	
	TEST(dll->head.next == &dll->tail, "DLLCreate(), head and tail conection(1)");
	TEST(dll->head.prev == NULL, "DLLCreate(), head prev == NULL");
	TEST(dll->tail.prev == &dll->head, "DLLCreate(), head and tail conection(2)");
	TEST(dll->tail.next == NULL, "DLLCreate(), head prev == NULL");
	printf("\n");
	
	my_it.node = &dll->tail;
	my_it = DLLInsert(dll, my_it, &char_test[0]);
	TEST(dll->head.next == my_it.node, "DLLInsert(), prev->new_node");
	TEST(&char_test[0] == DLLGetData(my_it), "DLLInsert() new_node->data & GetData()");
	TEST(&dll->tail == my_it.node->next, "DLLInsert(), new_node->next");
	TEST(&dll->head == my_it.node->prev, "DLLInsert(), new_node->prev");
	TEST(dll->tail.prev == my_it.node, "DLLInsert(), next->new_node");
	printf("\n");
	TEST(DLLIsEmpty(dll) == 0, "DLLIsEmpty(), not empty list");
	my_it = DLLBegin(dll);
	TEST(&dll->tail == my_it.node->next, "DLLBegin(), one item in list");
	TEST(DLLSize(dll) == 1, "DLLIsEmpty(), one item in list");
	my_it = DLLGetNext(my_it);
	my_it2 = my_it;
	TEST(1 == DLLIsSameIter(my_it, my_it2), "DLLIsSameIter(), True");
	TEST(my_it.node == &dll->tail, "DLLGetNext, one item in list");
	my_it = DLLGetPrev(my_it);
	TEST(dll->head.next == my_it.node, "DLLGetPrev(), one item in list");
	TEST(0 == DLLIsSameIter(my_it, my_it2), "DLLIsSameIter(), False");
	printf("\n");
	
	my_it = DLLRemove(my_it);
	TEST(dll->head.next == &dll->tail, "DLLRemove(), test 1");
	TEST(dll->head.next == my_it.node, "DLLRemove(), test 2");
	TEST(DLLIsEmpty(dll) == 1, "DLLIsEmpty(), empty list");
	my_it = DLLBegin(dll);
	TEST(my_it.node == &dll->tail, "DLLBegin, empty list");
	my_it = DLLEnd(dll);
	TEST(my_it.node == &dll->tail, "DLLBegin, one item in list");
	TEST(DLLSize(dll) == 0, "DLLIsEmpty(), empty list");
	printf("\n");
	
	my_it = DLLPushBack(dll, &int_test[0]);
	TEST(my_it.node->data == &int_test[0], "DLLPushBack() empty list, data");
	TEST(my_it.node->next == &dll->tail, "DLLPushBack() empty list, next");
	TEST(my_it.node->prev == &dll->head, "DLLPushBack() empty list, prev");
	my_it = DLLPushBack(dll, &int_test[1]);
	TEST(my_it.node->data == &int_test[1], "DLLPushBack() one item, data");
	TEST(my_it.node->next == &dll->tail, "DLLPushBack() one item, next");
	TEST(my_it.node->prev->data == &int_test[0], "DLLPushBack() one item, prev");
	
	data = DLLPopBack(dll);
	TEST(data == &int_test[1], "DLLPopBack() two items, data");
	TEST(dll->tail.prev->data == &int_test[0], "DLLPopBack() two items, removing");
	data = DLLPopBack(dll);
	TEST(data == &int_test[0], "DLLPopBack() one item, data");
	TEST(dll->tail.prev == &dll->head, "DLLPopBack() one item, removing");
	
	my_it = DLLPushFront(dll, &int_test[0]);
	TEST(my_it.node->data == &int_test[0], "DLLPushFront() empty list, data");
	TEST(my_it.node->next == &dll->tail, "DLLPushFront() empty list, next");
	TEST(my_it.node->prev == &dll->head, "DLLPushFront() empty list, prev");
	my_it = DLLPushFront(dll, &int_test[1]);
	TEST(my_it.node->data == &int_test[1], "DLLPushFront() one item, data");
	TEST(my_it.node->next == dll->tail.prev, "DLLPushFront() one item, next");
	TEST(my_it.node->next->data == &int_test[0], "DLLPushFront() one item, prev");
	
	data = DLLPopFront(dll);
	TEST(data == &int_test[1], "DLLPopFront() two items, data");
	TEST(dll->head.next->data == &int_test[0], "DLLPopFront() two items, removing");
	data = DLLPopFront(dll);
	TEST(data == &int_test[0], "DLLPopFront() one item, data");
	TEST(dll->head.next == &dll->tail, "DLLPopFront() one item, removing");
	printf("\n");
	
	my_it = DLLPushBack(dll, &char_test[0]);
	DLLPushBack(dll, &char_test[1]);
	DLLPushBack(dll, &char_test[2]);
	my_it2 = DLLPushBack(dll, &char_test[3]);
	DLLForEach(my_it, my_it2, &PrintEach, &value);
	TEST(my_it2.node == DLLFind(my_it, my_it2, &IsMatch, &char_test[3]).node, "find");
	
	DLLDestroy(dll);

	return 0;
}




