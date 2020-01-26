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

#include "./../include/vector.h" /* vector array API */
#include "./../include/priorityq.h" /* Priority queue API */
#include "./../include/heapify.h" /* heapify API */

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

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

int PQCompareWrapper(const void *usr_data, const void *iter_data, void *wrapper_struct)
{
	
}

pq_t *PQCreate(compare_func_ptr cmp_ptr, void *param)
{
	pq_t *new_pq;

	assert(NULL != cmp_ptr);
	assert(NULL != param);

	new_pq = (pq_t *)malloc(sizeof(*new_pq));
	if (NULL != new_pq)
	{
		new_pq->pqueue = VectorCreate(sizeof(void *), 1);
		if (NULL == new_pq->pqueue)
		{
			FREE(new_pq);

			return NULL;
		}
		
		new_pq->wrapper.comp = cmp_ptr;
		new_pq->wrapper.param = param;
	}
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);

	VectorDestroy(pq->pqueue);
	FREE(pq);
}

void *PQDequeue(pq_t *pq)
{
	
}

int PQEnqueue(pq_t *pq, void *data)
{
	int status = 0;
	size_t size = 0;

	assert(NULL != pq);

	status = VectorPushBack(pq->pqueue, &data);

	if (0 == status)
	{
		size = PQSize(pq);
		HeapifyUp(pq->queue, size, VectorGetItemAddress(pq->queue, size), 
							sizeof(void *), pq->wrapper.comp, pq->wrapper.param);
	}

	return status;
}

void *PQPeek(const pq_t *pq)
{
	return VectorGetItemAddress(pq->pqueue, 1);
}

size_t PQSize(const pq_t *pq)
{
	return VectorSize(pq->pqueue);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return 0 == VectorSize(pq->pqueue);
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

	assert(NULL != pq);
	assert(NULL != match_func);

	for (i = 0; i < size && match_func(data, pq->pqueue); ++i)
	{
		pq->pqueue;
	}
}

void PQSwap(void **node1, void **node2)
{
	void *tmp = NULL;

	assert(NULL != node1);
	assert(NULL != node2);

	tmp = *node1;
	*node1 = *node2;
	node2 = tmp;
}
