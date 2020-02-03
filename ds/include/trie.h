#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */

typedef enum Status
{
    SUCCESS,
    FAIL
} status_t;

typedef enum Bool
{
    FALSE,
    TRUE
} bool_t;

typedef struct Trie trie_t;

/*
* TrieCreate() - 
* Returns pointer to the Trie, will return NULL if failed. 
* complexity of malloc();       
*/
trie_t *TrieCreate(size_t height);

/*
* TrieDetroy() -
* Destroys and frees Trie from memory.
* undefined behaviour for @trie NULL pointer
* complexity: free();                  
*/
void TrieDestroy(trie_t *trie);

/*
* TrieInsert() -
* Inserts a new trie element.
* undefined behaviour for @trie NULL pointer
* complexity: malloc();                  
*/
status_t TrieInsert(trie_t *trie, unsigned char *data);

/*
* TrieIsEmpty() -
* Checks if the trie is empty.
* undefined behaviour for @trie NULL pointer
* return value:
    -TRUE
    -FALSE
* complexity: O(1);                  
*/
bool_t TrieIsEmpty(const trie_t *trie);

/*
* TrieCountEdges() -
* Counts the number of edges in the trie.
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
size_t TrieCountEdges(const trie_t *trie);

/*
* TrieCountLeafs() -
* Counts the number of leafs in the trie.
* undefined behaviour for @trie NULL pointer
* complexity: O(n);                  
*/
size_t TrieCountOccupiedLeafs(const trie_t *trie);

/*
* TrieFreeNode() - 
* updates the availability of node to be freed and its ansestors.
* undefined behaviour for @trie NULL pointer
* undefined behaviour for @data NULL pointer or not leaf path.
* complexity: O(n)
*/
void TrieFreeLeaf(trie_t *trie, unsigned char *data);

/*
* TrieIsAvailable()
* Check if node is available
* undefined behaviour for @trie NULL pointer.
* undefined behaviour for @data NULL pointer.
* complexity: O(n)
*/
bool_t TrieIsAvailable(trie_t *trie, unsigned char *data);
/*
* TrieFindFirstAvailable()
* find lowest available root in trie; 
* undefined behaviour for @trie NULL pointer.
* undefined behaviour for @data NULL pointer.
* complexity: O(n)
*/
void TrieFindFirstAvailable(trie_t *trie, unsigned char *ip);

#endif 

