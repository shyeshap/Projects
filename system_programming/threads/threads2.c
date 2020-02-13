#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *SumOfDividers(void *param);

#define NUM (1000000000)

size_t arr[NUM_OF_THREADS];
size_t res[NUM_OF_THREADS] = {0};

int main()
{
	size_t i = 0;
	int status = 0;
	size_t sum = 0;
	pthread_t threads[NUM_OF_THREADS] = {0};

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&threads[i], NULL, SumOfDividers, (void*)i);
		if (0 != status)
		{
			printf("create: %lu\n error: %d", i, status);
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_join(threads[i], NULL);
		if (0 != status)
		{
			printf("join: %lu\n error: %d", i, status);
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		sum += res[i];
	}

	printf("\n%lu\n", sum);
	pthread_exit(NULL);
	

	return 0;
}

void *SumOfDividers(void *times)
{
	size_t section_size = NUM / NUM_OF_THREADS;
	size_t stop = (section_size + ((size_t)times * section_size) + 1);
	size_t i = ((size_t)times * section_size + 1);

	for (; i < stop; ++i)
	{
		if ((0 == (NUM % i)))
		{
			res[(size_t)times] += i;
		}
	}
	
	return NULL;
}