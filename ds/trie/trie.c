/*********************************
 *          SHYE SHAIRA          *
 *          03/02/2020           *
 *                               *
 *             TRIE              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "trie.h" /*trie API */

#define FREE(ptr) free(ptr); ptr = NULL;
#define MASK_1 (1)
#define BITS_IN_BYTE (8)
#define IP_ARR_SIZE (4)
#define IP_SIZE (IP_ARR_SIZE * BITS_IN_BYTE)

typedef enum ChildSide
{
	LEFT,
	RIGHT,
	NUM_OF_CHILDREN
} side_t; 

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
	size_t height;	
};

/************************************************************/

static void DestroyIMP(trie_node_t *node);
static size_t CountEdgesIMP(trie_node_t *node);
static side_t WhichChildIMP(unsigned char *data, size_t height);
static status_t InsertIMP(trie_node_t *node, unsigned char *data, size_t height);
static trie_node_t *CreateNodeIMP();
static void UpdateAvailabilityIMP(trie_node_t *node);
static size_t CountOccupiedLeafsIMP(trie_node_t *node);
static bool_t IsAvailableIMP(trie_node_t *node, unsigned char *data, size_t height);
static void FindFirstAvailableIMP(trie_node_t *node, unsigned char *ip_mask, size_t height);
static void FreeLeafIMP(trie_node_t *node, unsigned char *data, size_t height);
static void ZeroAvailIMP(unsigned char *ip, size_t height);

/*************************************************************/

trie_t *TrieCreate(size_t height)
{
	trie_t *new_tree = (trie_t *)malloc(sizeof(*new_tree));
	if (NULL == new_tree)
	{
		return NULL;
	}

	new_tree->root = CreateNodeIMP();
	if (NULL == new_tree->root)
	{
		FREE(new_tree);
		return NULL;
	}
	
	new_tree->height = height;

	return new_tree;
}

void TrieDestroy(trie_t *trie)
{
	assert(NULL != trie);

	DestroyIMP(trie->root);
	trie->root = NULL;

	FREE(trie);
}

status_t TrieInsert(trie_t *trie, unsigned char *data)
{
	assert(NULL != trie);
	assert(NULL != data);

	return InsertIMP(trie->root, data, trie->height);
}

bool_t TrieIsEmpty(const trie_t *trie)
{
	assert(NULL != trie);

	return (NULL == trie->root->direction[LEFT] && 
			NULL == trie->root->direction[RIGHT]);
}

size_t TrieCountEdges(const trie_t *trie)
{
	assert(NULL != trie);

	return (CountEdgesIMP(trie->root) - 1);
}

size_t TrieCountOccupiedLeafs(const trie_t *trie)
{
	assert(NULL != trie);

	return CountOccupiedLeafsIMP(trie->root);
}

void TrieFreeLeaf(trie_t *trie, unsigned char *data)
{
	assert(NULL != trie);
	assert(NULL != data);

	FreeLeafIMP(trie->root, data, trie->height);
}

bool_t TrieIsAvailable(trie_t *trie, unsigned char *data)
{
	assert(NULL != trie);
	assert(NULL != data);

	return IsAvailableIMP(trie->root, data, trie->height);
}

void TrieFindFirstAvailable(trie_t *trie, unsigned char *data)
{
	assert(NULL != trie);
	assert(NULL != data);  

	ZeroAvailIMP(data, trie->height);

	FindFirstAvailableIMP(trie->root, data, trie->height);	
}

/****************************************************************/

static void FindFirstAvailableIMP(trie_node_t *node, unsigned char *data, size_t height)
{
	size_t side = LEFT;

	if (NULL == node || 0 == height)
	{
		return;
	}

	if (NULL != node->direction[side] && 
		NOT_AVAILABLE == node->direction[side]->avail)
	{
		*(data + ((IP_SIZE - height) / BITS_IN_BYTE)) |=
				(MASK_1 << ((height - 1) % BITS_IN_BYTE));  
		side = RIGHT;
	}

	else
	{
		FindFirstAvailableIMP(node->direction[side], data, height - 1);
	}
}

static void ZeroAvailIMP(unsigned char *data, size_t height)
{
	if (0 == height)
	{
		return;
	}

	*(data + ((IP_SIZE - height) / BITS_IN_BYTE)) &=
				~(MASK_1 << ((height - 1) % BITS_IN_BYTE));
	
	ZeroAvailIMP(data, height - 1);
}

static side_t WhichChildIMP(unsigned char *data, size_t height)
{
	return 0 < ((*(data + ((IP_SIZE - height) / BITS_IN_BYTE)) &
				(MASK_1 << ((height - 1) % BITS_IN_BYTE))));  
}

static size_t CountOccupiedLeafsIMP(trie_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}

	if (NULL == node->direction[LEFT] &&
		NULL == node->direction[RIGHT] && 
		NOT_AVAILABLE == node->avail)
	{
		return 1;
	}

	return (CountOccupiedLeafsIMP(node->direction[LEFT]) + 
			CountOccupiedLeafsIMP(node->direction[RIGHT]));
}

static status_t InsertIMP(trie_node_t *node, unsigned char *data, size_t height)
{
	status_t status = SUCCESS;
	side_t next_side = WhichChildIMP(data, height);

	if (0 == height)
	{
		node->avail = NOT_AVAILABLE;

		return SUCCESS;
	}

	if (NULL == node->direction[next_side])
	{
		node->direction[next_side] = CreateNodeIMP();
		if (NULL == node->direction[next_side])
		{
			return FAIL;
		}
	}
	
	status = InsertIMP(node->direction[next_side], data, height - 1);
	UpdateAvailabilityIMP(node);

	return status;
}

static void UpdateAvailabilityIMP(trie_node_t *node)
{
	if (NULL != node->direction[LEFT] &&
		NULL != node->direction[RIGHT] &&
		NOT_AVAILABLE == node->direction[LEFT]->avail &&
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

static bool_t IsAvailableIMP(trie_node_t *node, unsigned char *data, size_t height)
{
	bool_t status = TRUE;

	if (NULL == node || (0 == height && AVAILABLE == node->avail))
	{
		return TRUE;
	}

	if (NOT_AVAILABLE == node->avail)
	{
		return FALSE;
	}

	status *= IsAvailableIMP(node->direction[WhichChildIMP(data, height)], data, height - 1);

	return status;
}

static void FreeLeafIMP(trie_node_t *node, unsigned char *data, size_t height)
{
	if (0 == height)
	{
		node->avail = AVAILABLE;

		return;
	}

	FreeLeafIMP(node->direction[WhichChildIMP(data, height)], data, height - 1);

	node->avail = AVAILABLE;
}

static size_t CountEdgesIMP(trie_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}

	return  1 + CountEdgesIMP(node->direction[LEFT]) + 
				CountEdgesIMP(node->direction[RIGHT]);
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
