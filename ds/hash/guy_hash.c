#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dll.h"
#include "hash.h"

struct Hash 
{
    size_t table_size;
    match_func_t is_match;
    hash_func_t hash_func;
    dll_t *table[1];
};

/******************************************************************************/
/*                  Static Help Functions                                     */
/******************************************************************************/ 

static void InitDLLEntries(hash_t* hash);
static dll_t *GetList(const hash_t *table, const void *data);

/******************************************************************************/

hash_t *HashCreate(size_t table_size, hash_func_t hash_func, match_func_t is_match)
{
    hash_t *table = malloc(offsetof(hash_t, table) + (table_size * sizeof(dll_t*)));
    if (NULL != table)
    {
        table->table_size = table_size;
        table->is_match = is_match;
        table->hash_func = hash_func;
        InitDLLEntries(table);
    }
    
    return table;
}

void HashDestroy(hash_t *hash_table)
{
    size_t i = 0;
    
    assert(NULL != hash_table);
    
    for (i = 0; i < hash_table->table_size; ++i)
    {
        DLLDestroy(hash_table->table[i]);
    }
    
    free(hash_table); hash_table = NULL;
}

int HashInsert(hash_t *hash_table, void *data)
{
    dll_t *current = NULL;
    
    assert(NULL != hash_table);
    
    current = GetList(hash_table, data);
    
    return (DLLIsSameIter(DLLEnd(current), DLLPushBack(current, data)));
}

void HashRemove(hash_t *hash_table, const void *data)
{
    dll_t *current = NULL;
    
    assert(NULL != hash_table);
    
    current = GetList(hash_table, data);
    
    DLLRemove(DLLFind(DLLBegin(current), 
                      DLLEnd(current), 
                      hash_table->is_match, 
                      (void *)data));
}

void *HashFind(const hash_t *hash_table, const void *data)
{
    dll_t *current = NULL;
    void *found = NULL;
    
    assert(NULL != hash_table);
    
    current = GetList(hash_table, data);
    
    found = DLLGetData(DLLFind(DLLBegin(current), 
                       DLLEnd(current), 
                       hash_table->is_match, 
                       (void *)data));
    if (NULL != found)
    {
        HashRemove((hash_t *)hash_table, data);
        DLLPushFront(current, found);
    }                 
    
    return found;
}

int HashForeach(hash_t *hash_table, action_func_t action, void *param)
{
    int result = 0;
    size_t i = 0;
    
    assert(NULL != hash_table);
    
    for (i = 0; i < hash_table->table_size; ++i)
    {
        result = DLLForEach(DLLBegin(hash_table->table[i]), 
                             DLLEnd(hash_table->table[i]), 
                             action, 
                             param);
        if (0 != result)
        {
            break;
        }
    }
    
    return result;
}

size_t HashSize(const hash_t *hash_table)
{
    size_t size = 0 ,i = 0;
    
    assert(NULL != hash_table);
    
    for (i = 0; i < hash_table->table_size; ++i)
    {
        size += DLLSize(hash_table->table[i]);
    }
    
    return size;
}

int HashIsEmpty(const hash_t *hash_table)
{
    int result = 1;
    size_t i = 0;
    
    assert(NULL != hash_table);
    
    for (i = 0; (i < hash_table->table_size) &&  (0 != result) ; ++i)
    {
        result *= DLLIsEmpty(hash_table->table[i]);
    }
    
    return (0 != result);
}

/******************************************************************************/
static dll_t *GetList(const hash_t *table, const void *data)
{
    return table->table[(table->hash_func(data)) % (table->table_size)];
}

static void InitDLLEntries(hash_t* hash)
{
    size_t i = 0;
    
    for (i = 0; i < hash->table_size; ++i)
    {
        hash->table[i] = DLLCreate();
        
        if (NULL == hash->table[i])
        {
            for (--i; ; --i)
            {
                DLLDestroy(hash->table[i]);
            }
        }
    }
}
