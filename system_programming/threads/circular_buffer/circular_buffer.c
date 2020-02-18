#include <stddef.h> /* offsetof() */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /*assert() */

#include "./../../include/circular_buffer.h"

struct Cbuffer
{
	size_t read_index;
	size_t write_index;
	size_t capacity;
	int arr[1];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *cb = (cbuffer_t *)malloc
				(offsetof(cbuffer_t, arr) + (capacity * sizeof(int)));
	if (NULL == cb)
	{
		return NULL;
	}

	cb->read_index = 0;
	cb->write_index = 0;
	cb->capacity = capacity;

	return cb;
}

void CBufferDestroy(cbuffer_t *cb)
{
	assert(NULL != cb);

	free(cb);
	cb = NULL;
}

void CBufferWrite(cbuffer_t *cb , int num)
{
	assert(NULL != cb);
	
	cb->arr[cb->write_index] = num;
	++cb->write_index;
	cb->write_index %= cb->capacity;
}

int CBufferRead(cbuffer_t *cb)
{
	int curr_num = 0;

	assert(NULL != cb);

	curr_num = cb->arr[cb->read_index];
	++(cb->read_index);
	cb->read_index %= cb->capacity;

	return curr_num;
}

size_t CBufferCapacity(const cbuffer_t *cb)
{
	assert(NULL != cb);

	return cb->capacity;
}