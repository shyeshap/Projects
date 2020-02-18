#include <stdio.h>		/* perror() 	*/
#include <stdlib.h>		/* exit()   	*/
#include <semaphore.h>	/* semaphore_	*/
#include <fcntl.h>		/* O_CREAT		*/
#include <sys/stat.h> 	/* MODE 		*/

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

#define TIMES 100

int main()
{
	char *ping_name = "/ping";
	char *pong_name = "/pong";

	int i = 0;
	sem_t *ping = NULL, *pong = NULL;
	int status = 0;

	ping = sem_open(ping_name, O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == ping)
	{
		printf("SEM_FAILED\n");
		return 1;
	}

	pong = sem_open(pong_name, O_CREAT, SEM_PERMS, 0);
	if (SEM_FAILED == pong)
	{
		sem_close(ping);
		sem_unlink(ping_name);
		printf("SEM_FAILED\n");
		return 1;
	}

	while (i < TIMES)
	{	

		status = sem_wait(pong);
		while (status != 0)
		{
			sem_wait(pong);
		}
		printf("pong\n");
		status = sem_post(ping);
		while (status != 0)
		{
			sem_post(ping);
		}

		++i;
	}

	sem_close(ping);
	sem_unlink(ping_name);

	return 0;
}
