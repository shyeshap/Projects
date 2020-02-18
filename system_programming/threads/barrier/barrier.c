#include <stdio.h>			/* printf() */
#include <pthread.h>		/* pthread_	*/
#include <semaphore.h>		/* sem_ 	*/

#define GREEN "\033[32m"
#define RESET "\033[0m"

#define NUM_OF_CONSUMERS (5)

/**************************************************************/
static void *Producer(void *data);
static void *Consumer(void *data);
/**************************************************************/

int waiting_threads = 0;
int global = 0;
int producer_done = 1;
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
		for (i = 0; i < NUM_OF_CONSUMERS; ++i)
		{
			sem_wait(&sem);
		}

		pthread_mutex_lock(&mutex);

		++global;
		printf(GREEN "producer: %d\n" RESET, global);
		pthread_cond_broadcast(&cond);

		pthread_mutex_unlock(&mutex);
	}
	
	return NULL;
}

static void *Consumer(void *data)
{
	while (1)
	{
		int local = global;

		pthread_mutex_lock(&mutex);
		sem_post(&sem);

		while (global == local)
		{
			pthread_cond_wait(&cond, &mutex);
		}

		printf("consumer: %d\n", local);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}
