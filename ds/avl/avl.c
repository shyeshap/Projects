/*********************************
 *          SHYE SHAIRA          *
 *          20/01/2020           *
 *                               *
 *         BALANCED TREE         *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "avl.h" /* avl API */

#define FREE(ptr) free(ptr); ptr = NULL;

typedef enum children
{
	LEFT,
	RIGHT,
	NUM_OF_CHILDREN
} children_t;

typedef struct AVLNode
{
	void *data;
	struct AVLNode *child[NUM_OF_CHILDREN];
	long height;
} avl_node_t;

struct AVLTree
{
	avl_node_t *root;
	compare_func_t func;
};

static avl_node_t *AVLCreateNode(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(*new_node));
	if (NULL != new_node)
	{
		new_node->data = data;
		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
		new_node->height = 0;	
	}
	
	return new_node;
}

static size_t AVLPreOrderSize(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return 1 + AVLPreOrderSize(node->child[LEFT]) + AVLPreOrderSize(node->child[RIGHT]);
}

static size_t MaxChildHeight(avl_node_t *node) 
{
	return node->child[RIGHT]->height > node->child[LEFT]->height ? 
			node->child[RIGHT]->height : node->child[LEFT]->height;
}

static void AVLUpdateHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	if (NULL == node->child[RIGHT] && NULL == node->child[LEFT])
	{
		node->height = 0;
	}
	
	else if (NULL == node->child[RIGHT] && NULL != node->child[LEFT])
	{
		node->height = node->child[LEFT]->height + 1;
	}
	
	else if (NULL == node->child[LEFT] && NULL != node->child[RIGHT])
	{
		node->height = node->child[RIGHT]->height + 1;
	}
	
	else
	{
		node->height = MaxChildHeight(node) + 1;
	}	
}

static avl_node_t *AVLRotate(avl_node_t *node, int rotation_direction)
{
	avl_node_t *child_holder = node->child[!rotation_direction];
	
	node->child[!rotation_direction] = child_holder->child[rotation_direction];
	child_holder->child[rotation_direction] = node;
	
	AVLUpdateHeight(node);
	
	return child_holder;
}

static long GetBalanceFactor(avl_node_t *node)
{
	long left_child_height = -1, right_child_height = -1;
	
	if (NULL == node)
	{
		return -1;
	}
	
	if (NULL != node->child[RIGHT])
	{
		right_child_height = node->child[RIGHT]->height;
	}
	
	if (NULL != node->child[LEFT])
	{
		left_child_height = node->child[LEFT]->height;
	}
	
	return right_child_height - left_child_height;
}

static avl_node_t *AVLBalance(avl_node_t *node)
{	
	if (GetBalanceFactor(node) > 1)
	{
		if (NULL != node->child[LEFT] && GetBalanceFactor(node->child[LEFT]) < 0)
		{
			node->child[LEFT] = AVLRotate(node->child[LEFT], LEFT);
		}
		
		node = AVLRotate(node, LEFT);
	}

	else if(GetBalanceFactor(node) < -1)
	{
		if (NULL != node->child[RIGHT] && GetBalanceFactor(node->child[RIGHT]) > 0)
		{
			node->child[RIGHT] = AVLRotate(node, LEFT);
		}
		
		node = AVLRotate(node, RIGHT);
	}
	
	return node;
}

static avl_node_t *AVLInsertNode(compare_func_t func, avl_node_t *root, avl_node_t *new_node)
{
	children_t child_side = 0;
	
	assert(NULL != func);
	
	child_side = 0 < func(new_node->data, root->data);
	
	if (root->child[child_side] == NULL)
	{
		root->child[child_side] = new_node;
		AVLUpdateHeight(root);
		return AVLBalance(root);
	}
	
	else
	{
		root->child[child_side] = AVLInsertNode(func, root->child[child_side], new_node);
		AVLUpdateHeight(root);
	}
	
	return AVLBalance(root);
}

static avl_node_t *AVLFindNode(compare_func_t func, avl_node_t *node, const void *data)
{
	avl_node_t *ret = NULL;
	
	assert(NULL != func);
	
	if (NULL == node || func(data, node->data) == 0)
	{
		return node;
	}
	
	else
	{
		ret = AVLFindNode(func, node->child[0 < func(data, node->data)], data);
	}
	
	return ret;
}

