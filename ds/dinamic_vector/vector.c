/*********************************/
/*    Data Structures            */
/*    Vector                     */       
/*    Author :  SHYE             */
/*    Reviewed By: YONATAN       */
/*    Date:     1/12/2019        */
/*                               */
/*********************************/

#include <stdlib.h> /* malloc, realloc */
#include <string.h> /* memmov */
#include <assert.h> /* assert */

#include "vector.h" /* vector data structure functions */

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 2
#define SHRINK_POINT 4

struct Vector{
	void *start;
	size_t size;
	size_t capacity;
	size_t element_size;
};

vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	void *start = NULL;
	vector_t *new_vector = NULL;
	
	if (0 == element_size || 0 == capacity)
	{
		return NULL;
	}
	else
	{
		new_vector = (vector_t *)malloc(sizeof(vector_t));
		if (NULL == new_vector)
		{
			return NULL;
		} 
		start = (void *)malloc(element_size * capacity);
		if (NULL == start)
		{
			return NULL; 
		}
		
		new_vector->start = start;
		new_vector->size = 0;
		new_vector->capacity = capacity;
		new_vector->element_size = element_size;
	}

	return new_vector;
}

void VectorDestroy(vector_t *myvector)
{
	assert(NULL != myvector);
	
	free(myvector->start); myvector->start = NULL;
	free(myvector); myvector = NULL;
}

int VectorReserve(vector_t *myvector, size_t new_capacity)
{
	assert(NULL != myvector);
	
	if (new_capacity > 0)
	{
		myvector->start = (void *)realloc(myvector->start, new_capacity * 
													myvector->element_size);
		if(NULL == myvector->start)
		{
			return 1;
		}
		
		myvector->capacity = new_capacity;
		
		return 0;
	}
	else
	{
		return 1;
	}
}

size_t VectorCapacity(const vector_t *myvector)
{
	assert(NULL != myvector);
	
	return myvector->capacity;
}

size_t VectorSize(const vector_t *myvector)
{
	assert(NULL != myvector);
	
	return myvector->size;
}

int VectorPushBack(vector_t *myvector, const void *data)
{
	int status = 0;
	void *current = NULL;

	assert(NULL != myvector);
	assert(NULL != data);
	
	if (myvector->size == myvector->capacity)
	{
		status = VectorReserve(myvector, myvector->capacity * GROWTH_FACTOR);
	}
	
	current = (char *)myvector->start + (myvector->size * 
										myvector->element_size);
	memmove(current, data, myvector->element_size);
	++myvector->size;
	
	return status;
}

void VectorPopBack(vector_t *myvector)
{
	if (myvector->size > 0)
	{
		--myvector->size;
	
		if (myvector->size == myvector->capacity / SHRINK_POINT)
			{
				VectorReserve(myvector, myvector->capacity / SHRINK_FACTOR);
			}
	}
}

void *VectorGetItemAddress(const vector_t *myvector, int position)
{
	if ((position > myvector->size) || (position == 0))
	{
		return NULL;
	}
	else
	{
		return ((char *)myvector->start + ((position - 1) * 
											myvector->element_size));	
	}
}


