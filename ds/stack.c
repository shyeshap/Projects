#include <stdio.h> /* typedef */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "stack.h" /* stack ds */


struct Stack
{
	void *start;
	void *current;
	void *end;
	size_t element_size;
};

stack_t *StackCreate(size_t element_size, size_t capacity)
{
	stack_t *newstack = (stack_t *) malloc (sizeof(stack_t)); 
	if(NULL == newstack)
	{
		return NULL;
	}
	
	newstack->element_size = element_size;
	
	newstack->start = (void *) malloc (element_size * capacity);
	if(NULL == newstack->start)
	{
		return NULL;
	}
	
	newstack->current = newstack->start;
	newstack->end = (char *)(newstack->start) + (element_size * capacity);

	return newstack;
}

int StackPush(stack_t *stack, void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	
	if (stack->current == stack->end)
	{
		return 0;
	}
	else
	{
		memcpy(stack->current, data, stack->element_size);
		stack->current = (char *)(stack -> current) + stack->element_size;
	}
	return 1;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	
	if (stack->current != stack->start)
	{
		stack->current = (char *)(stack->current) - stack->element_size;
	} 
}

int StackIsEmpty(stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->current == stack->start);
}

size_t StackSize(stack_t *stack)
{
	assert(NULL != stack);
	
	return (((size_t)(stack->current) - (size_t)(stack->start)) / stack -> element_size);
}

void *StackPeek(stack_t *stack)
{
	assert(NULL != stack);
	
	return (char *)stack->current - stack->element_size;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
		
	free(stack->start); stack->start = NULL;
	free(stack); stack = NULL;
}



