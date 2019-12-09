#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */

#include "dllist.h"

#define FREE(x) free(x); x = NULL;

typedef struct DLLNode
{
	void *data;
	struct DLLNode *next;
	struct DLLNode *prev;
} DLLnode_t;

struct DLL
{
	struct DLLNode head;
	struct DLLNode tail;
};

dll_t *DLLCreate()
{
	dll_t *new_dll = (dll_t *)malloc(sizeof(dll_t));
	if (NULL == new_dll)
	{
		return NULL;
	}
	
	new_dll->head.prev = NULL;
	new_dll->tail.next = NULL;
	new_dll->head.next = &new_dll->tail;
	new_dll->tail.prev = &new_dll->head;
	
	return new_dll;
}

void DLLDestroy(dll_t *dll)
{
	DLLnode_t *runner = dll->head.next;
	
	assert(NULL != dll);
	
	while (NULL != runner->next)
	{
		runner = runner->next;
		FREE(runner->prev);
	}
	
	FREE(dll);
}

iterator_t DLLBegin(const dll_t *dll)
{
	iterator_t it;
	
	assert(NULL != dll);
	
	it = dll->head.next;
	
	return it; 
}

iterator_t DLLEnd(const dll_t *dll)
{
	iterator_t it;
	
	assert(NULL != dll);
	
	it = (DLLnode_t *)&dll->tail;
	
	return it;
}

iterator_t DLLInsert(dll_t *dll, iterator_t it, void *data)
{
	DLLnode_t *new_node = (DLLnode_t *)malloc(sizeof(DLLnode_t));
	if (NULL == new_node)
	{
		return DLLEnd(dll);
	}
	
	new_node->data = data;
	new_node->prev = it->prev;
	new_node->next = it;
	it->prev->next = new_node;
	it->prev = new_node;
	
	it = new_node;
	
	return it;
}

iterator_t DLLRemove(iterator_t it)
{
	iterator_t new_it;
	
	new_it = it->next;
	it->next->prev = it->prev;
	it->prev->next = it->next;
	
	FREE(it);
	
	return new_it;
}

iterator_t DLLGetNext(iterator_t it)
{
	it = it->next;
	
	return it;
}

iterator_t DLLGetPrev(iterator_t it)
{
	it = it->prev;
	
	return it;
}

int DLLIsEmpty(const dll_t *dll)
{
	return dll->head.next == &dll->tail;
}

size_t DLLSize(const dll_t *dll)
{
	size_t count = 0;
	iterator_t runner;
	runner = dll->head.next;
	
	while (runner->next != dll->tail.next)
	{
		++count;
		runner = runner->next;
	}
	
	return count;
}

void *DLLGetData(iterator_t it)
{
	return it->data;
}

int DLLIsSameIter(const iterator_t it1, const iterator_t it2)
{
	return it1 == it2;
}

iterator_t DLLPushBack(dll_t *dll, void *data)
{
	iterator_t it = DLLEnd(dll);
	
	it = DLLInsert(dll, it, data);
	
	return it;
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
	iterator_t it = DLLBegin(dll);

	it = DLLInsert(dll, it, data);
	
	return it;
}

void *DLLPopFront(dll_t *dll)
{
	void *data = dll->head.next->data;
	iterator_t it = DLLBegin(dll);
		
	assert(NULL != dll);
		
	DLLRemove(it);
	
	return data;
}

void *DLLPopBack(dll_t *dll)
{
	void *data = dll->tail.prev->data;
	iterator_t it = DLLGetPrev(DLLEnd(dll));
	
	assert(NULL != dll);
	
	DLLRemove(it);
	
	return data;
}

iterator_t DLLSplice(iterator_t start, iterator_t end, iterator_t where)
{
	start->prev->next = end;
	end->prev->next = where->next;
	where->next->prev = end->prev;
	end->prev = start->prev;
	start->prev = where;
	where->next = start;
	
	return where;
}

int DLLForEach(iterator_t start, iterator_t end, action_func_ptr a_ptr, void *ap)
{
	iterator_t runner = start;

	assert(NULL != ap);
	
	while (end != runner)
	{
		if (0 == a_ptr(runner->data, ap))
		{
			runner = DLLGetNext(runner);
		}
		else
		{
			return 1;
		}
	}
	
	return ((end != runner) );
}

iterator_t DLLFind(iterator_t start, iterator_t end, match_func_ptr m_ptr, void *ap)
{
	iterator_t runner = start;

	assert(NULL != ap);
	
	while ((0 == m_ptr(runner->data, ap)) && (end != runner))
	{
		runner = runner->next;
	}
	
	return runner;
}
