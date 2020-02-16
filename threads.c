#include <stdio.h>
#include <stdlib.h> /*malloc() */
#include <pthread.h>

void *ThreadFunc1(void *param);
void *ThreadFunc2(void *param);
static void MakeKey();

static pthread_key_t key = 0;

int main()
{
	pthread_t thread1 = 0, thread2 = 0;
	int status = 0;
	void *ret = NULL;

	status = pthread_create(&thread1, NULL, ThreadFunc1, NULL);
	status = pthread_create(&thread2, NULL, ThreadFunc2, NULL);

	printf("Father thread %ld\n", pthread_self());
	
	ThreadFunc1(NULL);

	pthread_join(thread1, &ret);

	printf("%d\n", *(int *)ret);

	free(ret);

	return 0;
}

void *ThreadFunc1(void *param)
{
	int *mal = malloc(4);

	printf("Child 1 thread %ld\n", pthread_self());

	*mal = 1;

	pthread_setspecific(key, mal);

	*mal = 7;

	pthread_exit(mal);
}

void *ThreadFunc2(void *param)
{
	int *mal = malloc(4);

	printf("Child 2 thread %ld\n", pthread_self());

	*mal = 3;

	pthread_setspecific(key, mal);

	pthread_exit(mal);
}

static void MakeKey(void *value)
{
	(void)pthread_key_create(&key, NULL);
}