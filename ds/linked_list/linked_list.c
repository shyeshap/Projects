/****************************************/
/*			Data Structures				*/
/*			Single Linked List			*/
/*			Author: Shye Shapira		*/
/*			Reviewed By: Raz			*/
/*			Date: 2/12/2019				*/
/*										*/
/****************************************/

#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert */

#include "linked_list.h" /*Single Linked List API Functions*/ 

#define FREE(x) free(x); x = NULL;

node_t *SLLCreateNode(node_t *next, const void *data)
{
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->next = next;
	node->data = (void *)data;
	
	return node;
}

void SLLDestroy(node_t *node)
{
	node_t *next = NULL;
	
	assert(NULL != node);

	while (NULL != node->next)
	{
		next = node->next;
		node->next = NULL;
		FREE(node);
		node = next;
	}
	
	FREE(node);
}

int SLLInsert(node_t *node, node_t *next_node)
{
	void *temp_data = NULL;
	
	assert(NULL != node);
	assert(NULL != next_node);
	
	temp_data = node->data;
	node->next = next_node->next;
	node->data = next_node->data;
	next_node->data = temp_data;
	next_node->next = node;
	
	return 0;
}

int SLLInsertAfter(node_t *new_node, node_t *previous_node)
{
	assert(NULL != new_node);
	assert(NULL != previous_node);
	
	new_node->next = previous_node->next;
	previous_node->next = new_node;
	
	return 0;
}

void SLLRemove(node_t *node)
{
	node_t *temp_node = NULL;
	
	assert(NULL != node);
	
	temp_node = node->next;
	
	node->data = temp_node->data;
	node->next = temp_node->next;
	temp_node->next = NULL;
	
	FREE(temp_node);
}

void SLLRemoveAfter(node_t *node)
{
	node_t *temp_node = node->next;
		
	node->next = temp_node->next;
	temp_node->next = NULL;
	
	FREE(temp_node);
}

size_t SLLSize(const node_t *head)
{
	node_t *runner = NULL;
	size_t counter = 0;
	
	assert(NULL != head);
	
	runner = (node_t *)head;
	
	while (NULL != runner)
	{
		runner = runner->next;
		++counter;
	}
	
	return counter;
}

node_t *SLLFlip(node_t *head)
{
	node_t *next = NULL, *prev = NULL, *current = NULL;
	
	assert(NULL != head);

	current = head;
		
	while (NULL != current->next)
	{
		next = current->next;	
		current->next = prev;
		prev = current;
		current = next;
	}
	
	current->next = prev;
	
	return current;
}

node_t *SLLGetNode(const node_t *head, match_func_ptr_t func_ptr, void *additional)
{
	node_t *runner = NULL;
	
	assert(NULL != head);
	assert(NULL != func_ptr);
	assert(NULL != additional);
	
	runner = (node_t *)head;
	
	while (NULL != runner && 0 == func_ptr(runner, additional))
	{
		runner = runner->next;
	}
	
	return runner;
}

int SLLForEach(node_t *head, action_func_ptr_t func_ptr, void *additional)
{
	node_t *runner = NULL;
	
	assert(NULL != head);
	assert(NULL != func_ptr);
	assert(NULL != additional);
	
	runner = head;
	
	while ((0 == func_ptr(runner, additional)) && (NULL != runner->next))
	{
		runner = runner->next;
	}
	
	return (NULL != runner->next);
}

int SLLHasLoop(const node_t *head)
{
	node_t *fast_runner = NULL, *slow_runner = NULL;
	
	assert(NULL != head);
	
	fast_runner = (node_t *)head->next;
	slow_runner = (node_t *)head;

	
	while (fast_runner->next != NULL && fast_runner != slow_runner)
	{
		slow_runner = slow_runner->next;
		fast_runner = fast_runner->next;
		if (fast_runner->next == NULL)
		{
			break;
		}
		fast_runner = fast_runner->next;
	}
	
	return slow_runner == fast_runner;
}

node_t *SLLFindIntersection(const node_t *head1, const node_t *head2)
{
	size_t size1 = 0, size2 = 0, difference = 0;
	const node_t *runner1 = NULL, *runner2 = NULL;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	size1 = SLLSize(head1);
	size2 = SLLSize(head2);
	runner1 = head1;
	runner2 = head2;
	
	if (size1 > size2)
	{
		difference = size1 - size2;
		
		while (difference > 0)
		{
			runner1 = runner1->next;
			--difference;
		}
	}
	else if (size2 > size1)
	{
		difference = size2 - size1;
		
		while (difference > 0)
		{
			runner2 = runner2->next;
			--difference;
		}
	}
	
	while (NULL != runner1->next)
	{
		if (runner1 == runner2)
		{
			return (node_t *)runner1;
		}
		runner1 = runner1->next;
		runner2 = runner2->next;
	}
	
	return (node_t *)runner1;
} 

node_t *SLLFlipRec(node_t *head)
{	
	node_t *new_head = NULL;
	
	if (head->next == NULL)
	{
		return head; 
	}
	
	new_head = SLLFlipRec(head->next);
	head->next->next = head;
	head->next = NULL;
		
	return new_head;
}                                 
