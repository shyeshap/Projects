/*********************************/
/*    Data Structures            */
/*    Vector                     */       
/*    Author :  SHYE             */
/*    Reviewed By: YONATAN       */
/*    Date:     1/12/2019        */
/*                               */
/*********************************/

#include <stdio.h>  /* printf() */
#include <string.h> /* strcmp(), strcpy() */
#include <stdlib.h> /* free */

#include "linked_list.h" /* linked list data structure functions */

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"

#define FREE(x) free(x); x = NULL;

#define RUN_TEST(test, msg)	if(test)					 	\
							{								\
								printf(GRN "[OK]\n" RESET);	\
							}								\
							else							\
							{								\
								printf(RED "%s\n", msg);	\
							}

int AddOneIfEven(void *node, void *additional)
{
	node_t *n = (node_t *)node;
	
	if (((*(int *)n->data) % 2) == 0)
	{
		*(int *)n->data += 1;
	}
	
	return 0;
}

int PrintNode(void *node, void *additional)
{
	node_t *n = (node_t *)node;
	
	printf("data: %d, next: %p\n", *(int *)n->data, (void *)n->next);
	
	return 0;
}

int IsMatch(void *node, void *additional)
{
	node_t *n = (node_t *)node;
	
	return (*(int *)n->data == *(int *)additional);
}

void test()
{
	size_t x = 1, y = 2, z = 3, o = 4, p = 5;
	node_t *add1 = NULL, *add2 = NULL, *add3 = NULL, *add4 = NULL;
	node_t *head = SLLCreateNode(NULL, &x);
	node_t *head_loop = NULL;
	RUN_TEST(1 == SLLSize(head), "size = 1");
	add1 = SLLCreateNode(NULL, &x);
	add2 = SLLCreateNode(NULL, &x);
	add3 = SLLCreateNode(NULL, &x);
	SLLInsertAfter(add1, head);
	RUN_TEST(2 == SLLSize(head), "size = 2");
	SLLInsert(add2, add1);
	RUN_TEST(3 == SLLSize(head), "size = 3");
	SLLInsert(add3, add2);
	RUN_TEST(4 == SLLSize(head), "size = 4");
	SLLRemove(add2);
	RUN_TEST(3 == SLLSize(head), "after remove size = 3");
	SLLRemoveAfter(add1);
	RUN_TEST(2 == SLLSize(head), "after removeatafter size = 2");
	SLLDestroy(head);
	
	
	head = SLLCreateNode(NULL, &x);
	add1 = SLLCreateNode(NULL, &y);
	add2 = SLLCreateNode(NULL, &z);
	add3 = SLLCreateNode(NULL, &o);
	
	SLLInsertAfter(add3, head);
	SLLInsert(add2, add3);
	SLLInsert(add1, add3);
	
	SLLForEach(head, &PrintNode, &x);
	head = SLLFlip(head);
	SLLForEach(head, &PrintNode, &x);
	
	RUN_TEST(add2 == SLLGetNode(head, IsMatch, &z), "get node");
	
	SLLForEach(head, &AddOneIfEven, &x);
	SLLForEach(head, &PrintNode, &x);
	
	RUN_TEST(0 == SLLHasLoop(head), "no loop");
	
	
	add4 = SLLCreateNode(NULL, &p);
	add3 = SLLCreateNode(add4, &o);
	head = SLLCreateNode(add3, &o);
	add4->next = head;
	RUN_TEST(1 == SLLHasLoop(head), "has loop");
	
	add4 = SLLCreateNode(NULL, &p);
	add3 = SLLCreateNode(add4, &o);
	add2 = SLLCreateNode(add3, &z);
	head = SLLCreateNode(add2, &o);
	
	add1 = SLLCreateNode(add4, &y);
	
	RUN_TEST(add4 == SLLFindIntersection(head, add1), "intersection");
	
	SLLDestroy(head);
	SLLDestroy(add1);
}

int main()
{
	test();
	
	return 0;
}
