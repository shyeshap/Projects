/********************************/
/*	    data structures			*/
/* 		 priority queue			*/
/*								*/
/*			Shye Shapira		*/
/*			10/12/2019			*/
/********************************/

#include <stdio.h> /* sizeof() */
#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "vector.h" /* vector array API */
#include "priorityq.h" /* Priority queue API */
#include "heapify.h" /* heapify API */

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;
#define MIN_CAPACITY 1
#define POSITION(index) (index + 1)
#define RIGHT_CHILD_INDEX(index) (POSITION(index) * 2)
#define LEFT_CHILD_INDEX(index) (RIGHT_CHILD_INDEX(index) - 1)
#define PARENT_INDEX(index) (POSITION(index) / 2)

enum status
{
	SUCCESS,
	FAIL
};

typedef struct Wrapper
{
	compare_func_ptr comp;
	void *param;	
} wrapper_t;

struct PQueue
{
	vector_t *pqueue;
	wrapper_t wrapper;
};

static void Swap(void **ptr1, void **ptr2);

static void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size,
                                             compare_func_ptr cmp, void *param);

static void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size,
                                               compare_func_ptr cmp, void *param);

/****************************************************************************************/

pq_t *PQCreate(compare_func_ptr cmp_ptr, void *param)
{
	pq_t *new_pq = NULL;

	assert(NULL != cmp_ptr);

	new_pq = (pq_t *)malloc(sizeof(*new_pq));
	if (NULL != new_pq)
	{
		new_pq->pqueue = VectorCreate(sizeof(void *), MIN_CAPACITY);
		if (NULL == new_pq->pqueue)
		{
			FREE(new_pq);

			return NULL;
		}
		
		new_pq->wrapper.comp = cmp_ptr;
		new_pq->wrapper.param = param;
	}

	return new_pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);

	VectorDestroy(pq->pqueue);
	FREE(pq);
}

void *PQDequeue(pq_t *pq)
{
	void **last = NULL, **root = NULL, *removed = NULL;

	assert(NULL != pq);

	last = VectorGetItemAddress(pq->pqueue, PQSize(pq));
	root = VectorGetItemAddress(pq->pqueue, 1);
	removed = *root;
	Swap(root, last);
	VectorPopBack(pq->pqueue);
	HeapifyDown(pq->pqueue, PQSize(pq), 0, sizeof(void *), 
					pq->wrapper.comp, pq->wrapper.param);

	return removed;
}

int PQEnqueue(pq_t *pq, void *data)
{
	size_t size = 0;

	assert(NULL != pq);

	if (0 == VectorPushBack(pq->pqueue, &data))
	{
		size = PQSize(pq);
		HeapifyUp(pq->pqueue, size, size - 1, sizeof(void *), 
						pq->wrapper.comp, pq->wrapper.param);

		return SUCCESS;
	}

	return FAIL;
}

void *PQPeek(const pq_t *pq)
{
	void **ret = NULL; 

	assert(NULL != pq);

	ret = VectorGetItemAddress(pq->pqueue, 1);
	
	return *ret;
}

size_t PQSize(const pq_t *pq)
{
	return VectorSize(pq->pqueue);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return (0 == VectorSize(pq->pqueue));
}

void PQClear(pq_t *pq)
{	
	assert(NULL != pq);

	while (!PQIsEmpty(pq))
	{
		VectorPopBack(pq->pqueue);
	}
}

void *PQErase(pq_t *pq, match_func match_func, void *data)
{
	size_t i = 0;
	size_t size = PQSize(pq);
	void **curr = NULL, **last = NULL;
	void *ret = NULL;

	assert(NULL != pq);
	assert(NULL != match_func);

	last = VectorGetItemAddress(pq->pqueue, PQSize(pq));

	for (i = 0; i < size; ++i)
	{
		curr = VectorGetItemAddress(pq->pqueue, i + 1);

		if (1 == match_func(data, *curr))
		{
			ret = *curr;
			Swap(curr, last);
			VectorPopBack(pq->pqueue);
			HeapifyDown(pq->pqueue, PQSize(pq), i, sizeof(void *), 
								pq->wrapper.comp, pq->wrapper.param);
			HeapifyUp(pq->pqueue, PQSize(pq), i, sizeof(void *), 
								pq->wrapper.comp, pq->wrapper.param);
			break;
		}
	}

	return ret;
}

/*******************************************************************************************/

static void Swap(void **ptr1, void **ptr2)
{
	void *tmp = NULL;

	assert(NULL != ptr1);
	assert(NULL != ptr2);

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;	
}

static void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size,
                                             compare_func_ptr cmp, void *param)
{
	void **new_data = NULL;
	void **parent = NULL;

	assert(NULL != arr);
	assert(NULL != cmp);

	UNUSED(size);
	UNUSED(element_size);

	while (0 < index)
	{
		new_data = VectorGetItemAddress(arr, POSITION(index));
		parent = VectorGetItemAddress(arr, PARENT_INDEX(index));

		if (0 <= cmp(*new_data, *parent, param))
		{
			Swap(parent, new_data); 
			index = (index - 1) / 2;
			new_data = parent;
			parent = VectorGetItemAddress(arr, PARENT_INDEX(index));
		}

		else
		{
			break;
		}
	}
}

static void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size,
                                               compare_func_ptr cmp, void *param)
{
	void **left_child = NULL, **right_child = NULL, **parent = NULL, **bigger_ptr = NULL;
	size_t left_child_indx = LEFT_CHILD_INDEX(index), right_child_indx = RIGHT_CHILD_INDEX(index), 
			bigger = 0;

	UNUSED(size);
	UNUSED(element_size);

	assert(NULL != arr);
	assert(NULL != cmp);

	while ((1 < size) && (left_child_indx < size))
	{
		parent = VectorGetItemAddress(arr, POSITION(index));
		left_child = VectorGetItemAddress(arr, POSITION(left_child_indx));
		right_child = VectorGetItemAddress(arr, POSITION(right_child_indx));
		
		if (0 <= cmp(*left_child, *parent, param))
		{
			bigger = left_child_indx;
		}

		else
		{
			bigger = index;
		}

		if ((right_child_indx < size) && (0 <= cmp(*right_child, *left_child, param)))
		{
			bigger = right_child_indx;
		}

		if (bigger != index)
		{
			bigger_ptr = VectorGetItemAddress(arr, POSITION(bigger));
			Swap(bigger_ptr, parent);
			index = bigger;
			right_child_indx = RIGHT_CHILD_INDEX(index);
			left_child_indx = LEFT_CHILD_INDEX(index);
		}
		
		else
		{
			break;
		}
	}
}