/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Binary Search Tree          */
/*   Author: Shye Shapira		 */
/*   Last Updated 7/1/20         */
/*   Reviewed by: Itai     		 */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /*assert() */ 

#include "bst.h" /* bst API */

#define DEADBEEF (void *)0xDEADBEEF
#define FREE(ptr) free(ptr); ptr = NULL;

typedef enum SIDE
{
	LEFT,
	RIGHT
} side_t;

typedef struct BSTNode
{
	void *data;
	struct BSTNode *children[2];
	struct BSTNode *parent;
} node_t;

struct BSTree
{
	node_t dummy;
	compare_func_t cmp;
	void *param;
};

bst_t *BSTCreate(compare_func_t cmp, void *param)
{
	bst_t *new_tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new_tree)
	{
		return NULL;
	}
	
	new_tree->cmp = cmp;
	new_tree->param = param;
	new_tree->dummy.data = DEADBEEF;
	new_tree->dummy.children[LEFT] = NULL;
	new_tree->dummy.children[RIGHT] = NULL;
	new_tree->dummy.parent = NULL;
	
	return new_tree;
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	
	return 0 == tree->dummy.children[LEFT];
}

bst_itr_t BSTBegin(const bst_t *tree)
{
	bst_itr_t itr = NULL;
	
	assert(NULL != tree);
	
	itr = (bst_itr_t)&tree->dummy;
	
	while (NULL != itr->children[LEFT])
	{
		itr = itr->children[LEFT];
	}
	
	return itr; 
}

bst_itr_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);
	
	return (bst_itr_t)&tree->dummy;
}

int BSTIsSameItr(const bst_itr_t it1, const bst_itr_t it2)
{
	return it1 == it2;
}

void *BSTGetData(const bst_itr_t it)
{
	assert(NULL != it);
	
	return it->data;
}

int BSTInsert(bst_t *tree, void *data)
{
	bst_itr_t itr = NULL;
	int child_side = LEFT;
	
	assert(NULL != tree);
	
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return 1;
	}
	
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	itr = tree->dummy.children[LEFT];
	
	if (BSTIsEmpty(tree))
	{
		tree->dummy.children[LEFT] = new_node;
		new_node->parent = &tree->dummy;
		
		return 0;
	}
	
	child_side = tree->cmp(data, itr->data, NULL);
	
	while (NULL != itr->children[child_side])
	{
		itr = itr->children[child_side];
		child_side = tree->cmp(data, itr->data, NULL);
	}		

	itr->children[child_side] = new_node;
	new_node->parent = itr;
		
	return 0;
}

static int ChildSide(bst_itr_t itr)
{
	assert(NULL != itr);
	
	return BSTIsSameItr(itr, itr->parent->children[RIGHT]);
}

void BSTDestroy(bst_t *tree)
{
	bst_itr_t itr = NULL;
	
	assert(NULL != tree);
	
	itr = tree->dummy.children[LEFT];
	
	while (!BSTIsEmpty(tree))
	{
		BSTRemove(itr);
		itr = tree->dummy.children[LEFT];
	}
	
	FREE(tree);
}

bst_itr_t BSTNext(bst_itr_t it)
{
	assert(NULL != it);
	
	if (NULL != it->children[RIGHT])
	{
		it = it->children[RIGHT];
		
		while (NULL != it->children[LEFT])
		{
			it = it->children[LEFT];
		}
	}
	
	else
	{
		while (LEFT != ChildSide(it))
		{
			it = it->parent;
		}
		
		it = it->parent;
	}
	
	return it;
}

bst_itr_t BSTPrev(bst_itr_t it)
{
	assert(NULL != it);
	
	if (NULL != it->children[LEFT])
	{
		it = it->children[LEFT];
		
		while (NULL != it->children[RIGHT])
		{
			it = it->children[RIGHT];
		}
	}
	
	else
	{
		while (DEADBEEF != it->parent->data && LEFT == ChildSide(it))
		{
			it = it->parent;
		}
		
		it = it->parent;
	}
	
	return it;
}

void BSTRemove(bst_itr_t it)
{
	bst_itr_t successor = NULL;
	
	assert(NULL != it);
	
	if (NULL == it->children[LEFT] && NULL == it->children[RIGHT])
	{
		it->parent->children[ChildSide(it)] = NULL;
		it->parent = NULL;
	}
	
	else if (NULL != it->children[LEFT] && NULL == it->children[RIGHT])
	{
		it->parent->children[ChildSide(it)] = it->children[LEFT];
		it->children[LEFT]->parent = it->parent  ;
	}
	
	else if (NULL != it->children[RIGHT] && NULL == it->children[LEFT])
	{
		it->parent->children[ChildSide(it)] = it->children[RIGHT];
		it->children[RIGHT]->parent = it->parent;
	}
	
	else
	{
		successor = BSTNext(it);
		successor->children[LEFT] = it->children[LEFT];
		it->children[LEFT]->parent = successor;
		it->children[RIGHT]->parent = it->parent;
		it->parent->children[ChildSide(it)] = it->children[RIGHT];
	}
	
	FREE(it);	
}

size_t BSTSize(const bst_t *tree)
{	
	bst_itr_t itr = NULL;
	bst_itr_t dummy = NULL;
	size_t counter = 0;

	assert(NULL != tree);
	
	itr = BSTBegin(tree);
	dummy = BSTEnd(tree);
	
	while(!BSTIsSameItr(dummy, itr))
	{
		++counter;
		itr = BSTNext(itr);
	}
	
	return counter;
}

bst_itr_t BSTFind(const bst_t *tree, const void *data)
{
	bst_itr_t itr = NULL;
	int match = 0;
	int direction = 0;

	assert(NULL != tree);
	
	itr = &((bst_t *)tree)->dummy;
	
	while ((NULL != itr->children[direction]) && !match)
	{
		itr = itr->children[direction];
		direction = tree->cmp(data, BSTGetData(itr), tree->param);
		match = !direction && !tree->cmp(BSTGetData(itr), data, tree->param);
	}
	
	if (!match)
	{
		itr = BSTEnd(tree);
	}
	
	return itr;
}

int BSTForEach(bst_itr_t start, bst_itr_t end, action_func_t action, void *param)
{
	int flag = 0;
	
	assert(NULL != start);
	assert(NULL != end);
	
	while(0 == flag && !BSTIsSameItr(start, end))
	{
		flag = action(start->data, param);
		start = BSTNext(start);
	}
	
	return flag;
}
