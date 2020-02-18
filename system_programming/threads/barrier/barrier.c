#include <stdio.h>			/* printf() */
#include <pthread.h>		/* pthread_	*/
#include <semaphore.h>		/* sem_ 	*/

#define NUM_OF_CONSUMERS (100)

/**************************************************************/
static void *Producer(void *data);
static void *Consumer(void *data);
/**************************************************************/

int waiting_threads = 0;
int global = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t sem = {0};

int main()
{
	pthread_t prod_thread = {0}, 
			  cons_thread[NUM_OF_CONSUMERS] = {0};
	int status = 0;
	size_t i = 0;
	sem_init(&sem, 0, 0);

	status = pthread_create(&prod_thread, NULL, Producer, NULL);
	if (0 != status)
	{
		printf("prod_thread create error");
		return 1;
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_create(&cons_thread[i], NULL, Consumer, (void *)i);
		if (0 != status)
		{
			printf("cons_thread %ld create error\n", i);
			return 1;
		}
	}

	status = pthread_join(prod_thread, NULL);
	if (0 != status)
	{
		printf("prod_pthread create error \n");
		
		return 1;
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_join(cons_thread[i], NULL);
		if (0 != status)
		{
			printf("cons_pthread create error \n");
			
			return 1;
		}
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	sem_destroy(&sem);

	return 0;
}

/**************************************************************/
static void *Producer(void *data)
{
	int i = 0;

	while (1)
	{
		global = global + NUM_OF_CONSUMERS;
		printf("%d\n", global);
	
		pthread_mutex_lock(&mutex);

		while(NUM_OF_CONSUMERS != waiting_threads)
		{
			pthread_mutex_unlock(&mutex);
			pthread_mutex_lock(&mutex);
		}

		waiting_threads = 0;
		pthread_cond_broadcast(&cond);

		pthread_mutex_unlock(&mutex);

		for (i = 0; i < NUM_OF_CONSUMERS; ++i)
		{
			sem_wait(&sem);
		}

	}
	
	return NULL;
}

static void *Consumer(void *data)
{
	while (1)
	{
		int local = 0;

		pthread_mutex_lock(&mutex);
		++waiting_threads;
		pthread_cond_wait(&cond, &mutex);
		local = --global;
		printf("consumer: %d\n", local);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem);
	}

	return NULL;
}
