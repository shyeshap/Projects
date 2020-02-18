#include <stdio.h>			/* printf()	*/
#include <pthread.h>		/* threads	*/

void *SumOfDividers(void *param);

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define NUM (100000000)
#define SIZE (1000)

#define UNUSED(x) (void)(x)

typedef void *(*start_routine_t) (void *);

/************ implementation declerations **************/
static void *Producer(void *param);
static void *Consumer(void *param);
static void CreateThreads(pthread_t *thread, start_routine_t);

/*******************************************************/

enum lock
{
	FREE,
	LOCKED
};

int can_produce = FREE;
int can_consume = LOCKED;
size_t arr[NUM] = {0};

int main()
{
	int status = 0;
	pthread_t thread_prod = 0, thread_cons = 0;

	CreateThreads(&thread_prod, Producer);
	CreateThreads(&thread_cons, Consumer);

	status = pthread_join(thread_prod, NULL);
	if (0 != status)
	{
		printf("thread_prod join error \n");
		return 1;
	}

	status = pthread_join(thread_cons, NULL);
	if (0 != status)
	{
		printf("thread_cons join error \n");
		return 1;
	}

	return 0;
}

/*************implementation functions********************/
static void *Producer(void *param)
{
	size_t i = 0, j = 0;

	UNUSED(param);

	for (j = 0; j < NUM; ++j)
	{
		while (__sync_lock_test_and_set(&can_produce, LOCKED));

		for (i = 0; i < SIZE; ++i)
		{
			++arr[i];
		}

		__sync_lock_release(&can_consume);
	}

	return NULL;
}

static void *Consumer(void *param)
{
	size_t i = 0, j = 0;
	size_t sum = 0;
	size_t n = 0;

	UNUSED(param);

	for (j = 0; j < NUM; ++j)
	{
		while (__sync_lock_test_and_set(&can_consume, LOCKED));
		
		for (i = 0; i < SIZE; ++i)
		{
			sum += arr[i];
		}

		n = arr[0];
		if (sum / SIZE == n)
		{
			printf(GREEN "SUCSSES %ld\n" RESET, n);
		}

		else
		{
			printf(RED "OH NO!! %ld\n" RESET, n);
		}
		
		sum = 0;

		__sync_lock_release(&can_produce);
	}

	return NULL;
}

static void CreateThreads(pthread_t *thread, start_routine_t rutine)
{
	int status = 0;

	status = pthread_create(thread, NULL, rutine, NULL);
	while (0 != status)
	{
		status = pthread_create(thread, NULL, rutine, NULL);
	}
}