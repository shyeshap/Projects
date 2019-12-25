/************************************/
/*		FIX SIZE ALLOCATOR			*/
/*									*/
/*			Shye Shapira			*/
/*			18/12/2019				*/
/************************************/

#include <sys/types.h>	/* size_t */
#include <assert.h> 	/* assert */

#include "fsa.h"

#define WORD_SIZE 8
#define SIZEOF_HEADER sizeof(block_header_t)
#define SIZEOF_FSA sizeof(fsa_t)

typedef char *byte_ptr_t;

struct FixedSizeAllocator
{
	size_t next_available_index;
	size_t block_size;
	size_t segment_size;
};

typedef struct BlockHeader 
{
	size_t next_free_index;	
} block_header_t;

static size_t AlignedBlockSize(const size_t block_size)
{
	size_t align = block_size / WORD_SIZE;
	
	if (block_size % WORD_SIZE != 0)
	{
		++align;
	}
	
	return ((WORD_SIZE * align) + SIZEOF_HEADER);
}

size_t FSASuggestSize(const size_t blocks_count, const size_t block_size)
{
	return (sizeof(fsa_t) + (AlignedBlockSize(block_size) * blocks_count));
}

fsa_t *FSAInit(void *allocated, const size_t segment_size, const size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t next_free = SIZEOF_FSA;
	block_header_t *header_runner = NULL;
	
	assert(NULL != allocated);
	
	fsa = (fsa_t *)allocated;
	fsa->block_size = AlignedBlockSize(block_size);
	fsa->next_available_index = SIZEOF_FSA;
	fsa->segment_size = segment_size;
	
	header_runner = (block_header_t *)((byte_ptr_t)allocated + SIZEOF_FSA);
		
	while (next_free < segment_size)
	{	
		next_free += fsa->block_size;
		header_runner->next_free_index = next_free;
		header_runner = (block_header_t *)((byte_ptr_t)header_runner + 
						fsa->block_size);
	}
	
	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	size_t temp_next_available = 0;
	block_header_t *current_header = NULL;
	
	assert(NULL != fsa);
	
	temp_next_available = fsa->next_available_index;
	current_header = (block_header_t *)((byte_ptr_t)fsa + 
										fsa->next_available_index);
	fsa->next_available_index = current_header->next_free_index;
	current_header->next_free_index = temp_next_available;
	
	return ((byte_ptr_t)current_header + SIZEOF_HEADER);
}

void FSAFree(void *block)
{
	block_header_t *current_header = NULL;
	size_t current_block_index = 0;
	fsa_t *fsa = NULL;
	
	assert(NULL != block);
	
	current_header = (block_header_t *)((byte_ptr_t)block - SIZEOF_HEADER);
	current_block_index = current_header->next_free_index;
	fsa = (fsa_t *)((byte_ptr_t)block - SIZEOF_HEADER - current_block_index);
	current_header->next_free_index = fsa->next_available_index;
	fsa->next_available_index = current_block_index;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t counter = 0;
	block_header_t *block_runner = NULL;
	size_t next_avalable = 0;
	
	assert(NULL != fsa);
	
	block_runner = 
				(block_header_t *)((byte_ptr_t)fsa + fsa->next_available_index);
	next_avalable = fsa->next_available_index;
				
	while (next_avalable != fsa->segment_size)
	{
		next_avalable =  block_runner->next_free_index;
		++counter;
		block_runner = 
			(block_header_t *)((byte_ptr_t)fsa + block_runner->next_free_index);
	}
	
	return counter;
}
