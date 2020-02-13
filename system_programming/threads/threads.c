#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *PutOnes(void *param);

#define SIZE (100000)

int arr[SIZE] = {0};

int main()
{
	
	size_t i = 0;
	int status = 0;
	size_t sum = 0;
	pthread_t threads[SIZE] = {0};
	size_t ind[SIZE] = {0};

	for (i = 0; i < SIZE; ++i)
	{
		ind[i] = i;
	}

	for (i = 0; i < SIZE; ++i)
	{
		status = pthread_create(&threads[i], NULL, PutOnes, &ind[i]);
		if (0 != status)
		{
			printf("%lu\n", i);
		}

		pthread_detach(threads[i]);
		/*pthread_join(threads[i], NULL);*/
	}

	sleep(10);

	for (i = 0; i < SIZE; ++i)
	{
		sum += arr[i];
	}

	printf("\n%lu\n", sum);
	pthread_exit(NULL);
	
	return 0;

} 

void *PutOnes(void *param)
{
	arr[*(int *)param] = 1;
}