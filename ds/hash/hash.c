/*********************************
 *          SHYE SHAIRA          *
 *          20/01/2020           *
 *                               *
 *             HASH              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "dll.h" /*DLL API */
#include "hash.h" /* avl API */

#define FREE(ptr) free(ptr); ptr = NULL;

struct Hash
{
	size_t table_size;
	match_func_t is_match;
	hash_func_t hash_func;
	dll_t *table[1];
};

/**************************** STATIC **********************************/
static dll_t *HashCorectLocation(hash_t *hash_table, void *data)
{
	return hash_table->table
					[hash_table->hash_func(data) % hash_table->table_size];
}

static hash_t *InitTable(hash_t *hash)
{
	size_t i = 0, j = 0;
	
	assert(NULL != hash);
	
	for (i = 0; i < hash->table_size; ++i)
		{
			hash->table[i] = DLLCreate();
			if (NULL == hash->table[i])
			{
				for (j = 0; j < i; ++j)
				{
					DLLDestroy(hash->table[j]);
				}

				FREE(hash);

				return NULL;
			}
		}

		return hash;
}

/**************************** API *************************************/
hash_t *HashCreate(size_t table_size, hash_func_t hash_func, match_func_t is_match)
{
	hash_t *new_hash = 
	(hash_t *)malloc(offsetof(hash_t, table) + sizeof(dll_t *) * table_size);

 	if (NULL != new_hash)
 	{	
		assert(NULL != hash_func);
		assert(NULL != is_match);

		new_hash->table_size = table_size;
		new_hash->is_match = is_match;
		new_hash->hash_func = hash_func;
	}
	
	new_hash = InitTable(new_hash);
	
	return new_hash;
}

void HashDestroy(hash_t *hash_table)
{
	size_t i = 0;

	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; ++i)
	{
		DLLDestroy(hash_table->table[i]);
	}

	FREE(hash_table);
}

int HashInsert(hash_t *hash_table, void *data)
{
	iterator_t itr = NULL;

	assert(NULL != hash_table);

	itr = DLLPushFront(HashCorectLocation(hash_table, data), data);
	
	return (!itr);
}

void HashRemove(hash_t *hash_table, const void *data)
{
	assert(NULL != hash_table);
	
	DLLRemove(DLLFind(DLLBegin(HashCorectLocation((hash_t *)hash_table, (void *)data)), 
						DLLEnd(HashCorectLocation((hash_t *)hash_table, (void *)data)), 
						hash_table->is_match, 
						(void *)data));
}

void *HashFind(const hash_t *hash_table, const void *data)
{
	dll_t *bucket = NULL;
	void *found_data = NULL;

	assert(NULL != hash_table);

	bucket = HashCorectLocation((hash_t *)hash_table, (void *)data);

	found_data = DLLGetData(DLLFind(DLLBegin(bucket), 
							DLLEnd(bucket), 
							hash_table->is_match, 
							(void *)data));
	if (NULL != found_data)
	{
		HashRemove((hash_t *)hash_table, data);
		DLLPushFront(bucket, found_data);
	}
	
	return found_data;
}

int HashForeach(hash_t *hash_table, action_func_t action, void *param)
{
	iterator_t begin = NULL, end = NULL;
	size_t i = 0;
	int bool = 0;

	assert(NULL != hash_table);
	assert(NULL != action);

	for (i = 0; (i < hash_table->table_size) && (bool == 0); ++i)
	{
		begin = DLLBegin(hash_table->table[i]);
		end = DLLEnd(hash_table->table[i]);
		bool = DLLForEach(begin, end, action, param);		
	}

	return bool;
}

size_t HashSize(const hash_t *hash_table)
{
	size_t i = 0, size = 0;

	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; ++i)
	{
		size += DLLSize(hash_table->table[i]);
	}

	return size;
}

int HashIsEmpty(const hash_t *hash_table)
{
	size_t i = 0;

	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; ++i)
	{
		if (0 == DLLIsEmpty(hash_table->table[i]))
		{
			return 0;
		}
	}

	return 1;
}
