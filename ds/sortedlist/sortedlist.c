/********************************/
/*		data structures			*/
/* 		sorted linked list		*/
/*								*/
/*			Shye Shapira		*/
/*			10/12/2019			*/
/********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "sortedlist.h" /* sorted linked list API */

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

struct SLL
{
	dll_t *list;
	is_before is_before;
	void *param;
};

sll_t *SortLLCreate(is_before func, void *param)
{
	sll_t *sll = (sll_t *)malloc(sizeof(sll_t));
	if (NULL == sll)
	{
		return NULL;
	}
	
	sll->list = DLLCreate();
	sll->is_before = func;
	sll->param = param;
	
	return sll;
}

void SortLLDestroy(sll_t *sll)
{
	DLLDestroy(sll->list);
	FREE(sll);
}

static sll_iterator_t SLLRun(sll_t *sll, sll_iterator_t start, 
									sll_iterator_t end, void *data)
{
	sll_iterator_t iter = start;
	
	assert(NULL != sll);

	while (!(SLLIsSameIter(iter, end)))
	{
		if (sll->is_before(data, SLLGetData(iter), sll->param))
		{
			break;
		}
		
		iter = SLLNext(iter);
	}
	
	return iter;
}

sll_iterator_t SortLLInsert(sll_t *sll, void *data)
{
	sll_iterator_t iter;
	
	assert(NULL != sll);
	assert(NULL != data);
	
	iter.current = DLLBegin(sll->list);
	
	iter = SLLRun(sll, iter, SLLEnd(sll), data);
	
	iter.current = DLLInsert(sll->list, iter.current, data);
	if (NULL == iter.current)
	{
		return SLLEnd(sll);
	}
	
	return iter;
}

sll_iterator_t SLLFind(const sll_t *sll, const void *data, sll_iterator_t start,
															sll_iterator_t end)
{
	sll_iterator_t iter = start;
	
	assert(NULL != sll);
	assert(NULL != data);
	
	iter = SLLRun((sll_t *)sll, start, end, (void *)data);
	
	if (!(SLLIsSameIter(iter, start) && !(SLLIsSameIter(iter, end))))
	{
		if ((sll->is_before(SLLGetData(SLLPrev(iter)), data, NULL)) == 0) 
		{
			return SLLPrev(iter);
		}
	}
	
	return end;
}

sll_iterator_t SortLLRemove(sll_iterator_t it)
{
	it.current = DLLRemove(it.current);
	
	return it;
}

int SLLIsEmpty(const sll_t *sll)
{
	assert(NULL != sll);
	
	return DLLIsEmpty(sll->list);
}

size_t SLLSize(const sll_t *sll)
{
	assert(NULL != sll);
	
	return DLLSize(sll->list);
}

sll_iterator_t SLLBegin(sll_t *sll)
{
	sll_iterator_t iter;
	
	assert(NULL != sll);
	
	iter.current = DLLBegin(sll->list);
	
	return iter;
}

sll_iterator_t SLLEnd(sll_t *sll)
{
	sll_iterator_t iter;
	
	assert(NULL != sll);
	
	iter.current = DLLEnd(sll->list);
	
	return iter;
}

sll_iterator_t SLLNext(sll_iterator_t it)
{
	it.current = DLLGetNext(it.current);
	
	return it;
}

sll_iterator_t SLLPrev(sll_iterator_t it)
{
	it.current = DLLGetPrev(it.current);
	
	return it;
}

void *SLLGetData(sll_iterator_t it)
{
	return DLLGetData(it.current);
}

int SLLIsSameIter(const sll_iterator_t it1, const sll_iterator_t it2)
{
	return DLLIsSameIter(it1.current, it2.current);
}

void* SLLPopBack(sll_t *sll)
{
	assert(NULL != sll);
	
	return DLLPopBack(sll->list);
}

void* SLLPopFront(sll_t *sll)
{
	assert(NULL != sll);
	
	return DLLPopFront(sll->list);
}

int SLLForEach(sll_iterator_t start, sll_iterator_t end, action_func_ptr a_ptr, 
																	void *ap)
{
	return DLLForEach(start.current, end.current, a_ptr, ap);
}

sll_iterator_t SLLFindBy(const sll_t *sll, sll_iterator_t start , sll_iterator_t 
									end, match_func_ptr m_ptr ,const void *data)
{
	sll_iterator_t iter;
	
	UNUSED(sll);

	iter.current = DLLFind(start.current, end.current, m_ptr, (void *)data);
	
	return iter;
}

void SLLMerge(sll_t *dest, sll_t *src)
{
	sll_iterator_t iter_dst, iter_src_start, iter_src_end, iter_dst_next;
	sll_iterator_t src_end, dst_end; 
	
	assert(NULL != src);
	assert(NULL != dest);
	
	iter_dst = SLLBegin(dest);
	iter_dst_next = SLLBegin(dest);
	iter_src_start = SLLBegin(src);
	iter_src_end = SLLBegin(src);
	
	src_end = SLLEnd(src);
	dst_end = SLLEnd(dest);
	
	while (!(SLLIsSameIter(iter_src_end, SLLEnd(src))))
	{		
		iter_dst = 
		SLLPrev(SLLRun(dest, iter_dst, dst_end, SLLGetData(iter_src_end)));
		
		iter_dst_next = SLLNext(iter_dst);
		
		if (SLLIsSameIter(iter_dst_next, SLLEnd(dest)))
		{
			iter_src_end = SLLNext(iter_src_end);
		}
		else
		{
			iter_src_end = 
			SLLRun(src, iter_src_end, src_end, SLLGetData(iter_dst_next));
		}
									
		DLLSplice(iter_src_start.current, iter_src_end.current, 
													iter_dst.current);
		
		iter_src_start = iter_src_end;
		iter_dst = iter_dst_next;
	}
}
