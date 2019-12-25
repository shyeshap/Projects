/*********************************/
/*    Data Structures            */
/*    Variant Size Allocator     */       
/*    Author: Shye Shapira       */
/*    Date: 21/12/2019           */
/*                               */
/*********************************/

#include <assert.h> /* assert */

#include "vsa.h"

#define DEADBEEF 0xDEADBEEF
#define END 0x80000000
#define HEADER_SIZE sizeof(block_t)

typedef char *byte_ptr_t;

struct BlockHeader
{
	long block_size;
	
	#ifndef NDBUG
	
	long magic_number;
	
	#endif 
};

typedef struct BlockHeader block_t;

vsa_t *VSAInit(void *allocated, size_t segment_size)
{
	vsa_t *vsa = allocated;
	block_t *end_block = NULL;
	
	assert(NULL != allocated);
	
	vsa->block_size = (long)(segment_size - (2 * HEADER_SIZE));
	
	end_block = (block_t *)((byte_ptr_t)vsa + segment_size - HEADER_SIZE);
	end_block->block_size = END;
	
	#ifndef NDBUG
	
	vsa->magic_number = DEADBEEF;
	end_block->magic_number = DEADBEEF;
	
	#endif
	
	return vsa;
}

static void MergeBlocks(block_t *block_header)
{
	block_t *block_runner = block_header;
	size_t free_size_sum = 0;
	
	assert(NULL != block_header);
	
	free_size_sum = 0;
	
	while (block_runner->block_size > 0 && block_runner->block_size != END)
	{
		free_size_sum += block_runner->block_size + HEADER_SIZE;
		block_runner = (block_t *)
			((byte_ptr_t)block_runner + HEADER_SIZE + block_runner->block_size);
	}
	
	block_header->block_size = free_size_sum - HEADER_SIZE;
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_t *block_runner = (block_t *)vsa;
	block_t *next_block_header = NULL;
	
	assert(NULL != vsa);
	
	while(block_runner->block_size != END)
	{
		if (0 > block_runner->block_size)
		{
			block_runner = (block_t *)((byte_ptr_t)block_runner + HEADER_SIZE
										+ (block_runner->block_size * -1));
			continue;
		}	
		
		MergeBlocks(block_runner);
			
		if (block_runner->block_size >= (long)(block_size + HEADER_SIZE))
		{
			next_block_header = (block_t *)
						((byte_ptr_t)block_runner + block_size + HEADER_SIZE);
			next_block_header->block_size = 
						block_runner->block_size - block_size - HEADER_SIZE;
			block_runner->block_size = -block_size;
			
			#ifndef NDBUG
			next_block_header->magic_number = DEADBEEF;
			#endif
			
			return (byte_ptr_t)block_runner + HEADER_SIZE;
		}
		
		block_runner = (block_t *)((byte_ptr_t)block_runner + HEADER_SIZE
										+ block_runner->block_size);
	}
	
	return NULL;
}

void VSAFree(void *block)
{
	block_t *runner = (block_t *)block;
	
	assert(NULL != block);
	
	runner = (block_t *)((byte_ptr_t)runner - HEADER_SIZE);
	
	assert(runner->magic_number == DEADBEEF);
	
	runner->block_size *= -1;
}

size_t VSALargestChunkSize(vsa_t *vsa)
{
	block_t *block_runner = (block_t *)vsa;
	size_t largest = 0;
	
	assert(NULL != vsa);
	
	while(block_runner->block_size != END)
	{
		if (0 > block_runner->block_size)
		{
			block_runner = (block_t *)((byte_ptr_t)block_runner + HEADER_SIZE
										+ (block_runner->block_size * -1));
			continue;
		}
		
		MergeBlocks(block_runner);
		
		if ((long)largest < block_runner->block_size)
		{
			largest = block_runner->block_size;
		}
		
		block_runner = (block_t *)((byte_ptr_t)block_runner + HEADER_SIZE
										+ block_runner->block_size);
	}
	
	return largest;
}
