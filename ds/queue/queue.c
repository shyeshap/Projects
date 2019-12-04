#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "queue.h" /* queue ds functions */
#include "linked_list.h"

#define FREE(x) free(x); x = NULL;

struct Queue
{
	node_t *front;
	node_t *rear;
};

queue_t *QCreate()
{
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    if (NULL != q)
    {
		q->rear = SLLCreateNode(NULL, NULL);
			if (NULL != q->rear)
			{
				q->front = SLLCreateNode(q->rear, NULL);
				if (NULL != q->front)
				{
					return q;	
				}
				FREE(q->rear);
			}
			FREE(q);
    }    
    return q;
}

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->front);
	
	FREE(queue);
}

int QEnqueue(queue_t *queue, void *data)
{
	node_t *new_node = NULL;
	int status = 0;
	
	assert(NULL != queue);
	assert(NULL != data);
	
	new_node = SLLCreateNode(NULL, data);
	if (NULL == new_node)
	{
		return !status;
	}
	
	status = SLLInsert(new_node, queue->rear);
	queue->rear = new_node;
	
	return status;
}

void QDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLRemoveAfter(queue->front);
}

void *QPeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return queue->front->next->data;
}

queue_t *QAppend(queue_t *queue1, queue_t *queue2)
{
	assert(NULL != queue1);
	assert(NULL != queue2);
	
	queue1->rear->next = queue2->front;
	SLLRemove(queue1->rear);
	SLLRemove(queue1->rear);
	queue1->rear = queue2->rear;
	
	FREE(queue2);
	
	return queue1;
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (queue->front->next == queue->rear);
}

size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLSize(queue->front) - 2);
}
