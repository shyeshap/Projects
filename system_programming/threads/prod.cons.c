#include <stdio.h>			/* printf()	*/
#include <unistd.h>	
#include <pthread.h>		/* threads	*/
#include <stdatomic.h>		/* atomic 	*/

void *SumOfDividers(void *param);

#define NUM (100)
#define SIZE (20)
volatile atomic_flag flag = ATOMIC_FLAG_INIT;

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
		while (atomic_flag_test_and_set(&flag));

		for (i = 0; i < SIZE; ++i)
		{
			++arr[i];
		}

		atomic_flag_clear(&flag);
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
		while (atomic_flag_test_and_set(&flag));

		for (i = 0; i < SIZE; ++i)
		{
			sum += arr[i];
		}

		n = arr[0];
		if (sum / SIZE == n)
		{
			printf("SUCSSES %ld\n", n);
		}

		else
		{
			printf("OH NO!! %ld\n", n);
		}
		
		sum = 0;
		atomic_flag_clear(&flag);
	}

	return NULL;
}