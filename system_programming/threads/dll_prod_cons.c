#include <stdio.h>			/* printf() */
#include <pthread.h>		/* threads	*/
#include <time.h>			/* time ()	*/
#include <stdlib.h>			/* srand()	*/

#include "./../../ds/include/dll.h"

typedef void *(*start_routine_t) (void *);

/****** implementaion functions declaration ********/
static void *Producer(void *param);
static void *Consumer(void *param);
static void CreateThreads(pthread_t *thread, start_routine_t rutine, void *param);
/***************************************************/

#define TIMES (15000)
#define TICKS (12000000)

enum lock
{
	UNLOCKED,
	LOCKED
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t prod_thread[TIMES] = {0}, cons_thread[TIMES] = {0};
dll_t *dll = NULL;

int main()
{
	int status = 0;
	size_t i = 0;
	size_t data_arr[TIMES] = {0};
	dll = DLLCreate();

	for (i = 0; i < TIMES; ++i)
	{
		data_arr[i] = i;
	}

	for (i = 0; i < TIMES; ++i)
	{
		CreateThreads(&prod_thread[i], Producer, &data_arr[i]);
		CreateThreads(&cons_thread[i], Consumer, &data_arr[i]);
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
	pthread_mutex_unlock(&mutex);

	return NULL;
}

static void *Consumer(void *data)
{
	int start_time = clock();

	while (clock() < (start_time + TICKS))
	{
		pthread_mutex_lock(&mutex);
		
		if (!DLLIsEmpty(dll))
		{
			printf("POP: %lu\n", *(size_t *)DLLPopBack(dll));
		}

		pthread_mutex_unlock(&mutex);
	}

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