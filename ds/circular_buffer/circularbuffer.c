/*********************************/
/*    Data Structures            */
/*    Bits Array                 */
/*    Author: Shye Shapira       */
/*    Reviewed By: RAZ  */
/*    Date:     26/11/2019       */
/*********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h> /* malloc */ 
#include <string.h> /* memcpy */
#include <sys/types.h> /* ssize_t */
#include <stddef.h> /* offsetof */

#include "circularbuffer.h" /* USER API */

#define OFFSET(type, member) offsetof(type, member)
#define FREE(x) free(x); x = NULL;

typedef char byte_t;

struct CBuffer 
{
	size_t read_index;
	size_t size;
	size_t capacity;
	byte_t arr[1];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *new_cb = (cbuffer_t *)malloc(OFFSET(cbuffer_t, arr) + capacity);
	if (NULL == new_cb)
	{
		return NULL;
	}
	
	new_cb->read_index = 0;
	new_cb->size = 0;
	new_cb->capacity = capacity;
	
	return new_cb;
}

void CBufferDestroy(cbuffer_t *cb)
{
	assert(NULL != cb);
	
	FREE(cb);
}

ssize_t CBufferRead(cbuffer_t *cb , void *buffer, size_t count)
{
	void *buff_run = buffer;
	size_t count_ret = count;
	
	assert(NULL != cb);
	assert(NULL != buffer);
	
	if (count > cb->size)
	{
		count = cb->size;
		count_ret = cb->size;
	}

	if (cb->capacity < (count + cb->read_index))
	{
		memcpy(buff_run, &cb->arr[cb->read_index], 
				cb->capacity - cb->read_index);
		count -= (cb->capacity - cb->read_index);
		buff_run = (byte_t *)buff_run + cb->capacity - cb->read_index;
		cb->read_index = 0;
	}
	
	memcpy(buff_run, &cb->arr[cb->read_index], count);
	cb->size -= count_ret;
	cb->read_index += count;
	
	return count_ret;
}

ssize_t CBufferWrite(cbuffer_t *cb ,const void *buffer, size_t count)
{
	const void *buff_run = buffer;
	size_t count_ret = count;
	size_t write_index = (cb->read_index + cb->size) % cb->capacity;

	assert(NULL != buffer);
	assert(NULL != cb);
	
	if ((cb->capacity - cb->size) < count)
	{
		count = cb->capacity - cb->size;
		count_ret = cb->capacity - cb->size;
	}

	if (cb->capacity < (count + write_index))
	{
		memcpy(&cb->arr[cb->read_index + cb->size], buff_run,
									cb->capacity - write_index);
		count -= (cb->capacity - write_index);
		buff_run = (byte_t *)buff_run + cb->capacity - write_index;
		cb->size += (cb->capacity - write_index);
		write_index = (cb->read_index + cb->size) % cb->capacity;
	}
	
	memcpy(&cb->arr[write_index], buff_run, count);
	cb->size += count_ret;
	
	return count_ret;
}

int CBufferIsEmpty(const cbuffer_t *cb)
{
	assert(NULL != cb);
	
	return (0 == cb->size);
}

size_t CBufferCapacity(const cbuffer_t *cb)
{
	assert(NULL != cb);
	
	return cb->capacity;
}

size_t CBufferFreeSpace(const cbuffer_t *cb)
{
	assert(NULL != cb);
	
	return (cb->capacity - cb->size);
}
