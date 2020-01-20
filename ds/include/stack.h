/*********************************/
/*    Data Structures            */
/*    Stack                      */       
/*    Author : Shye Shapira      */
/*    Reviewed By: Itay          */
/*    Date:     /11/2019         */
/*                               */
/*********************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef struct Stack stack_t;

/* creates new Stack */
stack_t* StackCreate(size_t element_size, size_t capacity);

/* destroy the Stack */
void StackDestroy(stack_t* mystack);

/* push given element to the top of the Stack */
int StackPush(stack_t* mystack, const void* data); /* 1 success, 0 fail */

/* pop the element that is on the top of the Stack and remove it */
void *StackPop(stack_t* mystack);

/* checkes if the Stack is empty */
int StackIsEmpty(const stack_t* mystack); /* 1 is empty, 0 not empty */

/* return the number of elements in the stack */
size_t StackSize(const stack_t* mystack);

/* returns the top most elemet on the Stack */
void* StackPeek(const stack_t* mystack);

void StackSortRec(stack_t *stack);

#endif
