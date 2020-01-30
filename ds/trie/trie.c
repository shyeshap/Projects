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

static void DestroyIMP(trie_node_t *node);
static size_t CountUsedLeafsIMP(trie_node_t *node);
static size_t SizeIMP(trie_node_t *node);
static status_t InsertIMP(trie_node_t *node, char *data);
static trie_node_t *CreateNodeIMP();
static void UpdateAvailabilityIMP(trie_node_t *node);
static void FreeLeafIMP(trie_node_t *node, char *data);
static bool_t IsAvailableIMP(trie_node_t *node, char *data);


/*************************************************************/

trie_t *TrieCreate()
{
	trie_t *new_tree = (trie_t *)malloc(sizeof(*new_tree));
	if (NULL == new_tree)
	{
		return NULL;
	}

	new_tree->root = CreateNodeIMP();

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
	assert(NULL != trie);
	assert(NULL != data);

	if (NULL == trie->root)
	{
		trie->root = CreateNodeIMP();
		if (NULL == trie->root)
		{
			return FAIL;
		}
	}
	
	return InsertIMP(trie->root, data);
}

bool_t TrieIsEmpty(const trie_t *trie)
{
	assert(NULL != trie);

	return (NULL == trie->root->direction[LEFT] && 
			NULL == trie->root->direction[RIGHT]);
}

size_t TrieSize(const trie_t *trie)
{
	assert(NULL != trie);

	return (SizeIMP(trie->root) - 1);
}

size_t TrieCountLeafs(const trie_t *trie)
{
	assert(NULL != trie);

	return CountUsedLeafsIMP(trie->root);
}

void TrieFreeLeaf(trie_t *trie, char *data)
{
	assert(NULL != trie);
	assert(NULL != data);

	FreeLeafIMP(trie->root, data);
}

bool_t TrieIsAvailable(trie_t *trie, char *data)
{
	assert(NULL != trie);
	assert(NULL != data);

	return IsAvailableIMP(trie->root, data);
}

/****************************************************************/

static bool_t IsAvailableIMP(trie_node_t *node, char *data)
{
	bool_t status = TRUE;

	if (NULL == node || ('\0' == *data && AVAILABLE == node->avail))
	{
		return TRUE;
	}

	if (NOT_AVAILABLE == node->avail)
	{
		return FALSE;
	}

	status *= IsAvailableIMP(node->direction[*data - 48], data + 1);

	return status;
}

static void FreeLeafIMP(trie_node_t *node, char *data)
{
	if ('\0' == *data)
	{
		node->avail = AVAILABLE;

		return;
	}

	FreeLeafIMP(node->direction[*data - 48], data + 1);

	node->avail = AVAILABLE;
}

static status_t InsertIMP(trie_node_t *node, char *data)
{
	status_t status = SUCCESS;

	if ('\0' == *data)
	{
		node->avail = NOT_AVAILABLE;

		return SUCCESS; 
	}

	if (NULL == node->direction[*data - 48])
	{
		node->direction[*data - 48] = CreateNodeIMP();
		if (NULL == node->direction[*data - 48])
		{
			return FAIL;
		}
	}

	status = InsertIMP(node->direction[*data - 48], data + 1);

	if(SUCCESS == status && node->direction[!(*data - 48)])
	{
		UpdateAvailabilityIMP(node);
	}
	
	return status;
}

static void UpdateAvailabilityIMP(trie_node_t *node)
{
	if (NOT_AVAILABLE == node->direction[LEFT]->avail &&
		NOT_AVAILABLE == node->direction[RIGHT]->avail)	
	{
		node->avail = NOT_AVAILABLE;
	}
}

static trie_node_t *CreateNodeIMP()
{
	trie_node_t *new_node = malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		return NULL;
	}

	new_node->avail = AVAILABLE;
	new_node->direction[LEFT] = NULL;
	new_node->direction[RIGHT] = NULL;

	return new_node;
}

static void DestroyIMP(trie_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	DestroyIMP(node->direction[LEFT]);	
	DestroyIMP(node->direction[RIGHT]);

	FREE(node);
}

static size_t SizeIMP(trie_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}

	return  1 + SizeIMP(node->direction[LEFT]) + 
				SizeIMP(node->direction[RIGHT]);
}

static size_t CountUsedLeafsIMP(trie_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}

	if (NULL == node->direction[LEFT]  && 
		NULL == node->direction[RIGHT] && 
		NOT_AVAILABLE == node->avail)
	{
		return 1;
	}

	else if(NULL == node->direction[LEFT]  && 
			NULL == node->direction[RIGHT] && 
			AVAILABLE == node->avail)
	{
		return 0;
	}

	return (CountUsedLeafsIMP(node->direction[LEFT]) + 
			CountUsedLeafsIMP(node->direction[RIGHT]));
}