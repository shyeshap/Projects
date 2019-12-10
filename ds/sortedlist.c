/********************************/
/*		data structures			*/
/* 		sorted linked list		*/
/*								*/
/*			Shye Shapira		*/
/*			10/12/2019			*/
/********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "dllist.h" /* API */ 

#define FREE(ptr) free(ptr); ptr = NULL;

sll_t *SortLLCreate(is_before func, void *param)
{

}

void SortLLDestroy(sll_t *sll)
{
	DLLDestroy(sll);
}

sll_iterator_t SortLLinsert(sll_t *sll, void *data)
{

}

sll_iterator_t SortLLRemove(sll_iterator_t it)
{
	return DLLRemove(it);
}

int SLLIsEmpty(const sll_t *sll)
{
	DLLIsEmpty(sll);
}

size_t SLLSize(const sll_t *sll)
{
	DLLSize(sll);
}

sll_iterator_t SLLBegin(sll_t *sll)
{
	DLLBegin(sll);
}

sll_iterator_t SLLEnd(sll_t *sll)
{
	DLLEnd(sll);
}

sll_iterator_t SLLNext(sll_iterator_t it)
{
	return DLLGetNext(it);
}

sll_iterator_t SLLPrev(sll_iterator_t it)
{
	return DLLGetPrev(it);
}

void *SLLGetData(sll_iterator_t it)
{
	return DLLGetData(it);
}

int SLLIsSameIter(const sll_iterator_t it1, const sll_iterator_t it2)
{
	return DLLIsSameIter(it1, it2);
}

void* SLLPopBack(sll_t *sll)
{
	return DLLPopBack(sll);
}

void* SLLPopFront(sll_t *sll)
{
	return DLLPopFront(sll);
}

int SLLForEach(sll_iterator_t start, sll_iterator_t end, action_func_ptr a_ptr, void *ap)
{

}

sll_iterator_t SLLFind(const sll_t *sll, const void *data, sll_iterator_t start, sll_iterator_t end)
{

}

sll_iterator_t SLLFindBy(const sll_t *sll, sll_iterator_t start , sll_iterator_t end

                                        match_func_ptr m_ptr ,const void *data)
{

}

void SLLMerge(sll_t *dest, sll_t *src)
{

}
