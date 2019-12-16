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

#include "sortedlist.h" /*sorted list API */
#include "priorityqueue.h" /* Priority queue API */

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

typedef struct Wrapper
{
	compare_func_ptr comp;
	void *param;	
} wrapper_t;

struct PQueue
{
	sll_t *pqueue;
	wrapper_t wrapper;
};

int PQCompareWrapper(const void *usr_data, const void *iter_data, void *wrapper_struct)
{
	wrapper_t *wrap = (wrapper_t *)wrapper_struct;
	
	assert(NULL != wrap);
	
	return (0 < wrap->comp((void *)usr_data, (void *)iter_data, wrap->param));	
}

pq_t *PQCreate(compare_func_ptr cmp_ptr, void *param)
{
	pq_t *pq = NULL;
	
	assert(NULL != cmp_ptr);
	
	pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == pq)
	{
		return NULL;
	}
	
	pq->wrapper.comp = cmp_ptr;
	pq->wrapper.param = param;
	pq->pqueue = SortLLCreate(&PQCompareWrapper, &pq->wrapper);
	
	return pq;	
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SortLLDestroy(pq->pqueue);
	FREE(pq);
}

void *PQDequeue(pq_t *pq)
{
	sll_iterator_t begin;
	void *data = NULL;
	assert(NULL != pq);
	
	begin = SLLBegin(pq->pqueue);
	data = SLLGetData(begin);
	SortLLRemove(begin);
	
	return data;
}

int PQEnqueue(pq_t *pq, void *data)
{
	sll_iterator_t iter;
	
	assert(NULL != pq);
	
	iter = SortLLInsert(pq->pqueue, data);
	
	return (SLLIsSameIter(iter, SLLEnd(pq->pqueue)));
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SLLGetData(SLLBegin(pq->pqueue));
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SLLSize(pq->pqueue);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SLLIsEmpty(pq->pqueue);
}

void PQClear(pq_t *pq)
{	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}	
}

void *PQErase(pq_t *pq, match_func m_ptr, void *param)
{
	void *data = NULL;
	sll_iterator_t iter;
	
	assert(NULL != pq);
	assert(NULL != m_ptr);
	
	iter = 
	SLLFindBy(pq->pqueue, SLLBegin(pq->pqueue), SLLEnd(pq->pqueue), m_ptr, param);
	data = SLLGetData(iter);
	
	if (!SLLIsSameIter(iter, SLLEnd(pq->pqueue)))
	{
		iter = SortLLRemove(iter);
	}
	
	return data;
}
