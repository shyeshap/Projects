/*********************************/
/*    Data Structures            */
/*    Vector                     */       
/*    Author :                   */
/*    Reviewed By:               */
/*    Date:      /11/2019        */
/*                               */
/*********************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct Vector vector_t;

/* creates the vector */
/* only positive parameters */
vector_t *VectorCreate(size_t element_size, size_t capacity);

/* destroy the vector */
/* Warning: the function doesn't get NULL pointer */
void VectorDestroy(vector_t *vector);

/* push new item at the end of the vector */
/* 0 - success , 1- failure */
/* Warning: Could resize the capacity in an unpredictable manner */
/* Warning: the function doesn't get NULL pointer */
int VectorPushBack(vector_t *vector, const void *data);

/* pops the last item in the vector */
/* Warning: the function doesn't get NULL pointer */
/* WORNING! undefined behavior for empty list */
void VectorPopBack(vector_t *vector);

/* resizing the vector size as needed with extra space */
/* 0 - success , 1- failure */
/* Warning: the function doesn't get NULL pointer */
/* undefined behavior for new capacity in size 0 */
int VectorReserve(vector_t *vector, size_t new_capacity);

/* This function return the total size of the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorCapacity(const vector_t *vector);

/* This function return the current number of elements in the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorSize(const vector_t *vector);

/* This function return specific item address to the user */
/* Warning: undefined behavior for position over size or under 1 */
/* Warning: the function doesn't get NULL pointer */
void *VectorGetItemAddress(const vector_t *vector, size_t position);

#endif
