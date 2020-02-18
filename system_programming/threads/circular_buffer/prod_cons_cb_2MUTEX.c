#include <stdio.h>			/* printf() */
#include <pthread.h>		/* pthread_	*/
#include <semaphore.h>		/* sem_ 	*/

#include "./../../include/circular_buffer.h"

#define UNUSED(x) (void)(x)
#define THREADS_NUM (400)
#define CB_CAPACITY (1)

typedef void *(*start_routine_t) (void *);

/**************************************************************/
static void *Producer(void *data);
static void *Consumer(void *data);
static void CreateThreads(pthread_t *thread, start_routine_t rutine, void *param);
/**************************************************************/

pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;
cbuffer_t *cb = NULL;
sem_t write_sem = {0}, read_sem = {0};

int main()
{
	pthread_t prod_thread[THREADS_NUM] = {0}, 
			  cons_thread[THREADS_NUM] = {0};
	size_t data_arr[THREADS_NUM] = {0};
	size_t i = 0;
	int status = 0;
	
	cb = CBufferCreate(CB_CAPACITY);
	sem_init(&write_sem, 0, CB_CAPACITY);
	sem_init(&read_sem, 0, 0);

	for (i = 0; i < THREADS_NUM; ++i)
	{
		data_arr[i] = i;
	}

	for (i = 0; i < THREADS_NUM; ++i)
	{
		CreateThreads(&prod_thread[i], &Producer, &data_arr[i]);
		CreateThreads(&cons_thread[i], &Consumer, NULL);
	}

	for (i = 0; i < THREADS_NUM; ++i)
	{
		status = pthread_join(prod_thread[i], NULL);
		if (0 != status)
		{
			printf("prod_pthread create error \n");
			return 1;
		}

		status = pthread_join(cons_thread[i], NULL);
		if (0 != status)
		{
			printf("cons_pthread create error \n");
			return 1;
		}
	}

	CBufferDestroy(cb);
	pthread_mutex_destroy(&write_mutex);
	pthread_mutex_destroy(&read_mutex);
	sem_destroy(&write_sem);
	sem_destroy(&read_sem);

	return 0;
}

/**********************************************************/
static void *Producer(void *data)
{
	sem_wait(&write_sem);
	pthread_mutex_lock(&write_mutex);
	printf("W: %d\n", *(int *)data);
	CBufferWrite(cb, *(int *)data);
	pthread_mutex_unlock(&write_mutex);
	sem_post(&read_sem);

	return NULL;
}

static void *Consumer(void *data)
{
	int read = 0;
	UNUSED(data);

	sem_wait(&read_sem);
	pthread_mutex_lock(&read_mutex);
	read = CBufferRead(cb);
	printf("R: %d\n", read);
	pthread_mutex_unlock(&read_mutex);
	sem_post(&write_sem);

	return NULL;
}

static void CreateThreads(pthread_t *thread, start_routine_t rutine, void *param)
{
	int status = 0;

	status = pthread_create(thread, NULL, rutine, param);
	while (0 != status)
	{
		status = pthread_create(thread, NULL, rutine, param);
	}
}