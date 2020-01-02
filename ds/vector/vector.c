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
	
	new_vector = (vector_t *)malloc(sizeof(vector_t));
	if (NULL == new_vector)
	{
		start = (void *)malloc(element_size * capacity);
		if (NULL == start)
		{
			return NULL; 
		}
		
		return NULL;
	} 
	
	new_vector->start = start;
	new_vector->size = 0;
	new_vector->capacity = capacity;
	new_vector->element_size = element_size;

	return new_vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->start); vector->start = NULL;
	free(vector); vector = NULL;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	assert(NULL != vector);

	vector->start = (void *)realloc(vector->start, new_capacity * 
											vector->element_size);
	if(NULL == vector->start)
	{
		return 1;
	}
	
	vector->capacity = new_capacity;
	
	return 0;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->capacity;
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size;
}

int VectorPushBack(vector_t *vector, const void *data)
{
	int status = 0;
	void *current = NULL;

	assert(NULL != vector);
	assert(NULL != data);
	
	if (vector->size == vector->capacity)
	{
		status = VectorReserve(vector, vector->capacity * GROWTH_FACTOR);
	}
	
	current = (char *)vector->start + (vector->size * 
										vector->element_size);
	memcpy(current, data, vector->element_size);
	++vector->size;
	
	return status;
}

void VectorPopBack(vector_t *vector)
{
	--vector->size;
	
	if (vector->size == vector->capacity / SHRINK_POINT)
	{
		VectorReserve(vector, vector->capacity / SHRINK_FACTOR);
	}
}

void *VectorGetItemAddress(const vector_t *vector, int position)
{
		return ((char *)vector->start + ((position - 1) * 
											vector->element_size));
}