static avl_node_t *AVLFindSuccessor(avl_node_t *node)
{
	avl_node_t *successor = NULL;
	
	if (NULL == node->child[LEFT])
	{
		return node;
	}
	
	else if (NULL == node->child[LEFT]->child[LEFT])
	{
		successor = node->child[LEFT];
		node->child[LEFT] = node->child[LEFT]->child[RIGHT];
	}
	
	else
	{
		successor = AVLFindSuccessor(node->child[LEFT]);
	}
	
	AVLUpdateHeight(node);
	AVLBalance(node);
	
	return successor;
}

static avl_node_t *AVLFindReplacer(avl_node_t *node_to_remove)
{
	avl_node_t *successor = NULL;
	
	if (NULL != node_to_remove->child[RIGHT])
	{
		if (NULL != node_to_remove->child[LEFT])
		{
			successor = AVLFindSuccessor(node_to_remove->child[RIGHT]);
			
			return successor;
		}
		
		return node_to_remove->child[RIGHT];
	}
	
	return node_to_remove->child[LEFT];
}

static avl_node_t *AVLRemoveNode(compare_func_t func, avl_node_t *root, 
													const void *data_to_remove)
{
	avl_node_t *replacer = NULL;
		
	assert(NULL != func);
	
	if (NULL != root)	
	{
		if (func(data_to_remove, root->data) == 0)
		{
			replacer = AVLFindReplacer(root);
			
			if (NULL != replacer)
			{
				replacer->child[LEFT] = root->child[LEFT];
				
				if(replacer != root->child[RIGHT])
				{
					replacer->child[RIGHT] = root->child[RIGHT];
				}
			}
			
			FREE(root);
			AVLUpdateHeight(replacer);

			return AVLBalance(replacer);
		}
		
		else
		{
			root->child[0 < func(data_to_remove, root->data)] = 
			AVLRemoveNode(func, root->child[0 < func(data_to_remove, root->data)], 		
			data_to_remove);
		}
	}
	
	AVLUpdateHeight(root);

	return AVLBalance(root);
}

static int AVLForeachInOrder(avl_node_t *node, action_ptr_t action, void *param)
{
	int res = 0;
	
	if (NULL == node)
	{
		return res;
		
	}
	
	else
	{
		res += AVLForeachInOrder(node->child[LEFT], action, param);
		res += action(node->data, param);
		res += AVLForeachInOrder(node->child[RIGHT], action, param);
	}

	return res;
}

static void AVLDestroyRec(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	else
	{
		AVLDestroyRec(node->child[LEFT]);
		AVLDestroyRec(node->child[RIGHT]);
		
		FREE(node);
	}
}

avl_t *AVLCreate(compare_func_t cmp)
{
	avl_t *new_tree = NULL;

	assert(NULL != cmp);
	
	new_tree = (avl_t *)malloc(sizeof(*new_tree));
	if (NULL != new_tree)
	{
		new_tree->func = cmp;
		new_tree->root = NULL;
	}
	
	return new_tree;
}

void AVLDestroy(avl_t *tree)
{
	AVLDestroyRec(tree->root);
		
	FREE(tree);
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = AVLCreateNode(data);
	
	assert (NULL != tree);
	
	if (NULL == new_node)
	{
		return 1;
	}
	
	else if (NULL == tree->root)
	{
		tree->root = new_node;
		AVLUpdateHeight(tree->root);
	}
	
	else
	{
		tree->root = AVLInsertNode(tree->func, tree->root, new_node);
	}
	
	return 0;
}

void AVLRemove(avl_t *tree, const void *data)
{
	assert (NULL != tree);
	
	tree->root = AVLRemoveNode(tree->func, tree->root, data);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	avl_node_t *node = NULL;
	
	assert(NULL != tree);
	
	node = AVLFindNode(tree->func, tree->root, data);
	
	if (node == NULL)
	{
		return NULL;
	}
	
	else
	{
		return node->data;
	}
}

int AVLForeach(avl_t *tree, action_ptr_t action, void *param)
{
	assert (NULL != tree);
	assert (NULL != action);
	
	return AVLForeachInOrder(tree->root, action, param);
}

size_t AVLSize(const avl_t *tree)
{
	assert(NULL != tree);
	
	return AVLPreOrderSize(tree->root);
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(NULL != tree);
	
	return tree->root == NULL;
}

long AVLGetHeight(const avl_t *tree)
{
	assert(NULL != tree);
	
	if (NULL == tree->root)
	{
		return -1;
	}

	return tree->root->height;
}

