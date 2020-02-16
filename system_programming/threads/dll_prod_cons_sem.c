#include <stdio.h>			/* printf() */
#include <pthread.h>		/* threads	*/
#include <time.h>			/* time ()	*/
#include <stdlib.h>			/* srand()	*/
#include <semaphore.h>		/* sem_ 	*/

#include "./../../ds/include/dll.h"

/****** implementaion functions declaration ********/
static void *Producer(void *param);
static void *Consumer(void *param);
/***************************************************/

#define TIMES 10000

enum lock
{
	UNLOCKED,
	LOCKED
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem = {0};
pthread_t prod_thread[TIMES] = {0}, cons_thread[TIMES] = {0};
dll_t *dll = NULL;

int main()
{
	int status = 0;
	size_t i = 0;
	size_t data_arr[TIMES] = {0};
	dll = DLLCreate();
	sem_init(&sem, 0, 0);

	for (i = 0; i < TIMES; ++i)
	{
		data_arr[i] = i;
	}

	for (i = 0; i < TIMES; ++i)
	{
		status = pthread_create(&prod_thread[i], NULL, Producer, &data_arr[i]);
		while (0 != status)
		{
			pthread_create(&prod_thread[i], NULL, Producer, &data_arr[i]);
		}

		status = pthread_create(&cons_thread[i], NULL, Consumer, &data_arr[i]);
		while (0 != status)
		{
			pthread_create(&cons_thread[i], NULL, Consumer, &data_arr[i]);
		}
	}

	for (i = 0; i < TIMES; ++i)
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

	DLLDestroy(dll);
	pthread_mutex_destroy(&mutex);

	return 0;
}

static void *Producer(void *data)
{
	pthread_mutex_lock(&mutex);
	DLLPushFront(dll, data);
	printf("PUSH: %lu\n", *(size_t *)DLLGetData(DLLBegin(dll)));
	sem_post(&sem);
	pthread_mutex_unlock(&mutex);

	return NULL;
}

static void *Consumer(void *data)
{
	sem_wait(&sem);
	pthread_mutex_lock(&mutex);
	printf("POP: %lu\n", *(size_t *)DLLPopBack(dll));
	pthread_mutex_unlock(&mutex);

	return NULL;
}
