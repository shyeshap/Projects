/*********************************
 *          SHYE SHAIRA          *
 *          20/01/2020           *
 *                               *
 *             HASH              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "trie.h" /*trie API */

#define FREE(ptr) free(ptr); ptr = NULL;

enum ChildSide
{
	LEFT,
	RIGHT,
	NUM_OF_CHILDREN
}; 

typedef enum Avalability
{
	AVAILABLE,
	NOT_AVAILABLE
} availability_t;

typedef struct TrieNode
{
	struct TrieNode *direction[2];
	availability_t avail;
} trie_node_t;

struct Trie
{
	trie_node_t *root;		
};

/************************************************************/

static void TrieDestroyIMP(trie_node_t *node);
static void DestroyIMP(trie_node_t *node);
static size_t CountUsedLeafsIMP(trie_node_t *node);

/*************************************************************/

trie_t *TrieCreate()
{
	trie_t *new_tree = (trie_t *)malloc(sizeof(*new_tree));
	if (NULL == new_tree)
	{
		return NULL;
	}

	new_tree->root = NULL;

	return new_tree;
}

void TrieDestroy(trie_t *trie)
{
	assert(NULL != trie);

	DestroyIMP(trie->root);

	FREE(trie);
}

status_t TrieInsert(trie_t *trie, char *data)
{
	return InsertIMP(trie->root, data);
}

bool_t TrieIsEmpty(const trie_t *trie)
{
	assert(NULL != trie);

	return NULL == root;
}

size_t TrieSize(const trie_t *trie)
{
	return SizeIMP(trie->root);
}

size_t TrieCountLeafs(const trie_t *trie)
{
	CountUsedLeafsIMP(trie->node);
}

/****************************************************************/

static void DestroyIMP(trie_node_t *node)
{
	assert(NULL != node);

	if (NULL == node)
	{
		return;
	}

	TrieDestroyIMP(node->direction[LEFT]);	
	TrieDestroyIMP(node->direction[RIGHT]);

	FREE(node);
}

static size_t SizeIMP(trie_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}

	return 1 + SizeIMP(node->direction[LEFT]) 
			 + SizeIMP(node->direction[RIGHT]);
}

static size_t CountUsedLeafsIMP(trie_node_t *node)
{
	if (NULL == node->direction[LEFT]  && 
		NULL == node->direction[RIGHT] && 
		NOT_AVALIABLE == node->avail)
	{
		return 1;
	}

	else if(NULL == node->direction[LEFT]  && 
			NULL == node->direction[RIGHT] && 
			NOT_AVALIABLE == node->avail)
	{
		return 0;
	}

	return (CountUsedLeafsIMP(node->direction[LEFT]) + 
			CountUsedLeafsIMP(node->direction[RIGHT]))
}

static status_t InsertIMP(trie_node_t *node, void *data)
{
	status_t stztus = SUCCESS;

	if ('\0' == *data)
	{
		return SUCCESS; 
	}

	else if (node->avail = NOT_AVALIABLE)
	{
		return FAIL;
	}

	if (NULL == node->direction[*data])
	{
		node->direction[*data] = CreateNode();
	}

	status = InsertIMP(node->direction[*data], ++data);

	if(NOT_AVAILABLE == node->direction[LEFT]->avail &&
		NOT_AVAILABLE == node->direction[RIGHT]->avail)	
	{
		node->avail = NOT_AVAILABLE;
	}

}