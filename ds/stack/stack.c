#include <stdio.h> /* typedef */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

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

int stackPush(stack_t *stack, void *data)
{
	if (stack->current == stack->end)
	{
		return 1;
	}
	else
	{
		memcpy(stack->current, data, stack->element_size);
		stack->current = (char *)(stack -> current) + stack->element_size;
	}
	return 0;
}

void StackPop(stack_t *stack)
{
	if (stack->current == stack->start)
	{
		return;
	} 
	stack->current = (char *)(stack->current) - stack->element_size;
}

int StackIsEmpty(stack_t *stack)
{
	return (stack->current == stack->start);
}

size_t StackSize(stack_t *stack)
{
	return (((size_t)(stack->current) - (size_t)(stack->start)) / stack -> element_size);
}

void *StackPick(stack_t *stack)
{
	return (char *)stack->current - stack->element_size;
}

int main()
{
	
	return 0;
}
