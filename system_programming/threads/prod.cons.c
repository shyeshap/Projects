#include <stdio.h>			/* printf()	*/
#include <pthread.h>		/* threads	*/

void *SumOfDividers(void *param);

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define BLUE "\x1b[34m"
#define RESET "\033[0m"

#define NUM (100000000)
#define SIZE (1000)

enum lock
{
	FREE,
	LOCKED
};

int can_produce = FREE;
int can_consume = LOCKED;

size_t arr[NUM] = {0};

void *Producer(void *param);
void *Consumer(void *param);

int main()
{
	int status = 0;
	pthread_t thread1 = 0, thread2 = 0;

	status = pthread_create(&thread1, NULL, Producer, NULL);
	if (0 != status)
	{
		printf("pthread1 create error \n");
		return 1;
	}

	status = pthread_create(&thread2, NULL, Consumer, NULL);
	if (0 != status)
	{
		printf("pthread2 create error \n");
		return 1;
	}


	status = pthread_join(thread1, NULL);
	if (0 != status)
	{
		printf("pthread1 join error \n");
		return 1;
	}

	pthread_join(thread2, NULL);
	if (0 != status)
	{
		printf("pthread2 join error \n");
		return 1;
	}

	return 0;
}

void *Producer(void *param)
{
	size_t i = 0, j = 0;

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

void *Consumer(void *param)
{
	size_t i = 0, j = 0;
	size_t sum = 0;
	size_t n = 0;

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